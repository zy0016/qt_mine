#ifndef PAINTMINE_H
#define PAINTMINE_H
#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include "mine_normal.h"

class QTimer;

#define EASY_SCREEN_SIZE_W 360
#define EASY_SCREEN_SIZE_H 500
#define MID_SCREEN_SIZE_W 520
#define MID_SCREEN_SIZE_H 650
#define HARD_SCREEN_SIZE_W 650
#define HARD_SCREEN_SIZE_H 770
class paintmine : public QWidget
{
    Q_OBJECT

public:
    paintmine(QWidget *parent = nullptr,CHESS_DIFFICULTY chess_level = Difficult_Easy,QString en="",QString cn="");

public slots:
    void NewGame(CHESS_DIFFICULTY chess_level = Difficult_Easy);
    void SetLanguage(int l);

private slots:

signals:
    void MineNumberValueChange(int iValue);
    void StartMineTimer();
    void StopMineTimer();
    void ClearMineTime();
    void gamefail();

protected:
    void paintEvent(QPaintEvent *event) override;
    void  mousePressEvent( QMouseEvent * e) override;
private:
    void SetMines(int iRow,int iCol);
    void InitChessman(CHESS_DIFFICULTY chess_level = Difficult_Easy);
    void BeginMine();
    void MineOver();
    void ClearTime();
    void SetMineNumber(int iValue);
    bool GetChessNumber(int & iRow,int & iCol,const QPoint &point);
    bool IfGameOver();
    void DrawMineNumber(int i,int j);
    bool IfExistMineInCurrentCol(int icol);
    CHESS_DIFFICULTY level;
    GAME_RESULT game_result;
    QString en_qm;
    QString cn_qm;
    bool bMineDefeat;//true:mine defeat,display game over,false:game doesn't over,
    QString qClew;

    int iFindMineNumber;//Find the mine number
    bool bStartMine;//true:begin mine,false:don't begin mine
    int iLanguage;
    int hx1;
    int hy1;
    int bh;
    int bw;
    int RowCount;
    int ColCount;
    int chessnum;
    int minenum;
    QVector<QVector<CHESSMANTYPE>> sChessmine;
};

#endif // PAINTMINE_H
