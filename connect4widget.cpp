#include "connect4widget.h"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QRadialGradient>
#include <QLabel>

#include <iostream>
#include <chrono>
#include <thread>

#define CIRCLE_SPACING 10
#define OUTER_BORDER_SPACING 20
#define BORDER_OFFSET OUTER_BORDER_SPACING/2
#define HALF_BORDER_OFFSET BORDER_OFFSET/2

Connect4Widget::Connect4Widget(QWidget* parent) :
    QWidget(parent),
    circleStates(cols, std::vector<int>(rows, 0)),
    hoveredCircle(-1, -1),
    gameStarted(false),
    currentPlayer(1),
    gameFinished(false),
    selectedPlayerId(1),
    twoPlayer(false) {
        setFixedSize(cols * (circleDiameter+CIRCLE_SPACING) + OUTER_BORDER_SPACING,
            rows * (circleDiameter+CIRCLE_SPACING) + OUTER_BORDER_SPACING);
        setMouseTracking(true);
}

Connect4Widget::~Connect4Widget() {}

void Connect4Widget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw column backgrounds.
    for (int col = 0; col < cols; col++) {
        int x = col*(circleDiameter + CIRCLE_SPACING) + HALF_BORDER_OFFSET;

        QLinearGradient columnGradient(x, 0, x + circleDiameter, 0);
        columnGradient.setColorAt(0.0, QColor("#a1c4fd")); // Dark blue.
        columnGradient.setColorAt(0.5, QColor("#d3e5ff")); // Light blue.
        columnGradient.setColorAt(1.0, QColor("#a1c4fd")); // Dark blue.

        painter.fillRect(x, HALF_BORDER_OFFSET, circleDiameter + CIRCLE_SPACING, height() - 2 * BORDER_OFFSET, columnGradient);
    }

    // Draw the circles on the board.
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            int x = col*(circleDiameter+CIRCLE_SPACING) + BORDER_OFFSET;
            int y = row*(circleDiameter+CIRCLE_SPACING) + BORDER_OFFSET;
            QRect circleRect(x, y, circleDiameter, circleDiameter);

            QRadialGradient gradient(circleRect.center(), circleDiameter / 2);
            if (circleStates[col][row] == 0 && !isCircleHovered(col, row)) {
                gradient.setColorAt(0, QColor(Qt::white).lighter(120));
                gradient.setColorAt(1, Qt::white);
                // painter.setBrush(Qt::noBrush);
            } else if (circleStates[col][row] == 1) {
                gradient.setColorAt(0, QColor(Qt::red).lighter(120));
                gradient.setColorAt(1, Qt::red);
                // painter.setBrush(Qt::red);
            } else if (circleStates[col][row] == 2) {
                gradient.setColorAt(0, QColor(Qt::yellow).lighter(120));
                gradient.setColorAt(1, Qt::yellow);
                // painter.setBrush(Qt::yellow);
            } else if (circleStates[col][row] == 3) {
                gradient.setColorAt(0, QColor(Qt::green).lighter(120));
                gradient.setColorAt(1, Qt::green);
                // painter.setBrush(Qt::blue);
            // } else if (circleStates[col][row] == 4) {
            //     painter.setBrush(Qt::gray);
            } else {
                if (this->currentPlayer == 1) {
                    gradient.setColorAt(0, QColor(Qt::red).lighter(175));
                    gradient.setColorAt(1, QColor(Qt::red).lighter(125));
                }
                if (this->currentPlayer == 2) {
                    gradient.setColorAt(0, QColor(Qt::yellow).lighter(175));
                    gradient.setColorAt(1, QColor(Qt::yellow).lighter(125));
                }
                // painter.setBrush(Qt::gray);
            }

            painter.setBrush(gradient);

            QPen pen (Qt::black, 2);
            painter.setPen(pen);

            painter.drawEllipse(circleRect);
            // painter.drawEllipse(x, y, circleDiameter, circleDiameter);

            // QPen borderPen(Qt::black, 2);
            // painter.setPen(borderPen);
            // painter.drawRect(BORDER_OFFSET, BORDER_OFFSET, this->width() - BORDER_OFFSET, this->height() - BORDER_OFFSET);
        }
    }
}

void Connect4Widget::playAsPlayerOne() {
    this->selectedPlayerId = 1;
    resetGame();
}

void Connect4Widget::playAsPlayerTwo() {
    this->selectedPlayerId = 2;
    resetGame();
}

bool Connect4Widget::insertToCol(int col) {
    std::cout << "insertToCol( " << col << ")" << std::endl;
    for (int i = this->rows - 1; i >= 0 ; i--) {
        std::cout << "Trying: [" << col << ", " << i << "]" << std::endl;
        if (this->circleStates[col][i] == 0) {
            this->circleStates[col][i] = this->currentPlayer;
            std::cout << "Insert success" << std::endl;
            update();
            return true;
        }
    }
    return false; // Can't insert to full column.
}

void Connect4Widget::mouseMoveEvent(QMouseEvent* event) {
    updateHoveredCircle(event->x(), event->y());
}

