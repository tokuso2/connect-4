#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // setFixedSize(1000, 800); // Window size.

    this->centralWidget = new QWidget(this);
    QGridLayout* mainLayout = new QGridLayout(centralWidget);

    mainLayout->setRowStretch(1, 1);

    this->connect4Widget = new Connect4Widget(centralWidget);
    mainLayout->addWidget(connect4Widget, 1, 0, 1, -1, Qt::AlignCenter);

    // Set up the player selection buttons.
    QHBoxLayout* buttonLayout2 = new QHBoxLayout();
    this->playAsPlayerOneButton = new QPushButton("Play as red", centralWidget);
    this->playAsPlayerTwoButton = new QPushButton("Play as yellow", centralWidget);
    this->playAsPlayerOneButton->setCheckable(true);
    this->playAsPlayerOneButton->setChecked(true);
    this->playAsPlayerTwoButton->setCheckable(true);
    buttonLayout2->addWidget(playAsPlayerOneButton);
    buttonLayout2->addWidget(playAsPlayerTwoButton);
    connect(playAsPlayerOneButton, &QPushButton::clicked, this, &MainWindow::onPlayAsPlayerOneButtonClicked);
    connect(playAsPlayerTwoButton, &QPushButton::clicked, this, &MainWindow::onPlayAsPlayerTwoButtonClicked);
    this->playAsPlayerOneButton->setMinimumHeight(50);
    this->playAsPlayerTwoButton->setMinimumHeight(50);
    mainLayout->setRowStretch(2, 2);
    mainLayout->addLayout(buttonLayout2, 2, 0, 1, -1);

    // Set up the exit and restart buttons.
    QHBoxLayout* buttonLayout1 = new QHBoxLayout();
    this->restartButton = new QPushButton("Restart", centralWidget);
    this->exitButton = new QPushButton("Exit", centralWidget);
    buttonLayout1->addWidget(restartButton);
    buttonLayout1->addWidget(exitButton);
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::onRestartButtonClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
    this->restartButton->setMinimumHeight(50);
    this->exitButton->setMinimumHeight(50);
    mainLayout->setRowStretch(2, 2);
    mainLayout->addLayout(buttonLayout1, 3, 0, 1, -1);

    // this->connect4Widget->setLayout(layout);

    setCentralWidget(centralWidget);
    // this->connect4Widget->move(50, 50);
}

void MainWindow::onRestartButtonClicked() {
    this->connect4Widget->resetGame();
}

void MainWindow::onExitButtonClicked() {
    this->close();
}

void MainWindow::onPlayAsPlayerOneButtonClicked() {
    this->connect4Widget->playAsPlayerOne();
    this->playAsPlayerOneButton->setChecked(true);
    this->playAsPlayerTwoButton->setChecked(false);
}

void MainWindow::onPlayAsPlayerTwoButtonClicked() {
    this->connect4Widget->playAsPlayerTwo();
    this->playAsPlayerTwoButton->setChecked(true);
    this->playAsPlayerOneButton->setChecked(false);
}

MainWindow::~MainWindow() {
    delete this->connect4Widget;
    delete this->exitButton;
    delete this->restartButton;
    delete this->centralWidget;
}