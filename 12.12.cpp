#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>
#define MAX_SCORE 10000

#define SIZE 19
#define CELL_SIZE 40
#define WINDOW_WIDTH (SIZE * CELL_SIZE)
#define WINDOW_HEIGHT (SIZE * CELL_SIZE)

char board[SIZE][SIZE];
bool playerXTurn = true;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void init_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void draw_board(){  //绘制棋盘 
    setlinecolor(BLACK);
    setfillcolor(RGB(255, 214, 170)); 
    solidrectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    setlinestyle(PS_SOLID, 2);
    for (int i = 0; i < SIZE; i++) {
        line(CELL_SIZE / 2, CELL_SIZE / 2 + i * CELL_SIZE, WINDOW_WIDTH - CELL_SIZE / 2, CELL_SIZE / 2 + i * CELL_SIZE);
        line(CELL_SIZE / 2 + i * CELL_SIZE, CELL_SIZE / 2, CELL_SIZE / 2 + i * CELL_SIZE, WINDOW_HEIGHT - CELL_SIZE / 2);
    }
}

void draw_piece(int x, int y) {//绘制棋子 
    if (playerXTurn) {
        setfillcolor(BLACK);
        setlinecolor(BLACK);
    } else {
        setfillcolor(WHITE);
        setlinecolor(WHITE);
    }
    fillcircle((x+1.5 ) * CELL_SIZE, (y+1.5 ) * CELL_SIZE, CELL_SIZE / 3);
}
int se;

void draw_buttons() {
	if(se==1){
	
    setfillcolor(LIGHTGRAY);
    fillrectangle(10, 10, 90, 40);
    settextstyle(20, 0, _T("宋体"));
    outtextxy(30, 20, "PvP");
}
	if(se==0||se==3){
	
    setfillcolor(LIGHTGRAY);
    fillrectangle(110, 10, 190, 40);
    settextstyle(20, 0, _T("宋体"));
    outtextxy(130, 20, "PvE");
}
	if(se==2){
		setfillcolor(LIGHTGRAY);
    	fillrectangle(210, 10, 290, 40);
    	settextstyle(20, 0, _T("宋体"));
    	outtextxy(220, 20, "replay");
	}
}


void handle_button_click(int x, int y) {
    if (x+2 >= 10 && x <= 90 && y >= 10 && y <= 40) {
        
    } else if (x >= 110 && x <= 190 && y >= 10 && y <= 40) {
       
        // 重新绘制游戏界面
        draw_board();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != ' ') {
                    draw_piece(j, i);
                }
            }
        }
    }
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

int evaluate(int x, int y, char player) {
    int score = 0;
    // 横向检查
    for (int i = max(0, x - 4); i <= min(SIZE - 5, x); i++) {
        int count = 0;
        for (int j = i; j < i + 5; j++) {
            if (board[y][j] == player) {
                count++;
            } else if (board[y][j] != ' ') {
                count = 0;
                break;
            }
        }
        if (count > 0) {
            score += pow(10, count - 1);
        }
    }
    // 纵向检查
    for (int i = max(0, y - 4); i <= min(SIZE - 5, y); i++) {
        int count = 0;
        for (int j = i; j < i + 5; j++) {
            if (board[j][x] == player) {
                count++;
            } else if (board[j][x] != ' ') {
                count = 0;
                break;
            }
        }
        if (count > 0) {
            score += pow(10, count - 1);
        }
    }
    // 左上到右下斜向检查
    for (int i = max(x - 4, 0), j = max(y - 4, 0); i <= min(x, SIZE - 5) && j <= min(y, SIZE - 5); i++, j++) {
        int count = 0;
        for (int k = 0; k < 5; k++) {
            if (board[j + k][i + k] == player) {
                count++;
            } else if (board[j + k][i + k] != ' ') {
                count = 0;
                break;
            }
        }
        if (count > 0) {
            score += pow(10, count - 1);
        }
    }
    // 左下到右上斜向检查
    for (int i = max(x - 4, 0), j = min(y + 4, SIZE - 1); i <= min(x, SIZE - 5) && j >= max(4, y); i++, j--) {
        int count = 0;
        for (int k = 0; k < 5; k++) {
            if (board[j - k][i + k] == player) {
                count++;
            } else if (board[j - k][i + k] != ' ') {
                count = 0;
                break;
            }
        }
        if (count > 0) {
            score += pow(10, count - 1);
        }
    }
    return score;
}




