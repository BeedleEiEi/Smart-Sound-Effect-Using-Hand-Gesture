#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"
#include "QSound"
#include "QFile"

#include "qdebug.h"

#include "QMediaPlayer"


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

int frameCount = 0;
int currentGesture = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    loadSoundConfig();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    delete ui;
    destroyAllWindows();
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
        createSoundEffect();
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
    Mat frameRoi;
    Mat frameHSV;


    cap >> frame;

    Rect roi(100,100,400,300);
    frameRoi = frame(roi);

    cvtColor(frameRoi,frameHSV,COLOR_BGR2HSV);

    inRange(frameHSV, Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX), frameThresh);

    Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));
////    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));

////    erode(frameTresh, frameTresh, erodeElement);
////    erode(frameTresh, frameTresh, erodeElement);

    dilate(frameThresh, frameThresh, dilateElement);
//    dilate(frameTresh, frameTresh, dilateElement);
    //threshold(frameGray, frameTresh, 100, 255, THRESH_BINARY_INV+THRESH_OTSU);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(frameThresh,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,Point());
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
                            circle(frameRoi,contours[i][p_far],3,Scalar(0,255,0),2);
                            count++;
                        }

                    }

                    if(count==1){
                        strcpy(a,"1");
                        if(!ui->checkBox->isChecked()){
                            effect1->play();
                        }
                        if(currentGesture == count){
                            frameCount++;
                        }else{
                            currentGesture = 1;
                            frameCount = 0;
                        }

                    }
                    else if(count==2){
                        strcpy(a,"2");
                        if(!ui->checkBox->isChecked()){
                            effect2->play();
                        }
                        if(currentGesture == count){
                            frameCount++;
                        }else{
                            currentGesture = 2;
                            frameCount = 0;
                        }
                    }
                    else if(count==3){
                        strcpy(a,"3");
                        if(!ui->checkBox->isChecked()){
                            effect3->play();
                        }
                        if(currentGesture == count){
                            frameCount++;
                        }else{
                            currentGesture = 3;
                            frameCount = 0;
                        }
                    }
                    else if(count==4){
                        strcpy(a,"4");
                        if(!ui->checkBox->isChecked()){
                            effect4->play();
                        }
                        if(currentGesture == count){
                            frameCount++;
                        }else{
                            currentGesture = 4;
                            frameCount = 0;
                        }
                    }
                    else if(count==5){
                        strcpy(a,"5");
                        if(!ui->checkBox->isChecked()){
                            effect5->play();
                        }
                        if(currentGesture == count){
                            frameCount++;
                        }else{
                            currentGesture = 5;
                            frameCount = 0;
                        }
                    }
                    else{
                        strcpy(a,"CAN'T DETECT");
                        frameCount = 0;
                    }

                    if(frameCount == 3){
                        frameCount = 0;
                        if(currentGesture == 5){

                        }
                        else if(currentGesture == 3){
                        }

                    }

                    putText(frame,a,Point(70,70),CV_FONT_HERSHEY_SIMPLEX,3,Scalar(255,0,0),2,8,false);
                    drawContours(frameThresh, contours, i,Scalar(255,255,0),2, 8, vector<Vec4i>(), 0, Point() );
                    drawContours(frameThresh, hullPoint, i, Scalar(255,255,0),1, 8, vector<Vec4i>(),0, Point());
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

//        namedWindow("Original_image",CV_WINDOW_NORMAL);
        namedWindow("Thresholded_image",CV_WINDOW_NORMAL);
//        namedWindow("ROI",CV_WINDOW_NORMAL);

//        resizeWindow("Original_image", 200, 200);
        resizeWindow("Thresholded_image", 200, 200);
//        resizeWindow("ROI", 200, 200);

//        imshow("Original_image",frameHSV);
        imshow("Thresholded_image",frameThresh);
//        imshow("ROI",frameRoi);


        qt_image = convertOpenCVMatToQtQImage(frame);

        ui->display->setPixmap(QPixmap::fromImage(qt_image));

        cout << frameCount << endl;

    }
}

