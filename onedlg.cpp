#include "onedlg.h"
#include <QMessageBox>
#include "painttree_one.h"
int tableDlg_one::iCount;//行计数i
tableDlg_one::tableDlg_one(QDialog *parent) :
    QDialog(parent)
{
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(Qt::Widget);
    treeLabel = new QLabel(tr("生成树"));
    stepLabel = new QLabel(tr("分析过程"));
//    stepTable = new QTableWidget;
//    text=new QTextEdit();
    stepTable = new steptable_one;
    paint=new paintTree_one;
    layout=new QGridLayout(); //创建网格布局
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    this->setLayout(layout);
    prevButton = new QPushButton(QIcon(":/image/prev.ico"),tr("上一步"));
    connect(prevButton,SIGNAL(clicked()),this,SLOT(slotPrevButton()));
    prevButton->setDisabled(true);
    nextButton = new QPushButton(QIcon(":/image/next.ico"),tr("下一步"));
    nextButton->setFocus();
    connect(nextButton,SIGNAL(clicked()),this,SLOT(slotNextButton()));
    layout->addWidget(treeLabel,0,0,Qt::AlignHCenter);
    layout->addWidget(stepLabel,0,1,Qt::AlignHCenter);
    layout->addWidget(paint,1,0);
    layout->addWidget(stepTable,1,1);
    layout->addWidget(prevButton,2,0,Qt::AlignHCenter);
    layout->addWidget(nextButton,2,1,Qt::AlignHCenter);
    stepTable->setTable();
    this->resize(900,600);
    this->show();
}

void tableDlg_one::resizeEvent(QResizeEvent *event)
{
    iWidth=stepTable->width();
//    iHeight=stepTable->height();
//    for(int i=0;i<6;i++)
//    {
//        stepTable->resize(QSize(iWidth,iHeight));
//        stepTable->setColumnWidth(i,iWidth/6);
//    }
    stepTable->setWidth(iWidth);
}



void tableDlg_one::setAnaly(analyproc *anIn) //复制analyproc对象给当前类
{
    this->analy=anIn;
    stepTable->setAnaly(anIn);
}

void tableDlg_one::setTreeNode(treeNode *tree)
{
    this->tree=tree;
    this->paint->setTreeNode(this->tree);//暂时不用
}



void tableDlg_one::slotNextButton()
{
    if(!prevButton->isEnabled())
        prevButton->setDisabled(false);
    stepTable->addARow();
    this->iCount=stepTable->getICount();
    paint->update();//更新画板，刷新语法树图
    paint->iCount=this->iCount-1;
    if(stepTable->isEnd())
    {
        nextButton->setDisabled(true);
        stepTable->setEnd(false);
    }
//    if(this->iCount == this->analy->row-1 )
//        nextButton->setDisabled(true);
}

void tableDlg_one::slotPrevButton()
{
    if(!nextButton->isEnabled())
        nextButton->setDisabled(false);
    stepTable->delARow();
    this->iCount=stepTable->getICount();
    paint->iCount=this->iCount-1;
    paint->update();
    if(stepTable->isStart())
    {
        prevButton->setDisabled(true);
        nextButton->setDisabled(false);
        stepTable->setStart(false);
    }
}
