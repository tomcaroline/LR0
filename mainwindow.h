#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMessageBox>
#include "grammar.h"
#include <QMenu>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions(); //创建监听动作
    void createToolBar(); //创建工具栏

private:
    Ui::MainWindow *ui;
    Grammar *m_g;
    analyproc *m_a;
    treeNode *m_t;
    QToolBar *toolBar;
    QAction *exitAction;  //退出
    QAction *aboutAction;  //帮助
    QAction *picAction; //流程图
    QAction *pcAction;
public slots:
    void slotAbout(); //帮助信号槽
    void slotOneStep();//单步生成按钮
    void slotAllStep();//一步生成按钮
    void slotPic();//
    void slotPC();
};

#endif // MAINWINDOW_H