void computer_move(int lastX, int lastY) {
    // 生成上一个玩家落子周围的八个空位置
    int availableMoves[8][2] = {
        {lastX - 1, lastY - 1},
        {lastX, lastY - 1},
        {lastX + 1, lastY - 1},
        {lastX - 1, lastY},
        {lastX + 1, lastY},
        {lastX - 1, lastY + 1},
        {lastX, lastY + 1},
        {lastX + 1, lastY + 1}
    };
    // 随机选择一个可用位置进行落子
    srand(time(NULL));
    int index;
    do {
        index = rand() % 8;
    } while (availableMoves[index][0] < 0 || availableMoves[index][0] >= SIZE || availableMoves[index][1] < 0 || availableMoves[index][1] >= SIZE || board[availableMoves[index][1]][availableMoves[index][0]] != ' ');

    int x = availableMoves[index][0];
    int y = availableMoves[index][1];

    board[y][x] = 'O';
    draw_piece(x, y);
    if (check_win(x, y, 'O')) {
        char message[20];
        sprintf(message, "计算机获胜!");
        outtextxy(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2, message);
    }
    playerXTurn = true;
}

void computer_move1(int lastX, int lastY) {
    // 生成上一个玩家落子周围的空位置
    int availableMoves[SIZE * SIZE][2];
    int numMoves = 0;
    for (int i = max(0, lastY - 1); i <= min(SIZE - 1, lastY + 1); i++) {
        for (int j = max(0, lastX - 1); j <= min(SIZE - 1, lastX + 1); j++) {
            if (board[i][j] == ' ') {
                availableMoves[numMoves][0] = j;
                availableMoves[numMoves][1] = i;
                numMoves++;
            }
        }
    }
    // 如果没有可用位置，随机选择一个空位置
    if (numMoves == 0) {
        do {
            int x = rand() % SIZE;
            int y = rand() % SIZE;
            if (board[y][x] == ' ') {
                availableMoves[0][0] = x;
                availableMoves[0][1] = y;
                numMoves = 1;
                break;
            }
        } while (true);
    }
    // 对可用位置进行评估，选择得分最高的位置进行落子
    int bestScore = -9999;
    int bestMove[2];
    for (int i = 0; i < numMoves; i++) {
        int x = availableMoves[i][0];
        int y = availableMoves[i][1];
        if (board[y][x] == ' ') {
            int score = evaluate(x,y,'X');
            if (score > bestScore) {
                bestScore = score;
                bestMove[0] = x;
                bestMove[1] = y;
            }
        }
    }
    int x = bestMove[0];
    int y = bestMove[1];
    board[y][x] = 'O';
    draw_piece(x, y);
    if (check_win(x, y, 'O')) {
        char message[20];
        sprintf(message, "计算机获胜!");
        outtextxy(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2, message);
    }
    playerXTurn = true;
}


