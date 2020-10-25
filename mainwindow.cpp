#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//        //toAscii()返回8位描述的string,为QByteArray,data()表示返回QByteArray的指针，QByteArray为字节指针
//        cv::Mat src = cv::imread( img_name.toUtf8().data(),1);
//    cv::imshow("My Image", src);
//    cv::waitKey(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    inputPath = QFileDialog::getOpenFileName( this, tr("Open Video"), ".",
                                                         tr("Image Files(*.mp4 *.avi *.jpeg *.bmp)"));
    ui->le_input_path->setText(inputPath);

}

void MainWindow::on_pushButton_2_clicked()
{
    inputPath = QFileDialog::getExistingDirectory(this, "请选择文件保存路径...", "./");

    ui->le_output_path->setText(inputPath);

}

void MainWindow::on_pushButton_3_clicked()
{
//        int deviceID = 0;             // 0 = open default camera
      int apiID = cv::CAP_ANY;      // 0 = autodetect default API
      capture.open(inputPath, apiID);
      if (!capture.isOpened()) {
          QString dlgTitle="warning 消息框";
             QString strInfo="不能打开视频文件";
             QMessageBox::warning(this, dlgTitle, strInfo);
          }
      while (1)
        {
            capture.read(frame);
            imshow("Live", frame);
            if (cv::waitKey(5) >= 0)
                break;
        }

}
