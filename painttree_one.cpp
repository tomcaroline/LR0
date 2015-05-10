#include "painttree_one.h"
#include <QPainter>
#include <QPixmap>

int paintTree_one::iCount;//已经画出的步骤

paintTree_one::paintTree_one(QWidget *parent) :
    QFrame(parent)
{
    this->iCount=-1;
    this->setStyleSheet ("border: 1px solid gray;background-color:white"); //设置边框颜色
//    this->setAutoFillBackground(true);
//    this->setPalette(Qt::white); //背景色为白色
}

void paintTree_one::paintEvent(QPaintEvent *event)
{
    paintNext();//画下一步
}

void paintTree_one::resizeEvent(QResizeEvent *event) //获得子控件大小,随窗口变化而变化
{
    iWidth=this->width();//画图窗口宽度
    iHeight=this->height();//画图窗口高度
    //this->resize(QSize(iWidth,iHeight));
}

QString paintTree_one::charToName(char &cCh)
{
    QString temp;
    if(cCh>='a'&&cCh<='e')
        temp.sprintf(":/image/lowercase/%c.png",cCh);
    else
        temp.sprintf(":/image/uppercase/%c.png",cCh);
    return temp;
}

void paintTree_one::setTreeNode(treeNode *t)
{
    this->m_tree=t;
}

