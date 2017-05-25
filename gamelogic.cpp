#include "gamelogic.h"

GameLogic::GameLogic()
{

}

void GameLogic::newGame(int a)
{
    tableSize = a;
    turn = 1;
    enemyTurn = 2;
    for(int i = 0; i<tableSize+1; ++i)
    {
        for(int j = 0; j<tableSize+1; ++j)
        {
            table[i][j].State = 0;
            table[i][j].x = i;
            table[i][j].y = j;
        }
    }
    table[tableSize/2][tableSize/2].State = 1;
    table[tableSize/2+1][tableSize/2].State = 2;
    table[tableSize/2][tableSize/2+1].State = 2;
    table[tableSize/2+1][tableSize/2+1].State = 1;

}

void GameLogic::handleClickedButton(int a)
{
    int i = a / tableSize+1;
    int j = a % tableSize+1;
    if (table[i][j].State == 0)
        {
            std::vector<Field> v;
            v.resize(0);
            getNeighbors(i, j, v);
            bool foundTurn = false;
            for (int k = 0; k < v.size(); k++)
            {
                branchAttack(i, j, v[k], foundTurn);
            }
            if (foundTurn)
            {
                table[i][j].State = turn;
                swichTurn();
            }
            emit sendUpdateView();

        }
}


void GameLogic::swichTurn()
{
    if (turn == 1)
    {
        turn = 2;
        enemyTurn = 1;
    }else if(turn == 2)
    {
        turn = 1;
        enemyTurn = 2;
    }
}

void GameLogic::getNeighbors(int x, int y, std::vector<Field> &v)
{
    if(table[x][y-1].State == enemyTurn)
    {
        v.push_back(table[x][y-1]);
    }
    if(table[x][y+1].State == enemyTurn)
    {
        v.push_back(table[x][y+1]);
    }
    if(table[x-1][y-1].State == enemyTurn)
    {
        v.push_back(table[x-1][y-1]);
    }
    if(table[x-1][y].State == enemyTurn)
    {
        v.push_back(table[x-1][y]);
    }
    if(table[x-1][y+1].State == enemyTurn)
    {
        v.push_back(table[x-1][y+1]);
    }


    if(table[x+1][y-1].State == enemyTurn)
    {
        v.push_back(table[x+1][y-1]);
    }
    if(table[x+1][y].State == enemyTurn)
    {
        v.push_back(table[x+1][y]);
    }
    if(table[x+1][y].State == enemyTurn)
    {
        v.push_back(table[x+1][y+1]);
    }

}

void GameLogic::branchAttack(int i,int j, Field F, bool &foundTurn)
{
    //! Determine direction
    char increment_direction;
    if(j < F.y && i == F.x)
    {
        increment_direction = 'd';
    }
    if(j > F.y && i == F.x)
    {
        increment_direction = 'a';
    }
    if(j == F.y && i > F.x)
    {
        increment_direction = 'w';
    }
    if(j == F.y && i < F.x)
    {
        increment_direction = 's';
    }

    if(j < F.y && i < F.x)
    {
        increment_direction = 'g';
    }

    if(j > F.y && i > F.x)
    {
        increment_direction = 'r';
    }

    if(j > F.y && i < F.x)
    {
        increment_direction = 'f';
    }

    if(j < F.y && i > F.x)
    {
        increment_direction = 't';
    }


    bool foundB = false;
    bool foundG = false;
    std::vector<Field> Devour;
    Devour.resize(0);
    increment(i, j, increment_direction);
    while (!foundG && !foundB && i > 0 && j > 0 && i < tableSize && j < tableSize && i > 0 && j > 0)
    {
        if(table[i][j].State == enemyTurn)
        {
            Devour.push_back(table[i][j]);
            increment(i, j, increment_direction);
        }
        if(table[i][j].State == turn)
        {
            foundB = true;
        }
        if (table[i][j].State == 0)
        {
            foundG = true;
        }
    }
    if (foundB)
    {
        foundTurn = true;
        for (int i = 0; i < Devour.size(); i++)
        {
            int m, n;
            m = Devour[i].x;
            n = Devour[i].y;
            table[m][n].State = turn;
        }
    }

}

void GameLogic::increment(int &i, int &j, char mode)
{
    if (mode == 'a')
    {
        j--;
    }
    if (mode == 'w')
    {
        i--;
    }
    if (mode == 'd')
    {
        j++;
    }
    if (mode == 's')
    {
        i++;
    }


    if (mode == 'r')
    {
        i--;
        j--;
    }
    if (mode == 't')
    {
        i--;
        j++;
    }
    if (mode == 'f')
    {
        i++;
        j--;
    }
    if (mode == 'g')
    {
        i++;
        j++;
    }
}

