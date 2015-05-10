/*伪码对话窗口*/

#ifndef WEIMA_H
#define WEIMA_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>

class weima : public QDialog
{
    Q_OBJECT
public:
    explicit weima(QWidget *parent = 0);
    void wmShow();
private:
    QLabel *wmLabel;
    QScrollArea *wmArea;
    QVBoxLayout *vLayout;
};

#endif // WEIMA_H
