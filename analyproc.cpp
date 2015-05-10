/*
此文件函数用于保存生成的步骤表，getRow(int)函数返回表中指定行的数据

*/
#include "analyproc.h"
#include <stdio.h>
analyproc::analyproc()
{
    this->row=0;
}

vector<string> analyproc::getRow(int i)// 获得表格的一行数据
{

    vector<string> temp;
//    if(iStep.empty())
//        temp.push_back(NULL);
//    else
//    {
        string sTemp;
        char str[3];
        sprintf(str,"%d",iStep[i]);
        sTemp.append(str);
        temp.push_back(sTemp);
        temp.push_back(sStatus[i]);
        temp.push_back(sSysmbol[i]);
        temp.push_back(sInput[i]);
        temp.push_back(sAction[i]);
        if(iGoto[i]==0)
            temp.push_back("");
        else
        {
            sprintf(str,"%d",iGoto[i]);
            sTemp.clear();
            sTemp.append(str);
            temp.push_back(sTemp);
        }
//    }
    return temp;
}

