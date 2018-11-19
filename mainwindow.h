#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "QMediaPlayer"

using namespace cv;

#include <iostream>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openCamButton_clicked();

    void process();

    QImage convertOpenCVMatToQtQImage(cv::Mat mat);

    void createTrackbars();

    void createSoundEffect();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    VideoCapture cap;

    Mat frame;

    QImage qt_image;

    QMediaPlayer * grenadeSound;


};

#endif // MAINWINDOW_H
