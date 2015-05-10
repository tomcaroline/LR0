#include "introdlg.h"

introDlg::introDlg(QWidget *parent) :
    QDialog(parent)
{
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->resize(855,710);
    this->setFixedSize(855,710);
    this->setWindowTitle(tr("算法流程图"));
    this->drawPic(tr(":/LR.jpeg"));
     this->show();
}

void introDlg::drawPic(QString srcPic) //贴图
{
    this->img =new QPixmap(srcPic);
    this->imgLabel=new QLabel();
    imgLabel->setPixmap(*img);
    this->layout = new QVBoxLayout();
    this->area = new QScrollArea(this);
    area->setWidget(imgLabel);
    this->setLayout(layout);
    layout->addWidget(area);
//    this->img->load(srcPic);
//    imgLabel->setPixmap(QPixmap::fromImage(*img));

}
