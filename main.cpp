#include <QApplication>
#include <QTranslator>
#include "gameBoard.h"
#include <QMessageBox>
static const QString qLanguage_cn = ".\\mine_cn.qm";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator qt;
    bool b = qt.load(qLanguage_cn);
    if (!b)
    {
        QMessageBox::about(nullptr,"about mine","can't load " + qLanguage_cn);
    }
    app.installTranslator(&qt);

    gameBoard minegame;
    //load language depart begin

//    QTranslator qt;
//    qt.load(qLanguage);

//    a.installTranslator(&qt);
//    QTranslator myapp(0);
//    myapp.load(qLanguage);

//    a.installTranslator(&myapp);
    //load language depart end.

    minegame.show();
    return app.exec();
}
