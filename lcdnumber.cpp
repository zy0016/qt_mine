#include "lcdnumber.h"

//! [0]
LcdNumber::LcdNumber(QWidget *parent)
    : QLCDNumber(parent)
{
    setMinimumWidth(50);
    setMaximumWidth(50);
    setMinimumHeight(40);
    setMaximumHeight(40);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
//! [0]