void Connect4Widget::leaveEvent(QEvent* event) {
    hoveredCircle = {-1, -1};
    update();
}

void Connect4Widget::updateHoveredCircle(int x, int y) {
    int col = (x - HALF_BORDER_OFFSET) / (circleDiameter+CIRCLE_SPACING);
    int row = (y - HALF_BORDER_OFFSET) / (circleDiameter+CIRCLE_SPACING);

    if (col >= 0 && col < cols && row >= 0 && row < rows && this->gameFinished != true) {
        for (int i = 0; i < this->rows; i++) {
            if (this->circleStates[col][i] == 0) {
                row = i;
            }
        }
        hoveredCircle = {col, row};
    } else {
        hoveredCircle = {-1, -1};
    }
    update();
}

bool Connect4Widget::isCircleHovered(int col, int row) const {
    return hoveredCircle.first == col && hoveredCircle.second == row;
}

void Connect4Widget::changePlayer() {
    if (this->currentPlayer == 1) {
        this->currentPlayer = 2;
        return;
    }
    if (this->currentPlayer == 2) {
        this->currentPlayer = 1;
        return;
    }
}

void Connect4Widget::computerMove() {
    if (gameFinished == false) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        bool attemptedMove = false;
        while (attemptedMove == false) {
            int randomMove = rand() % 7;
            attemptedMove = insertToCol(randomMove);
        }
        changePlayer();
        update();
    }
}

void Connect4Widget::mousePressEvent(QMouseEvent* event) {
    // Find out where the click happened.
    int col = (event->x() - HALF_BORDER_OFFSET) / (circleDiameter+CIRCLE_SPACING);
    int row = (event->y() - HALF_BORDER_OFFSET) / (circleDiameter+CIRCLE_SPACING);

    // Colour the circles based on which button was pressed.
    bool enterMove = false;
    if (gameFinished == false) {
        if (col >= 0 && col < cols && row >= 0 && row < rows) {
            std::cout << "[" << col << ", " << row << "]" << std::endl;
            enterMove = insertToCol(col);
            update();
        }
    }

    // Check for win conditions
    int winner = 0;

    // Check all horizontal wins.
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 5; j++) {
            int pos_owner = circleStates[i][j];
            if (pos_owner == 0) {
                continue;
            }
            bool mismatch = false;
            for (int k = 1; k < 4; k++) {
                if (pos_owner != circleStates[i+k][j]) {
                    mismatch = true;
                }
            }
            if (mismatch == true) {
                continue;
            }
            winner = pos_owner;
            for (int k = 0; k < 4; k++) {
                circleStates[i+k][j] = 3;
            }
            if (winner != 3) {
                break;
            }
        }
    }

    // Check all vertical wins.
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 2; j++) {
            int pos_owner = circleStates[i][j];
            if (pos_owner == 0) {
                continue;
            }
            bool mismatch = false;
            for (int k = 1; k < 4; k++) {
                if (pos_owner != circleStates[i][j+k]) {
                    mismatch = true;
                }
            }
            if (mismatch == true) {
                continue;
            }
            winner = pos_owner;
            for (int k = 0; k < 4; k++) {
                circleStates[i][j+k] = 3;
            }
            break;
        }
    }

    // Check all top-left to bottom-right wins.
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 2; j++) {
            int pos_owner = circleStates[i][j];
            if (pos_owner == 0) {
                continue;
            }
            bool mismatch = false;
            for (int k = 1; k < 4; k++) {
                if (pos_owner != circleStates[i+k][j+k]) {
                    mismatch = true;
                }
            }
            if (mismatch == true) {
                continue;
            }
            winner = pos_owner;
            for (int k = 0; k < 4; k++) {
                circleStates[i+k][j+k] = 3;
            }
            break;
        }
    }

    // Check all bottom-left to top-right wins.
    for (int i = 0; i <= 3; i++) {
        for (int j = 2; j <= 6; j++) {
            int pos_owner = circleStates[i][j];
            if (pos_owner == 0) {
                continue;
            }
            bool mismatch = false;
            for (int k = 1; k < 4; k++) {
                if (pos_owner != circleStates[i+k][j-k]) {
                    mismatch = true;
                }
            }
            if (mismatch == true) {
                continue;
            }
            winner = pos_owner;
            for (int k = 0; k < 4; k++) {
                circleStates[i+k][j-k] = 3;
            }
            break;
        }
    }

    if (winner != 0) {
        this->gameFinished = true;
    }

    if (enterMove == true) {
        changePlayer();
        computerMove();
    }
}

void Connect4Widget::resetGame() {
    for (int col = 0; col < this->cols; ++col) {
        for (int row = 0; row < this->rows; ++row) {
            this->circleStates[col][row] = 0;
        }
    }

    this->gameFinished = false;

    if (this->selectedPlayerId == 1) {
        this->currentPlayer = 1;
    } else {
        this->currentPlayer = 1;
        computerMove();
    }

    update();
}