#ifndef PAINTTREE_ONE_H
#define PAINTTREE_ONE_H

#include "treenode.h"
#include <QWidget>
#include <QRect>
#include <QFrame>

class paintTree_one : public QFrame
{
    Q_OBJECT
public:
    explicit paintTree_one(QWidget *parent = 0);
    QString charToName(char &cCh);//将字母转化为可用的资源路径
    void setTreeNode(treeNode *t);//设置图的节点
    void paintNext();
    void findXY(const char cCh, int &x, int &y);
protected:
        void paintEvent(QPaintEvent *event);
        void resizeEvent(QResizeEvent *event);
private:
        int iWidth;
        int iHeight;
        treeNode *m_tree;
public:
        static int iCount;

signals:

public slots:

};

#endif // PAINTTREE_ONE_H
