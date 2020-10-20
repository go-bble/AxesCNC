#ifndef SIGN_H
#define SIGN_H

#include <QWidget>
#include <QDialog>
//#include <QSqlDatabase>
//#include <QSqlQuery>
//#include <QSqlError>
#include <QtXml>
#include <QStringList>
namespace Ui {
class sign;
}

class sign : public QDialog
{
    Q_OBJECT

public:
    explicit sign(QWidget *parent = nullptr);
    ~sign();
    void do_keyborad();
    bool k_sign;

    //QSqlDatabase db;
    //QSqlQuery query;
    
    void InitSqlConnect();
    void InitXmlFile();
    QString findUserName(QString name);
    void addUser(QString name, QString password);
private slots:
    void on_signpushButton_2_clicked();

    void on_signpushButton_clicked();



    void on_signpushButton_3_clicked();

private:
    Ui::sign *ui;
};


#endif // SIGN_H
