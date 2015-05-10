#include "alldlg.h"
#include <QMessageBox>
#include "painttree.h"
//int tableDlg::iCount;
tableDlg::tableDlg(QWidget *parent) :
    QDialog(parent)
{
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(Qt::Widget);
    treeLabel = new QLabel(tr("生成树"));
    stepLabel = new QLabel(tr("分析过程"));
//    stepTable = new QTableWidget;
//    text=new QTextEdit();
    paint=new paintTree;
    stepTable = new steptable;
    layout=new QGridLayout(); //创建网格布局
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    this->setLayout(layout);
//    prevButton = new QPushButton(QIcon(":/image/prev.ico"),tr("上一步"));
//    connect(prevButton,SIGNAL(clicked()),this,SLOT(slotPrevButton()));
//    nextButton = new QPushButton(QIcon(":/image/next.ico"),tr("下一步"));
//    connect(nextButton,SIGNAL(clicked()),this,SLOT(slotNextButton()));
    layout->addWidget(treeLabel,0,0,Qt::AlignHCenter);
    layout->addWidget(stepLabel,0,1,Qt::AlignHCenter);
    layout->addWidget(paint,1,0);
    layout->addWidget(stepTable,1,1);
//    layout->addWidget(prevButton,2,0,Qt::AlignHCenter);
//    layout->addWidget(nextButton,2,1,Qt::AlignHCenter);
    stepTable->setTable();
    this->resize(900,600);
    this->show();
}

void tableDlg::resizeEvent(QResizeEvent *event)
{
    iWidth=stepTable->width();
    stepTable->setWidth(iWidth);
}


void tableDlg::setAnaly(analyproc *anIn) //复制analyproc对象给当前类
{
//    this->analy=anIn;
    stepTable->setAnaly(anIn);
}

void tableDlg::setTreeNode(treeNode *tree)
{
    this->tree=tree;
    this->paint->setTreeNode(this->tree);//暂时不用
}

steptable *tableDlg::getStepTable()
{
    return this->stepTable;
}


