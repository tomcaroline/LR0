#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analyproc.h"
#include "alldlg.h"
#include "painttree.h"
#include "onedlg.h"
#include "introdlg.h"
#include "weima.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    ui->setupUi(this);
    //Grammar *g=new Grammar;//语法分析类
    createToolBar();
    ui->tableWidget->setSpan(0,1,1,6);//合并单元格
    ui->tableWidget->setSpan(0,7,1,9);//合并单元格
    ui->tableWidget->setSpan(0,0,2,1);//合并单元格
//    ui->allStepButton->setStyleSheet("background-color: red;\
//                                     border-style: outset;\
//                                     border-width: 2px;\
//                                     border-color: beige;");
    QTableWidgetItem *tempAction=new QTableWidgetItem;
    QTableWidgetItem *tempGoto=new QTableWidgetItem;
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("状态"));
    tempAction->setText(tr("ACTION"));
    tempAction->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter); //居中显示
    ui->tableWidget->setItem(0,1,tempAction);
    tempGoto->setText(tr("GOTO"));
    tempGoto->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(0,7,tempGoto);
    connect(ui->oneStepButton,SIGNAL(clicked()),this,SLOT(slotOneStep()));//创建单步生成按钮的点击响应
    connect(ui->allStepButton,SIGNAL(clicked()),this,SLOT(slotAllStep()));//创建单步生成按钮的点击响应
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete m_g;
//    delete m_a;
//    delete m_t;
}

void MainWindow::createActions()
{
    exitAction=new QAction(QIcon(":/image/exit.ico"),tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setToolTip(tr("退出软件"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    aboutAction=new QAction(QIcon(":/image/about.ico"),tr("帮助"),this);
    aboutAction->setShortcut(tr("Ctrl+H"));
    aboutAction->setToolTip(tr("关于本软件"));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(slotAbout()));

    picAction=new QAction(QIcon(":/image/lrpic.ico"),tr("流程图"),this);
    picAction->setToolTip(tr("算法流程图"));
    picAction->setShortcut(tr("Ctrl+P"));
    connect(picAction,SIGNAL(triggered()),this,SLOT(slotPic()));

    pcAction=new QAction(QIcon(":/image/weima.ico"),tr("伪码"),this);
    pcAction->setToolTip(tr("算法的伪码"));
    pcAction->setShortcut(tr("Ctrl+P"));
    connect(pcAction,SIGNAL(triggered()),this,SLOT(slotPC()));
}

void MainWindow::createToolBar()
{
    createActions();
    toolBar=addToolBar(tr("tools"));
    toolBar->setMovable(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBar->addAction(picAction);
    toolBar->addAction(pcAction);
    toolBar->addAction(aboutAction);
    toolBar->addAction(exitAction);
}

void MainWindow::slotAbout()
{
    (new QMessageBox)->about(this,tr("帮助&关于"),tr("LR(0)算法图形化演示系统\n"
                                                 "输入的字符串必须全部为终结符构成.\n"
                                                 "所谓单步生成，是指语法树和分析过程同步执行，而且是一步一步的执行.\n"
                                                 "一步生成就是直接看到语法树和分析过程的最终结果.\n\n"
                                                 "作者:毛勇乐\n"
                                                 "邮件:tomcaroline98@gmail.com\n"));
}

void MainWindow::slotPic()
{
    introDlg dlg;
    dlg.exec();
}

void MainWindow::slotOneStep()
{
    m_g=new Grammar;
    m_a=new analyproc;
    m_t=new treeNode;
    string strInput;
    strInput=ui->inputGsEdit->text().toStdString();
    if(m_g->isInVn(strInput)==false)
    {
        (new QMessageBox)->about(this,tr("error"),tr("你输入的字符串不全为终结符,请重新输入！！！！"));
        return;
    }
    if(strInput.empty())
    {
        (new QMessageBox)->about(this,tr("error"),tr("请输入字符串"));
        return;
    }

    m_a->isLR=m_g->makeProject(strInput,m_a,m_t);//主要函数makeProject;
    tableDlg *tDlg=new tableDlg();
    tDlg->setAnaly(this->m_a);//复制分析步骤表
    tDlg->setTreeNode(this->m_t);//传递节点类将对象复制给tDlg
    (tDlg->getStepTable())->addAll();
}

void MainWindow::slotAllStep()
{
    m_g=new Grammar;//语法分析主函数类
    m_a=new analyproc;
    m_t=new treeNode;
    string strInput;
    strInput=ui->inputGsEdit->text().toStdString();
    if(m_g->isInVn(strInput)==false)
    {
        (new QMessageBox)->about(this,tr("error"),tr("你输入的字符串不全为终结符,请重新输入！！！！"));
        return;
    }
    if(strInput.empty())
    {
        (new QMessageBox)->about(this,tr("error"),tr("请输入字符串"));
        return;
    }
    m_a->isLR=m_g->makeProject(strInput,m_a,m_t);
    tableDlg_one *tDlg=new tableDlg_one();
    tDlg->setAnaly(this->m_a);
    tDlg->setTreeNode(this->m_t);
}

void MainWindow::slotPC()
{
    weima *wm=new weima;
    wm->wmShow();
}
