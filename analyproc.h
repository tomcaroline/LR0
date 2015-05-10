#ifndef ANALYPROC_H
#define ANALYPROC_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class analyproc
{
public:
    analyproc();
public:
    int row;
    vector<int> iStep;//步骤数组
    vector<string> sStatus;//状态栈数组
    vector<string> sSysmbol;//符号串数组
    vector<string> sInput;//输入串数组
    vector<string> sAction;//Action数组
    vector<int> iGoto;//goto数组
    vector<string> getRow(int i);
    bool isLR;
};

#endif // ANALYPROC_H
