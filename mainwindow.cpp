#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <QTextBlock>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    kk = new sign(this) ;
    QList<QPushButton *> btList = ui->Kwidget->findChildren<QPushButton *>();
    for (int i = 0; i < btList.size(); i++) {
      QPushButton *tmp =   static_cast<QPushButton *>(btList.at(i));
        connect(tmp,&QPushButton::clicked,this,&MainWindow::do_keyborad);
    }
    ui->Kwidget->hide();
    x0 = 0;
    y0 = 0;
    Unlock();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::G1(int x0, int y0, int xe, int ye)
{
    int Nxy,xi=0,yi=0,FM;
    Nxy =abs( (xe - x0)) + abs((ye - y0));
    int a1 =0,a2 = 0,b1,b2;
    int i=1;
    xi = x0;//x,y分别存放实时的坐标
    yi = y0;//
    //FM =xe*yi-xi*ye;

    while(Nxy!=0)
    {

        FM =(xe-x0)*(yi-y0)-(xi-x0)*(ye-y0);

        qDebug()<<FM<<";"<< FM<<";" << FM<<";"<< FM;
        if(FM >= 0 )
            {
            //F=FM-ye;
                if(xe-x0==0){
                        if(ye-y0>0)
                            yi=yi+1; //Y正向走步程序
                        else if(ye-y0<0)
                            yi--;//Y负向走步程序
                        //cout<<i<<"  "<<xi<<","<<yi<<"  \tFM="<<FM<<"  "<<endl;
                }

                else if(xe-x0>0){
                    if(ye-y0>0)//第一象限
                        xi++;
                    else {
                        yi--;//第四象限
                    }

                }
                    //xi=xi+1; //X正向走步程序
                else if(xe-x0<0){
                    if(ye-y0>0)//第2象限
                        yi++;
                    else {
                        xi--;//第3象限
                    }

                }

                    //xi--;//X负向走步程序
                //qDebug()<<i<<"+:  "<<xi<<","<<yi<<"  \tFM="<<FM<<"  "<<endl;
            }
        else
            {
                //F=FM+xe;
                if(ye-y0==0){
                    if(xe-x0>0)
                        xi=xi+1;
                    else if(xe-x0<0)
                        xi--;
                }
                else if(ye-y0>0){
                    if(xe-x0>0)//第一象限
                        yi++;
                    else {
                        xi--;//第2象限
                    }

                }
                    //yi=yi+1; //Y正向走步程序
                else if(ye-y0<0){
                    if(xe-x0>0)//第4象限
                        xi++;
                    else {
                        yi--;//第3象限
                    }

                }
                    //yi--;//Y负向走步程序


            }

                b1=xi;b2=yi;
                if(i==1){
                    a1=b1;a2=b2;
                }
                drawPix(a1,a2,b1,b2);
                qDebug()<<" x0->"<<a1<<" y0->"<<a2<<" xe->"<<b1<<" ye->"<<b2;
                //line(a1,(600-a2),b1,(600-b2));//line(a1,a2,b1,b2);
                a1=b1;a2=b2;
            //qDebug()<<i<<"-:  "<<xi<<","<<yi<<"  \tFM="<<FM<<"  "<<endl;
        Nxy--;
        i++;
        }
}

void MainWindow::G2_3(int x0, int y0, int xe, int ye, int xr, int yr, int shun)
{
        int Fe,xi=0,yi=0;
        int i= 1;
        int a1=x0;
        int a2=y0;
        int b1,b2;
        int x=xr;
        int y=yr;
        double rr=(xe-x)*(xe-x)+(ye-y)*(ye-y);
        xi=x0;yi=y0;//起点赋给xiyi

        while(xi!=xe||yi!=ye)//没有到达终点时
        {
        //Sleep(5);//休眠5毫秒//暂停5ms
            Fe=(xi-x)*(xi-x)+(yi-y)*(yi-y)-rr;
            //cout<<"Fe:"<<Fe<<endl;//system("pause");
            if(Fe>=0)
            {
                if(shun==1){
                    if(xi>=x&&yi<=y)
                        xi--;
                    else if(xi<=x&&yi<=y)
                        yi++;
                    else if(xi<=x&&yi>=y)
                        xi++;
                    else if(xi>=x&&yi>=y)
                        yi--;
                }
                else if(shun==2){
                    if(xi>=x&&yi<=y)
                        yi++;//xi--;
                    else if(xi<=x&&yi<=y)
                        xi++;//yi++;
                    else if(xi<=x&&yi>=y)
                        yi--;//xi++;
                    else if(xi>=x&&yi>=y)
                        xi--;//yi--;
                }
            }
            else
            {
                if(shun==1){
                    if(xi>=x&&yi<=y)
                        yi--;//xi--;
                    else if(xi<=x&&yi<=y)
                        xi--;//yi++;
                    else if(xi<=x&&yi>=y)
                        yi++;//xi++;
                    else if(xi>=x&&yi>=y)
                        xi++;//yi--;
                }
                else if(shun==2){
                    if(xi>=x&&yi<=y)
                        xi++;//yi++;//xi--;
                    else if(xi<=x&&yi<=y)
                        yi--;//xi++;//yi++;
                    else if(xi<=x&&yi>=y)
                        xi--;//yi--;//xi++;
                    else if(xi>=x&&yi>=y)
                        yi++;//xi--;//yi--;
                }

            }

                b1=xi;b2=yi;
                if(i==1){
                    a1=b1;a2=b2;
                }
                drawPix(a1,a2,b1,b2);
                //line(a1,(600-a2),b1,(600-b2));//line(a1,a2,b1,b2);
                a1=b1;a2=b2;

            i++;
        }
}

