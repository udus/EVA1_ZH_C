#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(1200, 900);
    actNewGame  = new QAction(tr("&Új"),this);
    actExitGame = new QAction(tr("&Kilépés"), this);
    menu = this->menuBar()->addMenu(tr("&Menü"));
    menu->addAction(actNewGame);
    menu->addSeparator();
    menu->addAction(actExitGame);
    firstGame = true;
    gameLogic = new GameLogic();
    //!CONNECTS
    connect(actNewGame, SIGNAL(triggered()),this,SLOT(newGame()));
    connect(actExitGame, SIGNAL(triggered()),this,SLOT(exitGame()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::newGame()
{
    if (!firstGame)
    {
        gameDelete();
    }
    firstGame = false;
    gameLayout = new QGridLayout();
    gameWidget = new QWidget();
    gameWidget->setLayout(gameLayout);
    gameWidget->setFixedSize(880,880);
    setCentralWidget(gameWidget);
    int tableSizeINTOgameLogic;
    int vPBsize;
    bool ok;
    do
    {
        // kezdőérték, min, max, lépésköz, ok vagy cancelled
        int i = QInputDialog::getInt(this, tr("&Méret"),tr("(4 vagy 8 vagy 16?)"), 4, 4, 16, 1, &ok);
        if (ok)
            tableSizeINTOgameLogic = i;
    }while(!(tableSizeINTOgameLogic == 4 || tableSizeINTOgameLogic == 8 || tableSizeINTOgameLogic == 16) && ok);
    if (ok)
    {
        gameLogic->newGame(tableSizeINTOgameLogic);
        vPBsize = tableSizeINTOgameLogic*tableSizeINTOgameLogic;
        vPushButtons.resize(vPBsize);
        for (int i=0; i<vPBsize; ++i)
        {
            vPushButtons[i] = new indexedPushButton();
            vPushButtons[i]->index = i;
            vPushButtons[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            connect(vPushButtons[i], SIGNAL(clicked()),this, SLOT(buttonClicked()));

            if(tableSizeINTOgameLogic==4)
            {
                vPushButtons[i]->setFont(QFont("Times New Roman", 100, QFont::Bold));
            }
            else if(tableSizeINTOgameLogic==8)
            {
              vPushButtons[i]->setFont(QFont("Times New Roman", 50, QFont::Bold));
            }
            else
            {
                vPushButtons[i]->setFont(QFont("Times New Roman", 20, QFont::Bold));
            }
            gameLayout->addWidget(vPushButtons[i], i/tableSizeINTOgameLogic+1, i%tableSizeINTOgameLogic+1);
        }
        connect(gameLogic, SIGNAL(sendUpdateView()),this,SLOT(recieveUpdateView()));
        //! IDE FELVENNI A KIIRAST
        recieveUpdateView();
    }

}



void MainWindow::exitGame()
{
    this->close();
}

void MainWindow::buttonClicked()
{
    indexedPushButton* senderButton = dynamic_cast <indexedPushButton*> (sender());
    gameLogic->handleClickedButton(senderButton->index);
}

void MainWindow::recieveUpdateView()
{
    int t = gameLogic->getTableSize();

    for (int i= 0; i<t*t; ++i)
    {
        vPushButtons[i]->setText("");
    }
    for (int i= 0; i<t*t; ++i)
    {
        int x = i/t+1;
        int y = i%t+1;
        if(gameLogic->getState(x,y)==1)
        {
            vPushButtons[i]->setText("●");
        }
        if(gameLogic->getState(x,y)==2)
        {
            vPushButtons[i]->setText("○");
        }
    }
}

void MainWindow::gameDelete()
{
    delete gameLayout;
    delete gameWidget;
}
