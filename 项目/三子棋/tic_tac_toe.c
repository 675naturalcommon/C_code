#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 第7章：综合项目实践
 * 7.3 三子棋游戏
 */

#define BOARD_SIZE 3

// 游戏棋盘结构
typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    int currentPlayer;
} TicTacToeGame;

// 初始化游戏
void initGame(TicTacToeGame *game) {
    // 初始化棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = ' ';
        }
    }

    // 随机选择先手玩家
    game->currentPlayer = rand() % 2;
}

// 显示棋盘
void displayBoard(const TicTacToeGame *game) {
    printf("\n当前棋盘状态:\n");
    printf("   1   2   3\n");
    printf("A | B | C\n");
    printf("---|---|---\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %c | %c | %c\n",
               game->board[i][0], game->board[i][1], game->board[i][2]);
        if (i < BOARD_SIZE - 1) {
            printf("---|---|---\n");
        }
    }

    printf("\n当前玩家: %c\n", game->currentPlayer == 0 ? 'X' : 'O');
}

// 检查获胜条件
int checkWin(const TicTacToeGame *game) {
    // 检查行
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[i][0] != ' ' &&
            game->board[i][0] == game->board[i][1] &&
            game->board[i][1] == game->board[i][2]) {
            return game->board[i][0];
        }
    }

    // 检查列
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[0][i] != ' ' &&
            game->board[0][i] == game->board[1][i] &&
                game->board[1][i] == game->board[2][i]) {
            return game->board[0][i];
        }
    }

    // 检查对角线
    if (game->board[0][0] != ' ' &&
        game->board[0][0] == game->board[1][1] &&
            game->board[1][1] == game->board[2][2]) {
        return game->board[0][0];
    }

    if (game->board[0][2] != ' ' &&
        game->board[0][2] == game->board[1][1] &&
            game->board[1][1] == game->board[2][0]) {
        return game->board[0][2];
    }

    return ' ';
}

// 下棋
void makeMove(TicTacToeGame *game, int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        printf("无效的位置！\n");
        return;
    }

    if (game->board[row][col] != ' ') {
        printf("该位置已被占用！\n");
        return;
    }

    game->board[row][col] = game->currentPlayer == 0 ? 'X' : 'O';

    // 切换玩家
    game->currentPlayer = 1 - game->currentPlayer;
}

// 主游戏循环
void playTicTacToe() {
    TicTacToeGame game;
    initGame(&game);

    printf("欢迎来到三子棋游戏！\n");
    printf("玩家X和O轮流下棋，率先连成一条线的玩家获胜。\n");

    while (checkWin(&game) == ' ') {
        displayBoard(&game);

        int row, col;
        printf("请玩家%c下棋 (行 0-2, 列 0-2): ", game->currentPlayer == 0 ? 'X' : 'O');
        scanf("%d %d", &row, &col);
        makeMove(&game, row, col);
    }

    displayBoard(&game);

    char winner = checkWin(&game);
    if (winner == 'X') {
        printf("玩家X获胜！\n");
    } else if (winner == 'O') {
        printf("玩家O获胜！\n");
    } else {
        printf("平局！\n");
    }
}
