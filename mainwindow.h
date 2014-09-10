#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>

#include "game_status.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* k);
    void keyReleaseEvent(QKeyEvent* k);

public slots:
    void tick();

private:
    Ui::MainWindow *ui;
    game_view_t* game_view;
    QTimer timer;
    game_status_t game_status;

};

#endif // MAINWINDOW_H
