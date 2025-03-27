#ifndef MINE_NORMAL_H
#define MINE_NORMAL_H

#include <QtWidgets/qwidget.h>
#include <QMouseEvent>
#include <QVector>

#define CHESSNUM_EASY 8
#define MINESNUM_EASY 10

#define CHESSNUM_MID 16
#define MINESNUM_MID 40

#define CHESSNUM_HARD 20
#define MINESNUM_HARD 50

//#define MINESTYLE_OLD

typedef enum
{
    GRID_NORMAL,
    GRID_FLAG,
    GRID_INTERROGATION,
    GRID_CLICKOPEN,
    GRID_DEFEAT
}GRIDTYPE;
typedef struct
{
    bool bMineType;//true:the grid has a mine,false:the grid hasn't a mine
    int iMineNum;//if the grid hasn't a mine,recore the number that around grid has mine.
    QPoint qPChessman;//the grid coordinate
    GRIDTYPE eGridType;//when people click the grid by mouse right button,record the grid type.
    bool bCheck;//true:Be checked by recursion,false :don't check by recursion
}CHESSMANTYPE;

typedef enum
{
    Difficult_Easy,
    Difficult_Middle,
    Difficult_Hard
}CHESS_DIFFICULTY;

typedef enum
{
    SUCCESS,
    FAIL,
    PROGRESSING
}GAME_RESULT;


#endif // MINE_NORMAL_H
