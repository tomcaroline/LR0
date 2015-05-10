/**
 * LR0语法分析的主要文件，列出了所有分析过程的函数
 */

#include "grammar.h"
#include "analyproc.h"
#include "treenode.h"
Grammar::Grammar()
{

}

bool Grammar::isInVn(string &str) //判断输入串是否全为为终结符
{
    bool flag;
    for(int i=0;i<str.length();i++)
    {
        flag=false;
        for(int j=0;j<VN_LENGTH;j++)
        {
            if(m_Vn[j]==str.at(i))
            {
                flag=true;
                break;
            }
        }
        if(flag==false)
            return false;
    }
    return true;
}

int Grammar::charToInt(char &c) //将字符转化为可用的二维数组下标
{
    int iTemp;
    switch(c)
    {
        case 'a':
            iTemp=0;break;
        case 'c':
            iTemp=1;break;
        case 'e':
            iTemp=2;break;
        case 'b':
            iTemp=3;break;
        case 'd':
            iTemp=4;break;
        case '#':
            iTemp=5;break;
        case 'S':
            iTemp=6;break;
        case 'A':
            iTemp=7;break;
        case 'B':
            iTemp=8;break;
    }
    return iTemp;
}

int Grammar::getGoto(int iStatus, char cChar) //获得Goto表的字符
{
    int iTemp;
    iTemp=charToInt(cChar);
    iTemp=atoi(&m_Table[iStatus][iTemp].at(0));
    return iTemp;
}

string Grammar::getAction(int iStatus, char cChar) //获得Action表的字符串
{
    string sTemp;
    int iTemp;
    iTemp=charToInt(cChar);
    sTemp=m_Table[iStatus][iTemp];
    return sTemp;
}

char Grammar::getGsLeft(int iNum) //获得文法左边字符
{
    char cTemp;
    cTemp=m_Gs[iNum-1].at(0);
    return cTemp;
}

string Grammar::getGsRight(int iNum)//获得文法右部字符串
{
    string sTemp;
    sTemp=m_Gs[iNum].substr(3,m_Gs[iNum].length()-1);
    return sTemp;
}