void MainWindow::drawPix(int x0, int y0, int xe, int ye)
{


    static bool bo = true;
    if(bo){
        bo = false;
        LB_h = ui->LB_draw->height();
        LB_w = ui->LB_draw->width();
        myPix = new QPixmap(LB_w,LB_h);
        myPix->fill(Qt::black);
        myPint = new QPainter(myPix);
        myPen = new QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
        myPint->setPen(*myPen);


        QLineF linex((0+LB_w/2),(0+LB_h/2),(30+LB_w/2),(0+LB_h/2));
        myPint->drawLine(linex);
        ui->LB_draw->setPixmap(*myPix);


        QLineF linex1((30+LB_w/2),(0+LB_h/2),(26+LB_w/2),(4+LB_h/2));
        myPint->drawLine(linex1);
        ui->LB_draw->setPixmap(*myPix);

        QLineF linex2((30+LB_w/2),(0+LB_h/2),((26)+LB_w/2),((-4)+LB_h/2));
        myPint->drawLine(linex2);
        ui->LB_draw->setPixmap(*myPix);


        myPen->setColor(Qt::green);
        myPint->setPen(*myPen);
        QLineF liney((0+LB_w/2),(0+LB_h/2),(0+LB_w/2),((-30)+LB_h/2));
        myPint->drawLine(liney);
        ui->LB_draw->setPixmap(*myPix);

        QLineF liney1((0+LB_w/2),((-30)+LB_h/2),(4+LB_w/2),((-26)+LB_h/2));
        myPint->drawLine(liney1);
        ui->LB_draw->setPixmap(*myPix);

        QLineF liney2((0+LB_w/2),((-30)+LB_h/2),((-4)+LB_w/2),((-26)+LB_h/2));
        myPint->drawLine(liney2);
        ui->LB_draw->setPixmap(*myPix);

        myPen->setColor(Qt::red);
        myPint->setPen(*myPen);

    }

    qApp->processEvents();
    QLineF line((x0+LB_w/2),(y0+LB_h/2),(xe+LB_w/2),(ye+LB_h/2));
    myPint->drawLine(line);
    //myPint->drawPoint((xe+LB_w/2),(ye+LB_h/2));
    ui->LB_draw->setPixmap(*myPix);
    ui->LB_draw->setScaledContents(true);
    ui->LB_draw->update();
    ui->lineEdit_3->setText(QString::number(xe+LB_w/2));
    ui->lineEdit_4->setText(QString::number(ye+LB_h/2));
    QThread::msleep(ui->horizontalSlider->value());

}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog :: getOpenFileName(this, "打开NC文件", ".","*.NC *.cpp *.txt");
    QFile file(fileName);
    if (file.open(QIODevice ::ReadWrite | QIODevice ::Text))
        {
            QTextStream textStream(&file);
            ui->textEdit->setPlainText(textStream.readAll());
            file.seek(0);
            ui->textEdit_2->setPlainText(textStream.readAll());
            on_pushButton_4_clicked();
        }
    else
    {
        QMessageBox box(QMessageBox::Information,tr("错误"),tr("文件打开或格式错误..."));
        QTimer::singleShot(2000,&box,SLOT(accept())); //也可将accept改为close
        box.exec();
    }
}

//参数
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


//加工
void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//编辑
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


