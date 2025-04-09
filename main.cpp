#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include "mine_normal.h"
#ifdef MINESTYLE_OLD
#include "gameBoard.h"
#else
#include "minemain.h"
#endif
//C:\Users\y36zhao\code\git\qt\build-qt_mine-Desktop_Qt_5_14_2_MinGW_64_bit-Debug\debug
int main(int argc, char *argv[])
{
    QString en = ".\\mine_en.qm";
    QString cn = ".\\mine_cn.qm";
    QApplication app(argc, argv);
    QTranslator qt;
    bool b = qt.load(cn);
    if (!b)
    {
        //QMessageBox::about(nullptr,"about mine","can't load " + qLanguage_cn);
    }
    app.installTranslator(&qt);
#ifdef MINESTYLE_OLD
    gameBoard minegame(nullptr,en,cn);
    minegame.show();
#else
    MainWindow minemain(nullptr,en,cn);
    minemain.show();
#endif
    return app.exec();
}