int Grammar::getGsLength(int iNum)//获得文法右部长度
{
    string sTemp;
    sTemp=m_Gs[iNum-1].substr(3,m_Gs[iNum-1].length()-1);
    return sTemp.length();
}
/*生成步骤表的函数，特别重要
 * 返回true说明输入串符合此文法
 * 否则返回false不符合文法
 * 将分析过程每一列保存到analyproc类中
 * 在这里我们将树的图看做是一个二维数组一样,保存坐标和节点值
*/
bool Grammar::makeProject(string input,analyproc *anIn,treeNode *tNode)//生成分析过程表和树图坐标
{
    int status;//状态栈栈顶元素
    int i=0;//移近时移近的次数
    int iStep=0;//步骤
    int iCount=0;//相同的规约次数
    int centerS=0;//‘S’保存居中显示
    char cinput;//保存输入串
    char csymbol;//非终结符
    int prevStatus=0;//上一次状态栈尾
    int tree_x=0;//坐标X
    int tree_y=0;//坐标Y
    Node nTemp;
    string action;//Action字符串
    string inTemp;//保存剩余字符串
    bool bFlags=true;
    bool isLr=false;
    input.push_back('#'); //输入串末尾添加＃
    iStatus.push_back(0);
    cSymbol.push_back('#');
    inTemp=input;
    while(bFlags)
    {
        status=iStatus.back();
        cinput=input.at(i);
        copyInput(anIn->sInput,inTemp,i);
        action=getAction(status,cinput);
        if(action.at(0)=='0')
            anIn->sAction.push_back("");//存储Action列
        else
            anIn->sAction.push_back(action);//存储Action列
        copyStatus(anIn->sStatus,iStatus);//保存状态栈
        copySymbol(anIn->sSysmbol,cSymbol);//保存符号栈

//        if(action.at(0)=='0')
//        {
//            return false;
//        }
//        status=atoi(&action.at(1));
        switch(action.at(0))
        {
            case '0'://说明字符串不符合文法
                iStep++;
                anIn->iStep.push_back(iStep);
                anIn->iGoto.push_back(0);
                anIn->row=iStep;
                nTemp.x=tree_x+1;
                nTemp.y=0;
                nTemp.key=cinput;
                tNode->tree.push_back(nTemp);
                bFlags=false;
                isLr=false;
                break;
            case 'S'://移进
                status=atoi(&action.at(1));
                iStatus.push_back(status);
                if(cSymbol.back()!='#')
                    tree_x++;
                cSymbol.push_back(cinput);
                nTemp.key=cSymbol.back();//存储节点值
                i++;
                iStep++;
                anIn->iGoto.push_back(0);
                anIn->iStep.push_back(iStep);
                anIn->row=iStep;
                nTemp.x=tree_x;//节点坐标X
                nTemp.y=0;//终结符坐标都应该为0
                tNode->tree.push_back(nTemp);
                if(nTemp.key=='c')
                    centerS=nTemp.x;
                break;
            case 'r'://规约
                status=atoi(&action.at(1));
                csymbol=getGsLeft(status);
                nTemp.key=csymbol;
/*
 * 下面这个switch使树图的坐标标准化
*/
                switch(status)
                {
                    case 1:
                        tree_y=0;
                        tree_y+=3+iCount;
                        nTemp.y=tree_y;
                        tree_x++;
                        break;
                    case 2:
                        tree_y=0;
                        tree_y+=1;
                        nTemp.y=tree_y;
                        break;
                    case 3://由于此文法表达试可能出现循环,必须将其简单化,转为标准坐标,否则为一条线上
                        if(prevStatus==3)
                        {
                            iCount++;
                            tree_y++;
                        }
                        else
                        {
                            tree_y=0;
                            tree_y+=2;
                        }
                        nTemp.y=tree_y;
                        break;
                    case 4:
                        tree_y=0;
                        tree_y+=2;
                        nTemp.y=tree_y;
                        break;
                }
                if(nTemp.key=='S')
                        nTemp.x=centerS;
                else
                    nTemp.x=tree_x;

                tNode->tree.push_back(nTemp);
                if(prevStatus!=status)
                    prevStatus=status;

//                tree_y=0;
                for(int j=0;j<getGsLength(status);j++)
                {
                    iStatus.pop_back();
                    cSymbol.pop_back();
                }
//                status=iStatus.back();

                status=iStatus.back();
                status=getGoto(status,csymbol);
                anIn->iGoto.push_back(status);
                iStatus.push_back(status);
                cSymbol.push_back(csymbol);
                iStep++;
                anIn->iStep.push_back(iStep);
                anIn->row=iStep;

                break;
             case 'a'://接受
//                status=atoi(&action.at(1));
                anIn->iGoto.push_back(0);
                bFlags=false;
                isLr=true;
                iStep++;
                anIn->iStep.push_back(iStep);
                anIn->row=iStep;
                break;
        }
    }
    return isLr;
}
/*
 * 将状态栈当前元素全部存入状态栈列里
*/
void Grammar::copyStatus(vector<string> &out, vector<int> in)//将状态栈整形转为字符串
{
    vector <int>::iterator it;
    string sTemp;
    char cTemp[2];
    for( it= in.begin();it!=in.end();it++)
    {
        sprintf(cTemp,"%d",*it);//格式化字符串
        sTemp.push_back(cTemp[0]);//添加到string末尾
    }
    out.push_back(sTemp);
}
/*
 * 将符号栈当前元素全部存入符号栈列里
*/
void Grammar::copySymbol(vector<string> &out, vector<char> in)
{
    vector <char>::iterator it;
    string sTemp;
    for( it= in.begin();it!=in.end();it++)
    {
        sTemp.push_back((char)*it);
    }
    out.push_back(sTemp);
}
/*
 * 将当前剩余字符串全部存入输入串列里
 * iCount表示前几个字符已经输入，将其删除
 * in表示输入的全部字符串
*/
void Grammar::copyInput(vector<string> &out, string in,int iCount)
{
    string str=in;
    str.erase(0,iCount);
    out.push_back(str);
}

