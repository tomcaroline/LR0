#include "weima.h"

weima::weima(QWidget *parent) :
    QDialog(parent)
{
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->resize(480,320);
    this->setFixedSize(480,320);
    this->setWindowTitle(tr("算法伪代码"));
    this->show();
}

void weima::wmShow()
{
    this->vLayout = new QVBoxLayout;
    this->wmLabel = new QLabel;
    this->wmArea = new QScrollArea;
    wmLabel->setText(tr("LR算法伪代码:\n\n\
                        \n 置ip指向输入串π的第一个符号\
                        \n 令S为栈顶状态\
                        \n a是ip指向的符号\
                        \n 重复 begin\
                        \n      if  ACTION[S，a]=Sj\
                        \n          then   begin  PUSH j，a	 //进栈\
                        \n              p 前进	 //指向下一输入符号\
                        \n          end\
                        \n      else if ACTION[S，a]=rj  //第j条产生式为A*π\
                        \n          then begin\
                        \n              pop  |π|  项\
                        \n              令当前栈顶状态为S’\
                        \n              push GOTO[S’，A]和A	//进栈\
                        \n          end\
                        \n      else if ACTION[S，a]=acc\
                        \n          then return (成功)\
                        \n      else error\
                        \n          end."));
            wmArea->setWidget(wmLabel);
             this->setLayout(vLayout);
            vLayout->addWidget(wmArea);
}