void paintTree_one::paintNext()
{
    vector<Node> nTemp;
    nTemp=this->m_tree->tree;
    int space_x, space_y;
    int lowCount=0;//树中出现终结符的个数，方便计算空间间隔宽度
    int upCount=0;//树中出现终结符的个数，方便计算空间间隔高度
    for(int j=nTemp.size()-1;j>=0;j--)
    {
        if(nTemp[j].y==0)
        {
            lowCount=nTemp[j].x+1;//x坐标从0开始的，所以要加一
            break;
        }
        else
        {
            lowCount=0;
            continue;
        }

    }
    for(int j=nTemp.size()-1;j>=0;j--)
    {
        char temp=nTemp[j].key;
        if(temp=='A' || temp=='B'  || temp=='S' )
        {
            upCount=nTemp[j].y+1; //y坐标从0开始的，所以要加一
            break;
        }
        else
        {
            upCount=0;
            continue;
        }
    }
//    int space_x=iWidth/(lowCount+1);//横向间隔
//    int space_y=iHeight/(upCount+1);//纵向间隔
    space_x=iWidth/(lowCount+1);//横向间隔
    if(upCount==0)
        space_y=iHeight/3;
    else
          space_y=iHeight/(upCount+1);//纵向间隔
    QString fileName;
    QPainter painter;
    //QPen pen;
    //pen.setWidth(2);//设置线的宽度为2个像素
    int currentX;
    int currentY;
    int x,y,nY;
    if(iCount<nTemp.size()&&iCount>=0)
    {
        for(int i=0;i<=iCount;i++)
        {
            painter.begin(this);
            //painter.setPen(pen);
            fileName=charToName(nTemp[i].key);
            currentX=space_x*(nTemp[i].x+1);
            currentY=iHeight-space_y*(nTemp[i].y+1);
            QPixmap picture;
            picture.load(fileName);
            //        painter.drawPixmap(currentX,currentY,picture);
            if(nTemp[i].key=='A')//画A->Ab或A->b的直线
            {
                if(nTemp[i].y>1)
                {
                    painter.drawPixmap(currentX,currentY,picture);
                    painter.drawLine(space_x*(nTemp[i-2].x+1)+16,iHeight-space_y*(nTemp[i-2].y+1)+16,currentX+16,currentY+16);
                    painter.drawLine(space_x*(nTemp[i-1].x+1)+16,iHeight-space_y*(nTemp[i-1].y+1)+16,currentX+16,currentY+16);
                    painter.end();
                }
                else
                {
                    painter.drawPixmap(currentX,currentY,picture);
                    painter.drawLine(currentX+16,currentY+space_y*nTemp[i].y+16,currentX+16,currentY+16);
                    painter.end();
                }
            }
            else if(nTemp[i].key=='B')//画B->d的直线
            {
                findXY('A',x,y);
                nY=y;
                painter.drawPixmap(currentX,iHeight-space_y*(nY+1),picture);
                painter.drawLine(currentX+16,currentY+space_y*nTemp[i].y+16,currentX+16,iHeight-space_y*(nY+1)+16);
                painter.end();
            }
            else if(nTemp[i].key=='S')//画S->aAcBe的所有直线
            {
                painter.drawPixmap(currentX,currentY,picture);
                findXY('A',x,y);
                nY=y;
                findXY('a',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,currentX+16,currentY+16);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,space_x*(x+1)+16,iHeight-space_y*(y+1)+16);
                findXY('A',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(y+1)+16,currentX+16,currentY+16);
                findXY('c',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(y+1)+16,currentX+16,currentY+16);
                findXY('B',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,currentX+16,currentY+16);
                findXY('e',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,currentX+16,currentY+16);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,space_x*(x+1)+16,iHeight-space_y*(y+1)+16);
                painter.end();
            }
            else
            {
                painter.drawPixmap(currentX,currentY,picture);
                painter.end();
            }
        }
    }
    else if(iCount>=0)
    {
        painter.begin(this);
        for(int i=0;i<=nTemp.size();i++)
        {
            fileName=charToName(nTemp[i].key);
            currentX=space_x*(nTemp[i].x+1);
            currentY=iHeight-space_y*(nTemp[i].y+1);
            QPixmap picture;
            picture.load(fileName);
            //        painter.drawPixmap(currentX,currentY,picture);
            if(nTemp[i].key=='A')//画A->Ab或A->b的直线
            {
                if(nTemp[i].y>1)
                {
                    painter.drawPixmap(currentX,currentY,picture);
                    painter.drawLine(space_x*(nTemp[i-2].x+1)+16,iHeight-space_y*(nTemp[i-2].y+1)+16,currentX+16,currentY+16);
                    painter.drawLine(space_x*(nTemp[i-1].x+1)+16,iHeight-space_y*(nTemp[i-1].y+1)+16,currentX+16,currentY+16);
                }
                else
                {
                    painter.drawPixmap(currentX,currentY,picture);
                    painter.drawLine(currentX+16,currentY+space_y*nTemp[i].y+16,currentX+16,currentY+16);
                }
            }
            else if(nTemp[i].key=='B')//画B->d的直线
            {
                findXY('A',x,y);
                nY=y;
                painter.drawPixmap(currentX,iHeight-space_y*(nY+1),picture);
                painter.drawLine(currentX+16,currentY+space_y*nTemp[i].y+16,currentX+16,iHeight-space_y*(nY+1)+16);
            }
            else if(nTemp[i].key=='S')//画S->aAcBe的所有直线
            {
                painter.drawPixmap(currentX,currentY,picture);
                findXY('A',x,y);
                nY=y;
                findXY('a',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,currentX+16,currentY+16);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,space_x*(x+1)+16,iHeight-space_y*(y+1)+16);
                findXY('A',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(y+1)+16,currentX+16,currentY+16);
                findXY('c',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(y+1)+16,currentX+16,currentY+16);
                findXY('B',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,currentX+16,currentY+16);
                findXY('e',x,y);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,currentX+16,currentY+16);
                painter.drawLine(space_x*(x+1)+16,iHeight-space_y*(nY+1)+16,space_x*(x+1)+16,iHeight-space_y*(y+1)+16);
            }
            else
                painter.drawPixmap(currentX,currentY,picture);
        }
        painter.end();
    }
}


void paintTree_one::findXY(const char cCh, int &x, int &y)
{
    vector<Node> nTemp;
    nTemp=m_tree->tree;
    if(cCh>='a'&&cCh<='e')//从左到右查找
    {
        for(int i=0;i<nTemp.size();i++)
        {
            if(nTemp[i].key==cCh)
            {
                x=nTemp[i].x;
                y=nTemp[i].y;
                return;
            }
        }
    }
    else
    {
        for(int i=nTemp.size();i>=0;i--)//从右到左查找
        {
            if(nTemp[i].key==cCh)
            {
                x=nTemp[i].x;
                y=nTemp[i].y;
                return;
            }
        }
    }
}


