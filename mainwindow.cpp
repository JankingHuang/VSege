#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("VSege");
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
    outputPath = QFileDialog::getExistingDirectory(this, "请选择文件保存路径...", inputPath);

    ui->le_output_path->setText(outputPath);

}

void MainWindow::on_pushButton_3_clicked()
{

//        int deviceID = 0;             // 0 = open default camera
      int apiID = cv::CAP_ANY;      // 0 = autodetect default API
      capture.open(inputPath.toStdString(), apiID);
      if (!capture.isOpened()) {
          QString dlgTitle="warning 消息框";
             QString strInfo="不能打开视频文件";
             QMessageBox::warning(this, dlgTitle, inputPath);
          }
      double num = 0;
      double sum = capture.get( cv::VideoCaptureProperties::CAP_PROP_FRAME_COUNT);
      while (1)
        {
            capture.read(frame);
            if(frame.empty()){
                break;
            }
            cv::imwrite(outputPath.toStdString() + "/" + std::to_string(num) + ".jpg" ,frame);
            num++;

            ui->progressBar->setValue((num / sum)  * 100);
            ui->progressBar->update();
             qDebug() << "num:" << num << "\t"
                      << "sum:" << sum << "\t"
                     << "num / sum: " << (num / sum) * 100 << endl;
            imshow("Live", frame);
            if (cv::waitKey(5) >= 0)
                       break;

        }
      QMessageBox::information(this,"提示","视频转化成功");

}
