#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "QMediaPlayer"

#include <QSound>

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

    void on_setupButton_clicked();

    void loadSoundConfig();

    void saveSoundConfig();


    void on_browseButton1_clicked();

    void on_browseButton2_clicked();

    void on_browseButton3_clicked();

    void on_browseButton4_clicked();

    void on_browseButton5_clicked();



private:

    Ui::MainWindow *ui;

    QTimer *timer;

    VideoCapture cap;

    Mat frame;

    Mat frameThresh;

    QImage qt_image;

    QSound * effect1;
    QSound * effect2;
    QSound * effect3;
    QSound * effect4;
    QSound * effect5;

    QString fileName[5];

};

#endif // MAINWINDOW_H
