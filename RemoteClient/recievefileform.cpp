#include "recievefileform.h"
#include "ui_recievefileform.h"

#include <QThread>

RecieveFileForm::RecieveFileForm(QString filename, QString filesize,int blockSize,int fileMaxBlock, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecieveFileForm) {
    ui->setupUi(this);
    ui->finishBt->setHidden(true);
    ui->filenameLb->setText(filename);
    this->filesize = filesize;
    this->blockSize = blockSize;
    ui->downloadedLb->setText(filesize);
    ui->progressBar->setMaximum(fileMaxBlock);
    startDownloadTime = QTime::currentTime();

}

RecieveFileForm::~RecieveFileForm() {
    delete ui;
}
//设置下载进度
void RecieveFileForm::setCurrentBlock(int currentBlock) {
    ui->progressBar->setValue(currentBlock);
    ui->speedLb->setText(QString("%1M/s").arg(
                             ((double)currentBlock*blockSize/1024/1024)/
                             ((QTime::currentTime().msecsSinceStartOfDay()
                               - startDownloadTime.msecsSinceStartOfDay())/1000.0)));
}
//下载完成4s后关闭下载框
void RecieveFileForm::finishDownload() {
    ui->finishBt->setHidden(false);
    ui->finishBt->repaint();
    ui->finishBt->update();
    QThread::sleep(4);
    this->close();

}
