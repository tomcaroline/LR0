#include "steptable_one.h"

int steptable_one::iCount;

steptable_one::steptable_one(QWidget *parent) :
    QTableWidget(parent)
{
    endTable=false;
    startTable=false;
}

void steptable_one::setTable()
{
    this->setRowCount(0);
    this->setColumnCount(6);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->verticalHeader()->setVisible(false); //隐藏行表头
    QStringList header;
    header<<"步骤"<<"状态栈"<<"符号栈"<<"输入串"<<"ACTION"<<"GOTO";
    this->setHorizontalHeaderLabels(header);
}

void steptable_one::addARow()
{
    analyproc *anIn;
    anIn = this->analy;
    vector<string> oneLine;
    iCount=this->rowCount();
    if(iCount < anIn->row)
    {
        oneLine=anIn->getRow(iCount);
        this->insertRow(iCount);
        for(int i=0;i<6;i++)//循环输出一行表格
        {
            QTableWidgetItem *item=new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            item->setText(QString::fromStdString(oneLine[i]));
            item->setTextColor(QColor(0,0,0));//black
            QFont blodText;//
            blodText.setBold(true);//加粗字体
            blodText.setPixelSize(15);
            item->setFont(blodText);
            this->setItem(iCount,i,item);
        }
//        iCount=this->rowCount();
    }
    else
    {
        if(anIn->isLR==false)
        {
            (new QMessageBox)->about(this,tr("error"),tr("你输入的字符串不符合文法"));
//            ->nextButton->setDisabled(true);
            endTable=true;

        }
        else
        {
            (new QMessageBox)->about(this,tr("OK"),tr("你输入的字符串符合文法"));
            //paint->update();
//            this->nextButton->setDisabled(true);
            endTable=true;
        }
        iCount=this->rowCount()-1;//内部是从0开始的，而表格是从1开始的
    }
}

void steptable_one::delARow()
{
    this->removeRow(iCount);
    iCount -= 1;
    if(iCount==-1)
        startTable=true;
}

void steptable_one::setAnaly(analyproc *anIn)
{
    this->analy=anIn;
}

void steptable_one::setWidth(int iWidth)
{
    for(int i=0;i<6;i++)
    {
        this->setColumnWidth(i,iWidth/6);
    }
}

int steptable_one::getICount()
{
    return this->iCount;
}

bool steptable_one::isEnd()
{
    return endTable;
}

bool steptable_one::isStart()
{
    return startTable;
}

void steptable_one::setEnd(bool eflag)
{
    this->endTable=eflag;
}

void steptable_one::setStart(bool sflag)
{
    this->startTable=sflag;
}

//void steptable_one::setButtonTF(QPushButton *button, bool flag)
//{
//    button->setDisabled(flag);
//}
