#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include "cv.h"
#include "highgui.h"
#include "imgcodecs.hpp"
#include "imgproc.hpp"
#include "core.hpp"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <QtPlugin>
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString Imgname;
    std::string ImgnameinChar;
    QImage newImg;
    QImage GrayImg;
    QImage NegImg;
    QImage GammaImg;

public slots:
    void loadandShowImg();
    void toGrayscale();
    Mat drawHist(Mat& image);
    void drawGrayHist();
    void drawGammaHist(double gamma);
    void negativeHist();
    void contrastHist(double brightness, double contrast);
    void orderDither(int msize);
    void on_show_clicked();
    void on_reset_clicked();
    void on_gray_clicked();
    void on_histgray_clicked();
    void on_histgamma_clicked();
    void on_negative_clicked();

private slots:
    void on_contrast_clicked();

    void on_quit_clicked();

    void on_dither_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