//状态
void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::do_keyborad()
{
    QString m_ObjectName = sender()->objectName();
    QStringList strList = m_ObjectName.split("_");
    QString value = static_cast<QString>(strList.at(1));
    if(value == "dot"){
        value = ".";
    }else if (value == "del") {
        value = "";
        QKeyEvent tabKey(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
        QCoreApplication::sendEvent(ui->textEdit_2, &tabKey);
    }
    else if (value == "undo") {
            value = "";
            ui->textEdit_2->undo();
        }
    //qDebug()<<m_ObjectName<<strList.at(0)<<"_"<<value;
    ui->textEdit_2->insertPlainText(value);
}

void MainWindow::on_BT_go_clicked()
{
    if(ui->textEdit_2->document()->lineCount()<2){
        QMessageBox box(QMessageBox::Information,tr("错误"),tr("文件未打开或文件格式错误..."));
        QTimer::singleShot(2000,&box,SLOT(accept())); //也可将accept改为close
        box.exec();
    }else {
        QtConcurrent::run([=](){
            int lineCount = ui->textEdit_2->document()->lineCount();
            QString Gcmd,tmp;
            QStringList Glist;
            double maxX =0;
            double maxY =0;
            double xe =0;
            double ye =0;
            static bool fis = false;
            for(int i = 0;i < lineCount; i++)
            {
                while (checkLock()) {
                    qApp->processEvents();
                    QThread::msleep(200);
                }
                Gcmd.clear();
                Glist.clear();
                Gcmd =static_cast<QTextBlock>(ui->textEdit_2->document()->findBlockByNumber(i)).text();
                ui->LB_G->setText(Gcmd);
                Gcmd.replace("X.","X0.");
                Gcmd.replace("Y.","Y0.");
                Gcmd.replace("-.","-0.");
                Gcmd.replace("I.","I0.");
                Gcmd.replace("J.","J0.");
                Glist = Gcmd.split(" ");
                for (int j = 0; j < Glist.count(); j++) {
                    //qDebug()<<"lineCount"<<i<<" ["<<j<<"]"<<Glist.at(j);
                    tmp = static_cast<QString>(Glist.at(j));
                    if(tmp == "G0"||tmp == "G1"||tmp == "G2"||tmp == "G3"){
                        Gmodel = tmp;
                        //qDebug()<<"--G?--"<<Gmodel;
                    }else if (tmp == "") {
                        //qDebug()<<"--continue--"<<xe;
                        continue;
                    }
                    if(tmp.at(0) == 'X')
                    {
                        xe =tmp.remove("X").toDouble();
                        //qDebug()<<"--x--"<<xe;
                    }else if (tmp.at(0) == 'Y')
                    {
                        ye =tmp.remove("Y").toDouble();
                        if(!fis){
                            fis = true;
                            x0 = xe;
                            y0 = ye;
                        }
                       //qDebug()<<"--y--"<<ye;
                    }else if (tmp.at(0) == 'I')
                    {
                        i0 =tmp.remove("I").toDouble();
                        //qDebug()<<"--I--"<<i0;
                    }else if (tmp.at(0) == 'J')
                    {
                        j0 =tmp.remove("J").toDouble();
                        //qDebug()<<"--J--"<<j0;
                    }

//                    if(x0 > maxX)
//                        maxX = xe;
//                    if(y0 > maxY)
//                        maxY = ye;
                }

                if(!qFuzzyCompare(x0,xe)||!qFuzzyCompare(y0,ye)){
                    qApp->processEvents();
                    //qDebug()<<i<<"x0:"<<x0<<"--xe:"<<xe<<"---Gcmd"<<Gcmd;
                    qDebug()<<i<<"Gmodel:"<<Gmodel<<"x0:"<<x0<<"--y0:"<<y0<<"--xe:"<<xe<<"--ye:"<<ye<<"--i0:"<<xe<<"--j0:"<<ye;
                    if(Gmodel == "G0"||Gmodel == "G1"){
                        G1((int)x0,(int)y0,(int)xe,(int)ye);
                    }else if (Gmodel == "G2") {
                        //qDebug()<<i<<"(int)(y0-j0):"<<(int)(x0-i0)<<"--(int)(y0+j0):"<<(int)(y0+j0);
                        G2_3((int)x0,(int)y0,(int)xe,(int)ye,(int)(x0+i0),(int)(y0+j0),1);
                    }else if (Gmodel == "G3") {
                        G2_3((int)x0,(int)y0,(int)xe,(int)ye,(int)(x0+i0),(int)(y0+j0),2);
                    }
                    x0 = xe;
                    y0 = ye;

                }

            }
        });


    }
}


void MainWindow::on_pushButton_7_clicked()
{
    Lock();
}

void MainWindow::on_pushButton_8_clicked()
{
    Unlock();
}

void MainWindow::on_pushButton_9_clicked()
{
    QProcess::startDetached(qApp->applicationFilePath(),QStringList());
    qApp->exit();
}

void MainWindow::on_pushButton_11_clicked()
{
    static bool key1 = false;
    if(key1 == false ){
        key1= true;
        ui->Kwidget->show();
        ui->textEdit_2->setFocus();
    }
    else{
        key1=false;
        ui->Kwidget->hide();
    }
}

void MainWindow::on_pushButton_12_clicked()
{

}
