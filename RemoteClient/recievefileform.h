#ifndef RECIEVEFILEFORM_H
#define RECIEVEFILEFORM_H

#include <QWidget>
#include <QTime>

namespace Ui {
class RecieveFileForm;
}

class RecieveFileForm : public QWidget {
    Q_OBJECT

  public:
    explicit RecieveFileForm(QString filename,QString filesize,int blockSize,int fileMaxBlock,QWidget *parent = nullptr);
    ~RecieveFileForm();
    void setCurrentBlock(int currentBlock);

    void finishDownload();

  private:
    Ui::RecieveFileForm *ui;
    QString filesize;
    int blockSize;
    QString sizeDownloaded;
    QTime startDownloadTime;
};

#endif // RECIEVEFILEFORM_H
