#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

namespace Ui {
class keyboard;
}

class keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit keyboard(QWidget *parent = nullptr);
    ~keyboard();


private:
    Ui::keyboard *ui;
};

#endif // KEYBOARD_H
