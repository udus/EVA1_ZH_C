#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <QPixmap>
#include <QIcon>
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include "gamelogic.h"



struct indexedPushButton : public QPushButton
{
    int index;
    QPushButton* PushButton;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadNewGame();
    ~MainWindow();
public slots:
    void newGame();
    void exitGame();
    void buttonClicked();
    void recieveUpdateView();
    void gameDelete();
private:
    QAction* actNewGame;
    QAction* actExitGame;
    QMenu*   menu;
    bool firstGame;
    QGridLayout* gameLayout;
    QWidget* gameWidget;
    GameLogic* gameLogic;
    std::vector<indexedPushButton*> vPushButtons;
};

#endif // MAINWINDOW_H
