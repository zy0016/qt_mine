#include <QApplication>
#include <QTranslator>
#include "gameBoard.h"
#include <QMessageBox>

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
    gameBoard minegame(nullptr,en,cn);
    minegame.show();
    return app.exec();
}
