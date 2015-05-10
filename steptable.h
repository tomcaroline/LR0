#ifndef STEPTABLE_H
#define STEPTABLE_H

#include <QTableWidget>
#include <QStringList>
#include <QHeaderView>
#include <QMessageBox>
#include "analyproc.h"

class steptable : public QTableWidget
{

public:
    explicit steptable(QWidget *parent = 0);
    void setTable();
    void addAll();
    void setAnaly(analyproc *anIn);
    void setWidth(int iWidth);
//    void setTreeNode(treeNode *tree);
private:
    analyproc *analy;//保存分析步骤的对象
    static int iCount;//当前表格行数
};

#endif // STEPTABLE_H
