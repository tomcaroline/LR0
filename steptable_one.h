#ifndef STEPTABLE_ONE_H
#define STEPTABLE_ONE_H

#include <QTableWidget>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include <QPushButton>
#include <QHeaderView>
#include "analyproc.h"

class steptable_one : public QTableWidget
{

public:
    explicit steptable_one(QWidget *parent = 0);
    void setTable();
    void addARow();
    void delARow();
    void setAnaly(analyproc *anIn);
    void setWidth(int iWidth);
    int getICount();
    bool isEnd();//结束表格
    bool isStart();//起始表格
    void setEnd(bool eflag);
    void setStart(bool sflag);
//    void setButtonTF(QPushButton *button,bool flag);
//    void setTreeNode(treeNode *tree);
private:
    analyproc *analy;//保存分析步骤的对象
    static int iCount;//当前表格行数
    bool endTable;
    bool startTable;
};

#endif // STEPTABLE_ONE_H
