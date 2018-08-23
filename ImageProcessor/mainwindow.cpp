#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QCoreApplication>
#include <cmath>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//load and show image implmentation
void MainWindow::loadandShowImg(){
    //get target file name
    Imgname = QFileDialog::getOpenFileName(this,tr("Select a image"),".",tr("Image Files(*.bmp *.jpg *.jpeg *.png)"));
    if(Imgname.length()==0){
        QMessageBox::information(NULL,tr("Path"),tr("You didn't select a image!"));
    }
    else{
        QMessageBox::information(NULL,tr("Path"),tr("You selected")+Imgname);
        //transform Qstring to const string in C++
        ImgnameinChar = Imgname.toLocal8Bit().constData();
        //load the original color img using OpenCV imread function by pass in a const string
        Mat img;
        img = imread(ImgnameinChar);
        //Qt read in RGB but OpenCV read in BGR
        cv::cvtColor(img,img,CV_BGR2RGB);
        //convert the load image to Qt format,Returns a QImage in which the values of the red and blue components of all pixels have been swapped, effectively converting an RGB image to an BGR image.
        QImage newImg((const unsigned char*)img.data,img.cols,img.rows, img.step, QImage::Format_RGB888);
        //show the converted image into app window
        ui->show_img->setPixmap(QPixmap::fromImage(newImg));
    }
 }

//color image to grayscale img implementation
void MainWindow::toGrayscale(){
    //clear out the content currently display on window
    ui->show_img->clear();
    //read in the grayscale image
    Mat gray;
    gray = imread(ImgnameinChar,0);
    //convert the Grayscale image to Qt format
    QImage GrayImg((const unsigned char*)gray.data,gray.cols,gray.rows,gray.step,QImage::Format_Indexed8);
    GrayImg.setPixel(0,0,qRgb(0,0,0));
    //display the image in the window
    ui->show_img->setPixmap(QPixmap::fromImage(GrayImg));
}

//reusable calculate histogram function
Mat MainWindow::drawHist(Mat& gray){
    //use the calcHist function provided by opencv to calculate the histogram value
    //because here we measure the gray image, so the channel number is 0
    int channels = 0;
    int size = 256;
    float hranges[] = {0,255};
    const float* ranges[] = {hranges};
    int dims = 1;
    MatND hist_val;
    //calculate the histogram value
    calcHist(&gray,1, &channels,Mat(),hist_val,dims,&size,ranges);
    int scale = 1;
    Mat hist_img(size*scale,size,CV_8U, Scalar(0));
    //get the max and min value of the hist_val
    double min =0;
    double max =0;
    minMaxLoc(hist_val,&min,&max,0,0);
    //display the histogram
    int maxPoint = saturate_cast<int>(0.9*size);
    //draw the point, refer to the OpenCV documentation
    for(int i=0;i<256;i++){
        float val = hist_val.at<float>(i);
        int intensity = saturate_cast<int>(val*maxPoint/max);
        rectangle(hist_img, Point(i*scale,size-1),Point((i+1)*scale-1, size-intensity),Scalar(255));
    }
    return hist_img;
}

//draw histogram of current grayscale img
void MainWindow::drawGrayHist(){
    //load the current img
    Mat gray;
    //read in the grayscale image
    gray = imread(ImgnameinChar,0);
    Mat res = drawHist(gray);
    //ui->show_img->setPixmap(QPixmap::fromImage(hist_img));
    namedWindow("GrayScale Histogram", WINDOW_NORMAL);
    imshow("GrayScale Histogram",res);
}

