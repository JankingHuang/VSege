#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString img_name = QFileDialog::getOpenFileName( this, tr("Open Image"), ".",
                                                         tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
        //toAscii()返回8位描述的string,为QByteArray,data()表示返回QByteArray的指针，QByteArray为字节指针
        cv::Mat src = cv::imread( img_name.toUtf8().data(),1);
    cv::imshow("My Image", src);
    cv::waitKey(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

