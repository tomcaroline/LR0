/*
分析过程表的控件
*/

#include "steptable.h"

int steptable::iCount;
steptable::steptable(QWidget *parent) :
    QTableWidget(parent)
{

}

void steptable::setTable()
{
    this->setRowCount(0);
    this->setColumnCount(6);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this-> setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->verticalHeader()->setVisible(false); //隐藏行表头
    QStringList header;
    header<<"步骤"<<"状态栈"<<"符号栈"<<"输入串"<<"ACTION"<<"GOTO";
    this->setHorizontalHeaderLabels(header);
}

void steptable::addAll()
{
    analyproc *anIn;
    anIn=this->analy;
    vector<string> oneLine;
    iCount=0;
    while(iCount<anIn->row)
    {
        oneLine=anIn->getRow(iCount);
        this->insertRow(iCount);
        for(int i=0;i<6;i++)//循环输出一行表格
        {
            QTableWidgetItem *item=new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            item->setText(QString::fromStdString(oneLine[i]));
            item->setTextColor(QColor(0,0,0));
            QFont blodText;//
            blodText.setBold(true);//set text to blod
            blodText.setPixelSize(15);
            item->setFont(blodText);
            this->setItem(iCount,i,item);
        }
        iCount++;
    }
//    else
//    {
        if(anIn->isLR==false)
        {
            (new QMessageBox)->about(this,tr("error"),tr("你输入的字符串不符合文法"));
//            this->nextButton->setDisabled(true);
        }
        else
        {
            (new QMessageBox)->about(this,tr("OK"),tr("你输入的字符串符合文法"));
//            this->nextButton->setDisabled(true);
        }
        //    }
}

void steptable::setAnaly(analyproc *anIn)
{
    this->analy=anIn;
}


void steptable::setWidth(int iWidth)
{
    for(int i=0;i<6;i++)
    {
//        stepTable->resize(QSize(iWidth,iHeight));
        this->setColumnWidth(i,iWidth/6);
    }
}
