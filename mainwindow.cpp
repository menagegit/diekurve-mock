#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGlobal>

#include <list>

/* ROADMAP:
 * 2 reflechir sur le bug clavier
 * 3 mettre le timer et peut etre la gestion clavier
 *   dans une autre classe "game" sur laquel on peut faire
 *   play pause restart ect...
 * 4 reseaux !
 */

player_option_t player_one = { red, Qt::Key_Left, Qt::Key_Right };
player_option_t player_two = { green, Qt::Key_A, Qt::Key_Z };

std::list<player_option_t*>options = std::list<player_option_t*>();

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game_view(new game_view_t(this, 640, 480)),
    timer(this),
    game_status(640, 480, game_view)
{
    srand(static_cast <unsigned> (time(0)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer.start(40);

    options.push_back(&player_one);
    options.push_back(&player_two);

    game_status.add_players(options);

    ui->setupUi(this);

    ui->rootHorizontalLayout->addWidget(game_view);
}

MainWindow::~MainWindow()
{
    delete game_view;
    delete ui;
}

void MainWindow::tick()
{
    game_status.update_game();
}

void MainWindow::keyPressEvent(QKeyEvent* k)
{
    // TODO lol; same bellow
    game_status.get_keyboard().pressed(k->key());
    if(k->key() == Qt::Key_Left)
        game_status.get_keyboard().pressed(Qt::Key_X);
    else if(k->key() == Qt::Key_Right)
        game_status.get_keyboard().pressed(Qt::Key_C);
}

void MainWindow::keyReleaseEvent(QKeyEvent* k)
{
    game_status.get_keyboard().released(k->key());
    if(k->key() == Qt::Key_Left)
        game_status.get_keyboard().released(Qt::Key_X);
    else if(k->key() == Qt::Key_Right)
        game_status.get_keyboard().released(Qt::Key_C);
}
