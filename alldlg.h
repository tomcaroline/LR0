#ifndef TABLEDLG_H
#define TABLEDLG_H
#include "analyproc.h"
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include "treenode.h"
#include "painttree.h"
#include "steptable.h"

class tableDlg : public QDialog
{
    Q_OBJECT
public:
    explicit tableDlg(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
//    void setTable();
//    void addAll();
    void setAnaly(analyproc *anIn);
    void setTreeNode(treeNode *tree);
//    void delARow();
    steptable *getStepTable();

private:
    int iWidth;
//    int iHeight;
    treeNode *tree;
    paintTree *paint;
    QGridLayout *layout;
    QLabel *treeLabel;
    QLabel *stepLabel;
    QTextEdit *text;
    steptable *stepTable;

//    QTableWidget *stepTable;
//    QPushButton *prevButton;
//    QPushButton *nextButton;//下一步按钮
//    analyproc *analy;//保存分析步骤的对象
//    static int iCount;//当前表格行数
};

#endif // TABLEDLG_H