//draw gamma histogram of current grascale img
void MainWindow::drawGammaHist(double gamma){
    ui->show_img->clear();
    //load the current img
    Mat gray;
    //read in the grayscale image
    gray = imread(ImgnameinChar,0);
    //build a look up table
    unsigned char table[256];
    for(int i=0;i<256;i++){
        table[i] = saturate_cast<unsigned char>(pow((double) (i/255.0),gamma)*255.0);
    }
    MatIterator_<unsigned char> start,end;
    //match the each image pixel with the look up table and make correction
    for(start=gray.begin<unsigned char>(), end=gray.end<unsigned char>(); start != end; start++){
        *start = table[(*start)];
    }
    Mat gray_copy = gray.clone();
    QImage GammaImg((const unsigned char*)gray.data,gray.cols,gray.rows,gray.step,QImage::Format_Indexed8);
    ui->show_img->setPixmap(QPixmap::fromImage(GammaImg));
    Mat res = drawHist(gray_copy);
    //ui->show_img->setPixmap(QPixmap::fromImage(hist_img));
    namedWindow("Gamma Correction Histogram", WINDOW_NORMAL);
    imshow("Gamma Correction Histogram",res);
}

//negative transformation histogram implementation
void MainWindow::negativeHist(){
    ui->show_img->clear();
    //load the current img
    Mat gray;
    //read in the grayscale image
    gray = imread(ImgnameinChar,0);
    for(int i=0;i<gray.rows;i++){
        for(int j=0; j<gray.cols;j++){
            //flip every pixels
            gray.at<unsigned char>(i,j) = 255-gray.at<unsigned char>(i,j);
        }
    }
    //make a copy of gray
    Mat gray_copy = gray.clone();
    QImage NegImg((const unsigned char*)gray.data,gray.cols,gray.rows,gray.step,QImage::Format_Indexed8);
    ui->show_img->setPixmap(QPixmap::fromImage(NegImg));
    Mat res = drawHist(gray_copy);
    //ui->show_img->setPixmap(QPixmap::fromImage(hist_img));
    namedWindow("Negative Transformation Histogram", WINDOW_NORMAL);
    imshow("Negative Transformation Histogram",res);
}

//contrast transformation histogram implementation
void MainWindow::contrastHist(double brightness, double contrast){
    ui->show_img->clear();
    //load the current img
    Mat gray;
    //read in the grayscale image
    gray = imread(ImgnameinChar,0);
    //initialize a zeros matrix which has identical size of gray
    Mat gray_trans = Mat::zeros(gray.size(),gray.type());
    for(int i=0; i<gray.rows;i++){
        for(int j=0; j<gray.cols;j++){
            gray_trans.at<unsigned char>(i,j) = saturate_cast<unsigned char>(contrast*(gray.at<unsigned char>(i,j))+brightness);
        }
    }
    //convert the Grayscale image to Qt format
    QImage GrayImg((const unsigned char*)gray_trans.data,gray_trans.cols,gray_trans.rows,gray_trans.step,QImage::Format_Indexed8);
    //display the image in the window
    ui->show_img->setPixmap(QPixmap::fromImage(GrayImg));
    //calculate histogram
    Mat res = drawHist(gray_trans);
    namedWindow("Contrast Transformation Histogram", WINDOW_NORMAL);
    imshow("Contrast Transformation Histogram",res);
}

