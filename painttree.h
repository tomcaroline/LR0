#ifndef PAINTTREE_H
#define PAINTTREE_H
#include "treenode.h"
#include <QWidget>
#include <QRect>
#include <QPen>
#include <QFrame>

class paintTree : public QFrame
{
    Q_OBJECT
public:
    explicit paintTree(QWidget *parent = 0);
    QString charToName(char &cCh);//将字母转化为可用的资源路径
    void setTreeNode(treeNode *t);//设置图的节点
    void paintAll();//画图函数
    void findXY(const char cCh, int &x, int &y);//找到节点值所在的坐标X,Y
protected:
        void paintEvent(QPaintEvent *event);
        void resizeEvent(QResizeEvent *event);
private:
        treeNode *m_tree;
        int iWidth;
        int iHeight;
        static int iCount;

};

#endif // PAINTTREE_H
