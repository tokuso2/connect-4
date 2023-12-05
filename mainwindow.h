#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "connect4widget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onRestartButtonClicked();
    void onExitButtonClicked();
    void onPlayAsPlayerOneButtonClicked();
    void onPlayAsPlayerTwoButtonClicked();

private:
    Connect4Widget* connect4Widget;
    QWidget* centralWidget;
    QPushButton* restartButton;
    QPushButton* exitButton;
    QPushButton* playAsPlayerOneButton;
    QPushButton* playAsPlayerTwoButton;
};

#endif // MAINWINDOW_H