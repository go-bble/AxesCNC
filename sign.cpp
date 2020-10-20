#include "sign.h"
#include "ui_sign.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>

sign::sign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign)
{
    ui->setupUi(this);
    ui->frame_z->hide();
    this->setStyleSheet("#sign{border-image: url(:/build-AxesCNC-Desktop_Qt_5_13_2_MSVC2017_32bit-Debug/timg.jpeg)}");
    this->setGeometry(0,0,1280,800);

    QList<QPushButton *> btList = ui->frame_z->findChildren<QPushButton *>();//ui->Kwidget->findChildren<QPushButton *>();
    for (int i = 0; i < btList.size(); i++) {
      QPushButton *tmp =   static_cast<QPushButton *>(btList.at(i));
        connect(tmp,&QPushButton::clicked,this,&sign::do_keyborad);
    }
    //connect(ui->usernamelineEdit,&QLineEdit::)
//    this->ui->groupBox->setTitle("GDUT EDM");
    ui->LB_tis1->hide();
    ui->LB_tis1_2->hide();
    k_sign = false;

    InitSqlConnect();
    InitXmlFile();
}

sign::~sign()
{
    delete ui;
}
void sign::InitXmlFile(){
   QFile file("mypassword.xml");
   if(!file.exists()){
       QDomDocument doc;

       // 添加处理指令即XML说明
       QDomProcessingInstruction instruction;
       instruction = doc.createProcessingInstruction("xml",
                                                     "version=\"1.0\" encoding=\"UTF-8\"");
       doc.appendChild(instruction);

       // 添加根元素
       QDomElement root = doc.createElement("database");
       doc.appendChild(root);

       // 添加第一个user元素及其子元素
       QDomElement book = doc.createElement("user");
       QDomAttr id = doc.createAttribute("id");
       QDomElement title = doc.createElement("name");
       QDomElement author = doc.createElement("password");
       QDomText text;
       id.setValue(QString("1"));
       book.setAttributeNode(id);
       text = doc.createTextNode("123456");
       title.appendChild(text);
       text = doc.createTextNode("111111");
       author.appendChild(text);
       book.appendChild(title);
       book.appendChild(author);
       root.appendChild(book);

       // 添加第二个user元素及其子元素
       book = doc.createElement("user");
       id = doc.createAttribute("id");
       title = doc.createElement("name");
       author = doc.createElement("password");
       id.setValue(QString("2"));
       book.setAttributeNode(id);
       text = doc.createTextNode("666666");
       title.appendChild(text);
       text = doc.createTextNode("222222");
       author.appendChild(text);
       book.appendChild(title);
       book.appendChild(author);
       root.appendChild(book);

       //QFile file("my.xml");
       if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
       QTextStream out(&file);

       // 将文档保存到文件，4为子元素缩进字符数
       doc.save(out, 4);
       file.close();
   }


}
void sign::InitSqlConnect(){
//    //sql db
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("Base.db");//如果本目录下没有该文件,则会在本目录下生成,否则连接该文件
//    if (!db.open()) {
//            QMessageBox box0(QMessageBox::Warning,tr("Database Error..."),db.lastError().text());
//            QTimer::singleShot(2000,&box0,SLOT(accept())); //也可将accept改为close
//            box0.exec();
//            return;
//     }
////    query.exec("CREATE TABLE signMessage("
////               "name VARCHAR(40) PRIMARY KEY AUTOINCREMENT, "
////               "password VARCHAR(40) NOT NULL)");
//    //创建表格
//    const QString createDB = "create table myBase(id text primary key, password text not null)";
//    if(!query.exec(createDB)){
//        QMessageBox box0(QMessageBox::Warning,tr("create Database Error..."),query.lastError().text());
//        QTimer::singleShot(2000,&box0,SLOT(accept())); //也可将accept改为close
//        box0.exec();
//        return;
//    }



}

