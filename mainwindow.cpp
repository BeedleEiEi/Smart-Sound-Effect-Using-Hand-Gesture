#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qdebug.h"


void on_trackbar( int, void* )
{//This function gets called whenever a
    // trackbar position is changed
}

//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;

//////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_openCamButton_clicked()
{
    cap.open(0);


    if(!cap.isOpened()){
        cout << "camera is not open" << endl;
    }
    else{
        cout << "camera is open" << endl;
        createTrackbars();
        connect(timer, SIGNAL(timeout()), this, SLOT(process()));
        timer->start(20);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    } else if(mat.channels() == 3) {            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
    } else {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();        // return a blank QImage if the above did not work
}

/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::process()
{
    Mat frameGray;
    Mat frameRoi;
    Mat frameTresh;

    cap >> frame;

    Rect roi(100,100,400,300);
    frameRoi = frame(roi);

    cvtColor(frameRoi,frameRoi,COLOR_BGR2HSV);

    cvtColor(frameRoi, frameGray,CV_RGB2GRAY);


    GaussianBlur(frameGray, frameGray, Size(19,19), 0.0, 0);

    inRange(frameRoi, Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX), frameTresh);

    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));
//    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));

//    erode(frameTresh, frameTresh, erodeElement);
//    erode(frameTresh, frameTresh, erodeElement);

    dilate(frameTresh, frameTresh, dilateElement);
//    dilate(frameTresh, frameTresh, dilateElement);
    //threshold(frameGray, frameTresh, 100, 255, THRESH_BINARY_INV+THRESH_OTSU);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(frameTresh,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,Point());
    if(contours.size()>0){
        int count;
        char a[40];
        size_t indexOfBiggestContour = -1;
        size_t sizeOfBiggestContour = 0;

        for (size_t i = 0; i < contours.size(); i++){
            if(contours[i].size() > sizeOfBiggestContour){
                sizeOfBiggestContour = contours[i].size();
                indexOfBiggestContour = i;
            }
        }
        vector<vector<int> >hull(contours.size());
        vector<vector<Point> >hullPoint(contours.size());
        vector<vector<Vec4i> >defects(contours.size());
        vector<vector<Point> >defectPoint(contours.size());
        vector<vector<Point> >contours_poly(contours.size());
        Point2f rect_point[4];
        vector<RotatedRect>minRect(contours.size());
        vector<Rect> boundRect(contours.size());
        for(size_t i=0;i<contours.size();i++){
            if(contourArea(contours[i])>5000){
                convexHull(contours[i],hull[i],true);
                convexityDefects(contours[i],hull[i],defects[i]);
                if(indexOfBiggestContour==i){
                    minRect[i]=minAreaRect(contours[i]);
                    for(size_t k=0;k<hull[i].size();k++){
                        int ind=hull[i][k];
                        hullPoint[i].push_back(contours[i][ind]);
                    }
                    count = 0;

                    for(size_t k=0;k<defects[i].size();k++){
                        if(defects[i][k][3]>13*256){
                            /*   int p_start=defects[i][k][0];   */
                            int p_end=defects[i][k][1];
                            int p_far=defects[i][k][2];
                            defectPoint[i].push_back(contours[i][p_far]);
                            circle(frameRoi,contours[i][p_end],3,Scalar(0,255,0),2);
                            count++;
                        }

                    }

                    if(count==1)
                        strcpy(a,"1");
                    else if(count==2)
                        strcpy(a,"2");
                    else if(count==3)
                        strcpy(a,"3");
                    else if(count==4)
                        strcpy(a,"4");
                    else if(count==5)
                        strcpy(a,"5");
                    else
                        strcpy(a,"IT'S NOT 1-5!!");

                    putText(frame,a,Point(70,70),CV_FONT_HERSHEY_SIMPLEX,3,Scalar(255,0,0),2,8,false);
                    drawContours(frameTresh, contours, i,Scalar(255,255,0),2, 8, vector<Vec4i>(), 0, Point() );
                    drawContours(frameTresh, hullPoint, i, Scalar(255,255,0),1, 8, vector<Vec4i>(),0, Point());
                    drawContours(frameRoi, hullPoint, i, Scalar(0,0,255),2, 8, vector<Vec4i>(),0, Point() );
                    approxPolyDP(contours[i],contours_poly[i],3,false);
                    boundRect[i]=boundingRect(contours_poly[i]);
                    rectangle(frameRoi, boundRect[i].tl(), boundRect[i].br(), Scalar(255,0,0), 2, 8, 0);
                    minRect[i].points(rect_point);
                    for(size_t k=0;k<4;k++){
                        line(frameRoi,rect_point[k],rect_point[(k+1)%4],Scalar(0,255,0),2,8);
                    }

                }
            }

        }

        namedWindow("Original_image",CV_WINDOW_NORMAL);
        namedWindow("Gray_image",CV_WINDOW_NORMAL);
        namedWindow("Thresholded_image",CV_WINDOW_NORMAL);
        namedWindow("ROI",CV_WINDOW_NORMAL);

        resizeWindow("Original_image", 200, 200);
        resizeWindow("Gray_image", 200, 200);
        resizeWindow("Thresholded_image", 200, 200);
        resizeWindow("ROI", 200, 200);

        imshow("Original_image",frame);
        imshow("Gray_image",frameGray);
        imshow("Thresholded_image",frameTresh);
        imshow("ROI",frameRoi);


        qt_image = convertOpenCVMatToQtQImage(frame);

        ui->display->setPixmap(QPixmap::fromImage(qt_image));

    }
}

void MainWindow::createTrackbars(){
    namedWindow("Trackbar",0);
    //create memory to store trackbar name on window
    char TrackbarName[50];
    sprintf( TrackbarName, "H_MIN", H_MIN);
    sprintf( TrackbarName, "H_MAX", H_MAX);
    sprintf( TrackbarName, "S_MIN", S_MIN);
    sprintf( TrackbarName, "S_MAX", S_MAX);
    sprintf( TrackbarName, "V_MIN", V_MIN);
    sprintf( TrackbarName, "V_MAX", V_MAX);
    //create trackbars and insert them into window
    //3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
    //the max value the trackbar can move (eg. H_HIGH),
    //and the function that is called whenever the trackbar is moved(eg. on_trackbar)
    //                                  ---->    ---->     ---->
    createTrackbar( "H_MIN", "Trackbar", &H_MIN, H_MAX, on_trackbar );
    createTrackbar( "H_MAX", "Trackbar", &H_MAX, H_MAX, on_trackbar );
    createTrackbar( "S_MIN", "Trackbar", &S_MIN, S_MAX, on_trackbar );
    createTrackbar( "S_MAX", "Trackbar", &S_MAX, S_MAX, on_trackbar );
    createTrackbar( "V_MIN", "Trackbar", &V_MIN, V_MAX, on_trackbar );
    createTrackbar( "V_MAX", "Trackbar", &V_MAX, V_MAX, on_trackbar );
}

