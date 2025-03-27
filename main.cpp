#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include "mine_normal.h"
#ifdef MINESTYLE_OLD
#include "gameBoard.h"
#else
#include "minemain.h"
#endif
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
