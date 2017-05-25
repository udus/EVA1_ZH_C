#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <vector>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QDateTime>


struct Field
{
    int x;
    int y;
    int State; // 1 - for BLACK, 2 - for WHITE, 0 - for EMPTY
};

class GameLogic : public QObject
{
 Q_OBJECT
public:
    GameLogic();
    void newGame(int a);
    void handleClickedButton(int a);
    void swichTurn();
    void calculateEffect(int i, int j);
    int getTableSize(){return tableSize;}
    int getState(int i, int j){return table[i][j].State;}
    void getNeighbors(int x, int y, std::vector<Field> &v);
    void branchAttack(int i, int j, Field F, bool &foundTurn);
    void increment(int &i, int &j, char mode);
private:
    int tableSize;
    Field table[22][22];
    int turn;
    int enemyTurn;
signals:
    void sendUpdateView();
};

#endif // GAMELOGIC_H
