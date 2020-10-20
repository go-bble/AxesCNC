#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <keyboard.h>
#include <QPushButton>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <sign.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    sign* kk;

    QPixmap *myPix;
    QPen *myPen;
    QPainter *myPint;
    int LB_w,LB_h;

    QString Gmodel;
    double x0,y0,i0,j0,f0;

    volatile bool m_lock;
    bool checkLock()const{ return m_lock; }
    void  Lock() { m_lock = true;}
    void Unlock() {m_lock = false;}

    void G1(int x0,int y0,int xe,int ye);
    void G2_3(int x0,int y0,int xe,int ye,int xr,int yr,int shun);
    void drawPix(int x0,int y0,int xe,int ye);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void do_keyborad();

    void on_BT_go_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
};


class virBTN :public QPushButton
{
    Q_OBJECT
};



#endif // MAINWINDOW_H
