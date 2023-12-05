#ifndef CONNECT4WIDGET_H
#define CONNECT4WIDGET_H

#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <vector>

class Connect4Widget : public QWidget {
    Q_OBJECT
public:
    explicit Connect4Widget(QWidget* parent = nullptr);
    ~Connect4Widget();
    void resetGame();
    void playAsPlayerOne();
    void playAsPlayerTwo();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    static const int rows = 6;
    static const int cols = 7;
    static const int circleDiameter = 75;
    std::vector<std::vector<int>> circleStates;
    std::pair<int, int> hoveredCircle;
    bool gameStarted;
    int currentPlayer;
    bool gameFinished;
    int selectedPlayerId;
    bool twoPlayer = false;

    bool isCircleHovered(int col, int row) const;
    void updateHoveredCircle(int x, int y);
    bool insertToCol(int col);
    void changePlayer();
    void computerMove();
};

#endif // CONNECT4WIDGET_H