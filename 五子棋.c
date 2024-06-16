#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define SIZE 19
#define CELL_SIZE 40
#define WINDOW_WIDTH (SIZE * CELL_SIZE)
#define WINDOW_HEIGHT (SIZE * CELL_SIZE)

char board[SIZE][SIZE];
bool playerXTurn = true;

void init_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void draw_board() {
    setlinecolor(BLACK);
    setfillcolor(RGB(255, 214, 170)); // 设置棋盘背景色
    solidrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    setlinestyle(PS_SOLID, 2);
    for (int i = 0; i < SIZE; i++) {
        line(CELL_SIZE / 2, CELL_SIZE / 2 + i * CELL_SIZE, WINDOW_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + i * CELL_SIZE);
        line(CELL_SIZE / 2 + i * CELL_SIZE, CELL_SIZE / 2, CELL_SIZE / 2 + i * CELL_SIZE, WINDOW_HEIGHT - CELL_SIZE / 2);
    }
}

void draw_piece(int x, int y) {
    if (playerXTurn) {
        setfillcolor(BLACK);
        setlinecolor(BLACK);
    } else {
        setfillcolor(WHITE);
        setlinecolor(WHITE);
    }
    fillcircle((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE, CELL_SIZE / 3);
}


bool check_win(int x, int y, char player) {
    int count;

    // 检查水平方向
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (x + i < SIZE && board[y][x + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (x - i >= 0 && board[y][x - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return true;
    }

    // 检查垂直方向
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (y + i < SIZE && board[y + i][x] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (y - i >= 0 && board[y - i][x] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return true;
    }

    // 检查对角线方向
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (x + i < SIZE && y + i < SIZE && board[y + i][x + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (x - i >= 0 && y - i >= 0 && board[y - i][x - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return true;
    }

    // 检查反对角线方向
    count = 1;
    for (int i = 1; i < 5; i++) {
        if (x + i < SIZE && y - i >= 0 && board[y - i][x + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 5; i++) {
        if (x - i >= 0 && y + i < SIZE && board[y + i][x - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 5) {
        return true;
    }

    return false;
}


int main() {
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_board();
    draw_board();

    MOUSEMSG mouse;
    while (true) {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONDOWN) {
            int x = mouse.x / CELL_SIZE - 1;
            int y = mouse.y / CELL_SIZE - 1;
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[y][x] == ' ') {
                board[y][x] = playerXTurn ? 'X' : 'O';
                draw_piece(x, y);
                if (check_win(x, y, playerXTurn ? 'X' : 'O')) {
                    char message[20];
                    sprintf(message, "Player %c wins!", playerXTurn ? 'X' : 'O');
                    outtextxy(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2, message);
                    break;
                }
                playerXTurn = !playerXTurn;
            }
        }
    }

    _getch();
    closegraph();
    return 0;
}

