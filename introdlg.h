
/* 算法流程图对话框*/

#ifndef INTRODLG_H
#define INTRODLG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QScrollArea>
class introDlg : public QDialog
{
    Q_OBJECT
public:
    explicit introDlg(QWidget *parent = 0);
    void drawPic(QString srcPic);

public slots:

private:
    QPixmap *img;
    QLabel *imgLabel;
    QVBoxLayout *layout;
    QScrollArea *area;
};

#endif // INTRODLG_H