void sign::do_keyborad()
{
    QString m_ObjectName = sender()->objectName();
    QStringList strList = m_ObjectName.split("_");
    QString value = static_cast<QString>(strList.at(1));
    QString m_FocusName = this->focusWidget()->objectName();
    if (value == "del") {
        value = "";
        QKeyEvent tabKey(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
        QCoreApplication::sendEvent(this->focusWidget(), &tabKey);
    }
    else {
        if(m_FocusName == "usernamelineEdit"||m_FocusName == "passwdlineEdit"){
            static_cast<QLineEdit*>(this->focusWidget())->insert(value);
        }
    }
    //qDebug()<<m_ObjectName<<strList.at(0)<<"_"<<value;
    //ui->textEdit_2->insertPlainText(value);
}
//sign
void sign::on_signpushButton_2_clicked()
{

    if(k_sign == false ){
        k_sign= true;
        ui->frame_z->show();
        ui->usernamelineEdit->clear();
        ui->passwdlineEdit->clear();
        ui->groupBox->setTitle("正在注册...");
        ui->signpushButton_2->setText("取消注册");
        ui->signpushButton->setText("确认");
        ui->usernamelabel->setText("请输入用户名");
        ui->passwdlabel->setText("请输入密码");
    }
    else{
        k_sign=false;
        ui->frame_z->hide();
        ui->groupBox->setTitle("GDUT EDM");
        ui->signpushButton_2->setText("注册");
        ui->signpushButton->setText("登录");
        ui->usernamelabel->setText("用户名");
        ui->passwdlabel->setText("密码");
    }

}

void sign::on_signpushButton_clicked()
{
    if(ui->usernamelineEdit->text().isEmpty()||ui->passwdlineEdit->text().isEmpty()){
        QMessageBox box0(QMessageBox::Warning,"错误!","账号或密码不能为空!");
                    QTimer::singleShot(5000,&box0,SLOT(accept())); //也可将accept改为close
                    box0.exec();
                    return;
    }
    if(k_sign){
        //inser message
        QString tmp = findUserName(ui->usernamelineEdit->text());
        if(!tmp.isEmpty()){
            QMessageBox box(QMessageBox::Information,tr("错误"),"账号已经存在");
            QTimer::singleShot(2000,&box,SLOT(accept())); //也可将accept改为close
            box.exec();
            return;
        }
        QMessageBox box(QMessageBox::Information,tr("注册成功"),"返回登录");
        QTimer::singleShot(2000,&box,SLOT(accept())); //也可将accept改为close
        box.exec();
        addUser(ui->usernamelineEdit->text(),ui->passwdlineEdit->text());
        on_signpushButton_2_clicked();
    }else {
        if(findUserName(ui->usernamelineEdit->text()) == ui->passwdlineEdit->text()){
            this->close();
        }else {
            QMessageBox box(QMessageBox::Information,tr("错误"),tr("账号或者密码错误..."));
            QTimer::singleShot(2000,&box,SLOT(accept())); //也可将accept改为close
            box.exec();
        }

    }

//    if(ui->usernamelineEdit->text() == "123456"&&ui->passwdlineEdit->text() == "111111"){
//        this->close();
//    }else if (ui->usernamelineEdit->text() == "666666"&&ui->passwdlineEdit->text() == "222222") {
//        this->close();
//    }
//    else {
//        QMessageBox box(QMessageBox::Information,tr("错误"),tr("账号或者密码错误..."));
//        QTimer::singleShot(2000,&box,SLOT(accept())); //也可将accept改为close
//        box.exec();
//    }

}


//keyboard
void sign::on_signpushButton_3_clicked()
{

    if(ui->frame_z->isVisible()){
        ui->frame_z->hide();
    }else {
        ui->frame_z->show();
        ui->usernamelineEdit->setFocus();
    }
}


QString sign::findUserName(QString name){
    QFile file("mypassword.xml");
    if (!file.open(QIODevice::ReadOnly)) return QString("");
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return QString("");
    }
    file.close();
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    QString tmp = "";
    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            //ui->listWidget->addItem(e.tagName() + e.attribute("编号"));
            QDomNodeList list = e.childNodes();
            for (int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement()){
                    if(node.toElement().tagName() == "name"){
                        if(name == node.toElement().text()){
                            node.clear();
                            node = list.at(i+1);
                            tmp = node.toElement().text();
                        }

                    }
                }
            }
        }
        n = n.nextSibling();
    }
    return tmp;
}

void sign::addUser(QString t_name,QString t_password){
    QFile file("mypassword.xml");
        if (!file.open(QIODevice::ReadOnly)) return;
        QDomDocument doc;
        if (!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();
        QDomElement root = doc.documentElement();
        QDomElement user = doc.createElement("user");
        QDomAttr id = doc.createAttribute("id");
        QDomElement name = doc.createElement("name");
        QDomElement password = doc.createElement("password");
        QDomText text;

        // 我们获得了最后一个孩子结点的编号，然后加1，便是新的编号
        QString num = root.lastChild().toElement().attribute("id");
        int count = num.toInt() +1;
        id.setValue(QString::number(count));
        user.setAttributeNode(id);
        text = doc.createTextNode(t_name/*ui->lineEdit_2->text()*/);
        name.appendChild(text);
        text = doc.createTextNode(t_password/*ui->lineEdit_3->text()*/);
        password.appendChild(text);
        user.appendChild(name);
        user.appendChild(password);
        root.appendChild(user);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
        QTextStream out(&file);
        doc.save(out, 4);
        file.close();
}
