#include "custspinbox.h"



CustSpinBox::CustSpinBox(QWidget * parent) : QSpinBox(parent)
{
    oldValue = 0;
}

CustSpinBox::~CustSpinBox()
{

}

void CustSpinBox::SetOldValue(int value)
{
    oldValue = value;
}

int CustSpinBox::GetOldValue()
{
    return oldValue;
}

int CustSpinBox::GetDirection()
{
    int val = abs(this->value());
    if((abs(oldValue) - val) < 0)
            return 1;               //if value must be count
      else
            return -1;               //if value we have in stack
}


int CustSpinBox::GetBrightSigned()
{

    if((oldValue - this->value()) <= 0)
            return this->value();
      else
            return -this->value();
}

int CustSpinBox::GetNextStep()
{
    if(this->value() > 0)
        return this->singleStep();
    else
        return -this->singleStep();
}
