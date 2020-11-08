#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("VSege");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  inputPath = QFileDialog::getOpenFileName(
      this, tr("Open Video"), ".", tr("Image Files(*.mp4 *.avi *.jpeg *.bmp)"));
  ui->le_input_path->setText(inputPath);
}

void MainWindow::on_pushButton_2_clicked() {
  outputPath = QFileDialog::getExistingDirectory(this, "请选择文件保存路径...",
                                                 inputPath);

  ui->le_output_path->setText(outputPath);
}

void MainWindow::on_pushButton_3_clicked() {

  bool ok;
  timeOut = ui->le_timeout->text().toInt(&ok, 10);
  qDebug() << "TimeOut:" << timeOut << endl;
  //        int deviceID = 0;             // 0 = open default camera
  int apiID = cv::CAP_ANY; // 0 = autodetect default API
  capture.open(inputPath.toStdString(), apiID);
  if (!capture.isOpened()) {
    QString dlgTitle = "warning 消息框";
    QString strInfo = "不能打开视频文件";
    QMessageBox::warning(this, dlgTitle, inputPath);
  }
  int num = 0;
  double sum = capture.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_COUNT);
  double fps = capture.get(cv::VideoCaptureProperties::CAP_PROP_FPS);
  qDebug() << "Sum:" << sum << endl << "Fps:" << fps << endl;
  double timeLength = sum / fps;
  int index = 0;
  if (timeOut > 0) {
    qDebug() << "sum judg:"<<timeOut * fps * index << endl;
    while (timeOut * fps * index < sum) {

      capture.set(cv::VideoCaptureProperties::CAP_PROP_POS_FRAMES,
                  timeOut * fps * index);
      capture.read(frame);
      if(frame.empty()){
          break;
      }
      cv::imwrite(outputPath.toStdString() + "/" + std::to_string(num) + ".jpg",
                     frame);
         num++;
         index++;
         qDebug() << "index:" << index <<endl
                  <<"num:" << num << endl;


      imshow("Live", frame);
      if (cv::waitKey(5) >= 0){
          break;
      }
    }

  } else {
    while (1) {
      capture.read(frame);
      if (frame.empty()) {
        break;
      }

      cv::imwrite(outputPath.toStdString() + "/" + std::to_string(num) + ".jpg",
                     frame);
      num++;

      ui->progressBar->setValue((num / sum) * 100);
      ui->progressBar->update();
      qDebug() << "num:" << num << "\t"
               << "sum:" << sum << "\t"
               << "num / sum: " << (num / sum) * 100 << endl;
      imshow("Live", frame);
      if (cv::waitKey(5) >= 0){
          break;
      }
    }
  }

  QMessageBox::information(this, "提示", "视频转化成功");
}

void MainWindow::on_bt_set_timeout_clicked() {
  bool ok;
  timeOut = ui->le_timeout->text().toInt(&ok, 10);
  qDebug() << "TimeOut:" << timeOut << endl;
}