//ordered dithering implementation
void MainWindow::orderDither(int msize){
    //Mat matrix2 = (Mat_<unsigned char>(2,2)<< 0,2,3,1);
    //Mat matrix4 = (Mat_<unsigned char>(4,4)<< 0.8,2,10,12,4,14,6,3,11,1,9,15,7,13,5);
    //Mat matrix8 = (Mat_<unsigned char>(8,8)<< 0,32,8,40,2,34,10,42,48,16,56,24,50,18,58,26,12,44,4,36,14,46,6,38,60,28,52,20,62,30,54,22,3,35,11,43,1,33,9,41,51,19,59,27,49,17,57,25,15,47,7,39,13,45,5,37,63,31,55,23,61,29,53,21);
    int matrix2[2][2] = {{0,2},{3,1}};
    int matrix4[4][4] = {{0,8,2,10},{12,4,14,6},{3,11,1,9},{15,7,13,5}};
    int matrix8[8][8] = {{0,32,8,40,2,34,10,42},{48,16,56,24,50,18,58,26},{12,44,4,36,14,46,6,38},{60,28,52,20,62,30,54,22},{3,35,11,43,1,33,9,41},{51,19,59,27,49,17,57,25},{15,47,7,39,13,45,5,37},{63,31,55,23,61,29,53,21}};
    ui->show_img->clear();
    //load the current img
    Mat gray;
    //read in the grayscale image
    gray = imread(ImgnameinChar,0);
    Mat gray_temp = gray.clone();
    int temp2 = 256/5;
    int temp4 = 256/17;
    int temp8 = 256/65;
    switch(msize){
    case 2 :

        for(int i=0; i<gray.rows;i++){
            for(int j=0; j<gray.cols;j++){
                gray_temp.at<unsigned char>(i,j) = (gray.at<unsigned char>(i,j)/temp2);
            }
        }
        for(int i=0; i<gray_temp.rows;i++){
            for(int j=0;j<gray_temp.cols;j++){
                //transform image location to dithering matrix location
                int x = i%msize;
                int y = j%msize;
                if(gray_temp.at<unsigned char>(i,j) <= matrix2[x][y]){
                    gray_temp.at<unsigned char>(i,j) = 0;
                }
                else{
                    gray_temp.at<unsigned char>(i,j) = 255;
                }
            }
        }
        break;
    case 4 :
        for(int i=0; i<gray.rows;i++){
            for(int j=0; j<gray.cols;j++){
                gray_temp.at<unsigned char>(i,j) = (gray.at<unsigned char>(i,j)/temp4);
            }
        }
        for(int i=0; i<gray_temp.rows;i++){
            for(int j=0;j<gray_temp.cols;j++){
                //transform image location to dithering matrix location
                int x = i%msize;
                int y = j%msize;
                if(gray_temp.at<unsigned char>(i,j) <= matrix4[x][y]){
                    gray_temp.at<unsigned char>(i,j) = 0;
                }
                else{
                    gray_temp.at<unsigned char>(i,j) = 255;
                }
            }
        }
        break;
    case 8 :
        for(int i=0; i<gray.rows;i++){
            for(int j=0; j<gray.cols;j++){
                gray_temp.at<unsigned char>(i,j) = (gray.at<unsigned char>(i,j)/temp8);
            }
        }
        for(int i=0; i<gray_temp.rows;i++){
            for(int j=0;j<gray_temp.cols;j++){
                //transform image location to dithering matrix location
                int x = i%msize;
                int y = j%msize;
                if(gray_temp.at<unsigned char>(i,j) <= matrix8[x][y]){
                    gray_temp.at<unsigned char>(i,j) = 0;
                }
                else{
                    gray_temp.at<unsigned char>(i,j) = 255;
                }
            }
        }
        break;
    default :
       QMessageBox::information(NULL,NULL,tr("Please input a valid number from {2,4,8}!"));
    }
    QImage ditImg((const unsigned char*)gray_temp.data,gray_temp.cols,gray_temp.rows,gray_temp.step,QImage::Format_Indexed8);
    ui->show_img->setPixmap(QPixmap::fromImage(ditImg));
}


//button logic
//load and show button
void MainWindow::on_show_clicked(){
    loadandShowImg();
}
//reset button
void MainWindow::on_reset_clicked(){
    ui->show_img->clear();
}
//grayscale button
void MainWindow::on_gray_clicked(){
    toGrayscale();
}

//grayscale histogram button
void MainWindow::on_histgray_clicked(){
    drawGrayHist();
}

//gamma histogram button
void MainWindow::on_histgamma_clicked(){
    QString input = ui->gamma_val->text();
    double input_d = input.toDouble();
    drawGammaHist(input_d);
}

//negative transformation histogram button
void MainWindow::on_negative_clicked(){
    negativeHist();
}

//contrast transformation histogram button
void MainWindow::on_contrast_clicked(){
    QString bright = ui->brightness_val->text();
    QString contrast = ui->contrast_val -> text();
    double bright_d = bright.toDouble();
    double contrast_d = contrast.toDouble();
    contrastHist(bright_d,contrast_d);
}

//ordered dithering button
void MainWindow::on_dither_clicked()
{
    QString size = ui->matrix_size->text();
    int size_i = size.toInt();
    orderDither(size_i);
}
//quit button
void MainWindow::on_quit_clicked()
{
    QCoreApplication::exit(0);
}

