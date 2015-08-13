#ifndef CUSTSPINBOX_H
#define CUSTSPINBOX_H

#include <QSpinBox>

class CustSpinBox : public QSpinBox
{
public:

    ~CustSpinBox();
    CustSpinBox(QWidget *parent = 0);
    void SetOldValue(int );
    int GetOldValue();
    int GetDirection();
    int GetBrightSigned();
    int GetNextStep();
private:
    int oldValue;
};

#endif // CUSTSPINBOX_H