/////////////////////////////////////////////////////////
void MainWindow::createTrackbars(){
    namedWindow("Trackbar",0);
    //create memory to store trackbar name on window
    char TrackbarName[50];
    sprintf(TrackbarName, "H_MIN", H_MIN);
    sprintf(TrackbarName, "H_MAX", H_MAX);
    sprintf(TrackbarName, "S_MIN", S_MIN);
    sprintf(TrackbarName, "S_MAX", S_MAX);
    sprintf(TrackbarName, "V_MIN", V_MIN);
    sprintf(TrackbarName, "V_MAX", V_MAX);
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

///////////////////////////////////////////////////////////////////////////
void MainWindow::createSoundEffect(){
    effect1 = new QSound(fileName[0], this);
    effect2 = new QSound(fileName[1], this);
    effect3 = new QSound(fileName[2], this);
    effect4 = new QSound(fileName[3], this);
    effect5 = new QSound(fileName[4], this);
}


void MainWindow::on_setupButton_clicked()
{
    cap.open(0);


    if(!cap.isOpened()){
        cout << "camera is not open" << endl;
    }
    else{
        cout << "camera is open" << endl;

        createTrackbars();

        namedWindow("Frame", WINDOW_NORMAL);
        resizeWindow("Frame", 200, 200);
        namedWindow("Threshold", WINDOW_NORMAL);
        resizeWindow("Threshold", 200, 200);

        moveWindow("Frame", 15, 15);
        moveWindow("Threshold", 230, 15);

        Mat frameRoi;
        Mat frameHSV;
        int c = 0;
        while(c != 27){

            cap >> frame;

            Rect roi(100,100,400,300);
            frameRoi = frame(roi);

            cvtColor(frameRoi,frameHSV,COLOR_BGR2HSV);

            inRange(frameHSV, Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX), frameThresh);

            Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

            dilate(frameThresh, frameThresh, dilateElement);

            imshow("Threshold", frameThresh);
            imshow("Frame", frameHSV);
            c = waitKey(30);
        }
        destroyAllWindows();
    }
}



void MainWindow::on_browseButton1_clicked()
{
    fileName[0] = QFileDialog::getOpenFileName(this, "Open File", "C:://");
    ui->lineEdit1->setText(fileName[0]);
    saveSoundConfig();
    createSoundEffect();
}

void MainWindow::on_browseButton2_clicked()
{
    fileName[1] = QFileDialog::getOpenFileName(this, "Open File", "C:://");
    ui->lineEdit2->setText(fileName[1]);
    saveSoundConfig();
    createSoundEffect();
}

void MainWindow::on_browseButton3_clicked()
{
    fileName[2] = QFileDialog::getOpenFileName(this, "Open File", "C:://");
    ui->lineEdit3->setText(fileName[2]);
    saveSoundConfig();
    createSoundEffect();
}

void MainWindow::on_browseButton4_clicked()
{
    fileName[3] = QFileDialog::getOpenFileName(this, "Open File", "C:://");
    ui->lineEdit4->setText(fileName[3]);
    saveSoundConfig();
    createSoundEffect();
}

void MainWindow::on_browseButton5_clicked()
{
    fileName[4] = QFileDialog::getOpenFileName(this, "Open File", "C:://");
    ui->lineEdit5->setText(fileName[4]);
    saveSoundConfig();
    createSoundEffect();
}

void MainWindow::loadSoundConfig(){
    QFile file("SoundConfig.txt");

    if(!file.exists()){
        cout << "Does not Exists" << endl;
        return;
    }
    else{
        if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream txtStream(&file);

            //read file
            txtStream.seek(0);
            int i = 0;
            while(!txtStream.atEnd()){
                fileName[i] = QString::fromStdString(txtStream.readLine().toStdString());
                i++;
            }
            ui->lineEdit1->setText(fileName[0]);
            ui->lineEdit2->setText(fileName[1]);
            ui->lineEdit3->setText(fileName[2]);
            ui->lineEdit4->setText(fileName[3]);
            ui->lineEdit5->setText(fileName[4]);
        }
    }

}

void MainWindow::saveSoundConfig(){
    QFile file("SoundConfig.txt");

    if(file.exists()){
        file.remove();
    }
    if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream txtStream(&file);

        //write file
        cout << "Writing File..." << endl;
        txtStream << fileName[0] << "\n";
        txtStream << fileName[1] << "\n";
        txtStream << fileName[2] << "\n";
        txtStream << fileName[3] << "\n";
        txtStream << fileName[4] << "\n";
        cout << "Finish^^" << endl;
    }
}
