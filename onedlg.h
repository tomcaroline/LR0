#ifndef TABLEDLG_ONE_H
#define TABLEDLG_ONE_H
#include "analyproc.h"
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include "treenode.h"
#include "painttree_one.h"
#include "steptable_one.h"
class tableDlg_one : public QDialog
{
    Q_OBJECT
public:
    explicit tableDlg_one(QDialog *parent = 0);
    void resizeEvent(QResizeEvent *event);
//    void setTable();
//    void addARow(analyproc *anIn);
    void setAnaly(analyproc *anIn);
    void setTreeNode(treeNode *tree);
//    void delARow();
signals:

public slots:
    void slotNextButton();
    void slotPrevButton();
private:
    int iWidth;
    int iHeight;
    treeNode *tree;
    paintTree_one *paint;
    QGridLayout *layout;
    QLabel *treeLabel;
    QLabel *stepLabel;
    QTextEdit *text;
//    QTableWidget *stepTable;
    steptable_one *stepTable;
    QPushButton *prevButton;
    QPushButton *nextButton;//下一步按钮
    analyproc *analy;//保存分析步骤的对象
    static int iCount;//当前表格行数
};

#endif // TABLEDLG_ONE_H