//pvp
void start_pvp_game() {
    MessageBox(GetHWnd(), "PVP mode selected", "Button Clicked", MB_OK);
    MOUSEMSG mouse;

    while (true) {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONDOWN) {
            int x = mouse.x / CELL_SIZE - 1;
            int y = mouse.y / CELL_SIZE - 1;
            handle_button_click(x,y); 
			printf("(%d,%d)",x+2,y+2) ;    
			
			if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[y][x] == ' ') {
                board[y][x] = playerXTurn ? 'X' : 'O';
                draw_piece(x, y);
                printf("  %c\n",playerXTurn ? 'X' : 'O');
                char message[20];
                    sprintf(message, "轮到%c下!", playerXTurn ? 'O' : 'X');
                    outtextxy(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, message);
                if (check_win(x, y, playerXTurn ? 'X' : 'O')) {
                    char message[20];
                    sprintf(message, "    玩家%c 获胜!", playerXTurn ? 'X' : 'O');
                    outtextxy(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2, message);
                    break;
                }
                playerXTurn = !playerXTurn;
                //保存对局信息到文件
    FILE* file = fopen("game.txt", "a");
    if (file != NULL) {
    	
            fprintf(file, "%d %d   \n", x+2,y+2);
        fclose(file);
    } else {
        printf("Unable to open file\n");
    }
            }
        }
}
}
// PVE 函数
void start_pve_game() {
    MessageBox(GetHWnd(), "PVE mode selected", "Button Clicked", MB_OK);
    MOUSEMSG mouse;
 
    while (true) {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONDOWN) {
            int x = mouse.x / CELL_SIZE - 1;
            int y = mouse.y / CELL_SIZE - 1;
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[y][x] == ' ') {
                board[y][x] = 'X';
                draw_piece(x, y);
                printf("(%d,%d)",x+2,y+2);
                //保存对局信息到文件
    FILE* file = fopen("game.txt", "a");
    if (file != NULL) {
        	
            fprintf(file, "%d %d  \n", x+2,y+2);
        
        fclose(file);
    } else {
        printf("Unable to open file\n");
    }
                printf("  %c\n",playerXTurn ? 'X' : 'O');
                if (check_win(x, y, 'X')) {
                    char message[20];
                    sprintf(message, "玩家获胜!");
                    outtextxy(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2, message);
                    break;
                }
                playerXTurn = false;
                computer_move1(x,y);
                
                
        }
    }
}
}

void start_pve_game1() {
    MessageBox(GetHWnd(), "PVE mode selected", "Button Clicked", MB_OK);
    MOUSEMSG mouse;
 
    while (true) {
        mouse = GetMouseMsg();
        if (mouse.uMsg == WM_LBUTTONDOWN) {
            int x = mouse.x / CELL_SIZE - 1;
            int y = mouse.y / CELL_SIZE - 1;
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[y][x] == ' ') {
                board[y][x] = 'X';
                draw_piece(x, y);
                printf("(%d,%d)",x+2,y+2);
                //保存对局信息到文件
    FILE* file = fopen("game.txt", "a");
    if (file != NULL) {
        	
            fprintf(file, "%d %d  \n", x+2,y+2);
        
        fclose(file);
    } else {
        printf("Unable to open file\n");
    }
                printf("  %c\n",playerXTurn ? 'X' : 'O');
                if (check_win(x, y, 'X')) {
                    char message[20];
                    sprintf(message, "玩家获胜!");
                    outtextxy(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2, message);
                    break;
                }
                playerXTurn = false;
                computer_move1(x,y);
                
                
        }
    }
}
}

//读取文件 
void load_game_from_file(const char* filename, int moves[][2], int* numMoves) {
    FILE* file = fopen(filename, "r");
    *numMoves = 0;
    if (file != NULL) {
        while (fscanf(file, "%d %d\n", &moves[*numMoves][0], &moves[*numMoves][1]) == 2) {
            (*numMoves)++;
        }
        fclose(file);
    } else {
        printf("Unable to open file\n");
    }
}

// 函数：对局回放
void replay_game(int moves[][2], int numMoves) {
    for (int i = 0; i < numMoves; i++) {
        int x = moves[i][0];
        int y = moves[i][1];
        draw_piece(x,y);
        playerXTurn = !playerXTurn;
    }
}
        

int main() {
	printf("输入0代表pve(易)，1代表pvp, 2代表对局回放，3代表pve(难)");
	scanf("%d",&se);
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_board();
    draw_board();
    draw_buttons();

    if(se==1){
    	start_pvp_game();
	}
	if(se==0){
		start_pve_game();
	}   
	if(se==2){
    // 对局回放
    int loadedMoves[SIZE * SIZE][2];
    int loadedNumMoves;
    load_game_from_file("game.txt", loadedMoves, &loadedNumMoves);

    // 对局回放
    replay_game(loadedMoves, loadedNumMoves*3); 
    
}
   if(se==3){
   	start_pve_game1();
   }
    _getch();
    system("pause");
    return 0;
}

