#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class Mybutton : public QPushButton
{
    Q_OBJECT
public:
    explicit Mybutton(QWidget *parent = 0);
    ~Mybutton();

signals:

public slots:
};

#endif // MYBUTTON_H
