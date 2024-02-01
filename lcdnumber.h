#ifndef LCDNUMBER_H
#define LCDNUMBER_H
#include <QLCDNumber>

//! [0]
class LcdNumber : public QLCDNumber
{
    Q_OBJECT

public:
    explicit LcdNumber(QWidget *parent = nullptr);
};
//! [0]


#endif // LCDNUMBER_H
