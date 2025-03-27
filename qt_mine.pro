QT += widgets
RC_FILE = logo.rc
HEADERS       = button.h \
    gameBoard.h \
    lcdnumber.h \
    mine.h \
    mine_normal.h \
    minemain.h \
    paintmine.h
SOURCES       = button.cpp \
                gameBoard.cpp \
                lcdnumber.cpp \
                main.cpp \
                mine.cpp \
                minemain.cpp \
                paintmine.cpp

TRANSLATIONS = mine_cn.ts \
                mine_en.ts

# install
target.path = C:\Users\y36zhao\code\git\qt\qt_mine
INSTALLS += target

DISTFILES += \
    blackmine.png
