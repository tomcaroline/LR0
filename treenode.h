/*
此文件是节点坐标和节点值保存的类,将树图看做二维数组,只需将坐标同时扩大几倍就可以形成美丽的树状图

*/

#ifndef TREENODE_H
#define TREENODE_H
#include <vector>
#include <iostream>
using namespace std;
struct Node{
    int x;//节点X坐标
    int y;//节点Y坐标
    char key;//节点值
};
class treeNode
{
public:
    treeNode();
public:
    vector<Node> tree;//存储节点信息的栈
};

#endif // TREENODE_H
