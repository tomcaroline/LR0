#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "analyproc.h"
#include "treenode.h"
using namespace std;
#define VN_LENGTH 5
#define GS_LENGTH 4
#define TABLE_ROW 10
#define TABLE_COLUMN 9

class Grammar
{
public:
    Grammar();
    bool isInVn(string &str);
    int charToInt(char &c);
    int getGoto(int iStatus,char cChar);
    string getAction(int iStatus,char cChar);
    char getGsLeft(int iNum);
    string getGsRight(int iNum);
    int getGsLength(int iNum);
    bool makeProject(string input,analyproc *anIn,treeNode *tNode);
    void copyStatus(vector<string> &out,vector<int> in); //保存状态栈
    void copySymbol(vector<string> &out,vector<char> in);//保存字符栈
    void copyInput(vector<string> &out,string in,int iCount); //保存剩余字符串
//    void operator delete(Grammar &g);
private:
    vector<int> iStatus;//状态栈
    vector<char> cSymbol;//符号栈
    string input;//输入串
    char m_Vn[VN_LENGTH]={'a','b','c','d','e'};//初始化终结符
    /* 初始化文法G[s]*/
    string m_Gs[GS_LENGTH]={"S->aAcBe","A->b","A->Ab","B->d"};
    /*存储LR(0)分析表，大于10为归约，小于0为进栈，0表示出错，1到10表示状态转移，100表示接受*/
    string m_Table[TABLE_ROW][TABLE_COLUMN]={
        {"S2","0","0","0","0","0","1","0","0"},
        {"0","0","0","0","0","acc","0","0","0"},
        {"0","0","0","S4","0","0","0","3","0"},
        {"0","S5","0","S6","0","0","0","0","0"},
        {"r2","r2","r2","r2","r2","r2","0","0","0"},
        {"0","0","0","0","S8","0","0","0","7"},
        {"r3","r3","r3","r3","r3","r3","0","0","0"},
        {"0","0","S9","","0","0","0","0","0"},
        {"r4","r4","r4","r4","r4","r4","0","0","0"},
        {"r1","r1","r1","r1","r1","r1","0","0","0"}
    };
};

#endif // GRAMMAR_H
