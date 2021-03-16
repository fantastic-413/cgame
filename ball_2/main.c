#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//全局变量定义
int gameover = 0;       //游戏是否结束
int high,width;         //游戏画面尺寸

int ball_x,ball_y;      //小球坐标
int ball_vx,ball_vy;    //小球速度vx，vy

int position;           //挡板中心坐标
int radius;             //挡板半径大小
int left,right;        //挡板左右边界

int score;              //得分



void gotoxy(int x,int y)  //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor()       //用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()     //Initialization data
{
    high = 25;
    width = 60;

    ball_x = 1;
    ball_y = width/2;

    ball_vx = 1;
    ball_vy = 1;

    position = width/2;
    radius = 8;
    left = position - radius;
    right = position + radius;

    score = 0;

    HideCursor();
}

void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    int i,j;

    //得分为负，游戏结束
    if(score < 0){
        system("cls");
        printf("GAME OVER! YOU LOSE!\n");
        gameover = 1;
    }

    for(i = 0;(i < high)&&(!gameover); i++){
        for(j = 0;j < width + 1; j++){
            if(i == ball_x && j == ball_y)
                printf("O");        //打印小球
            else if((i == high - 1) && (j >= left) && (j <= right))
                printf("*");        //打印挡板
            else
                printf(" ");
        }
        printf("║\n");      //打印右边界
    }
    for(j = 0;j < width + 1; j++)
        printf("▄");        //打印下边界
    printf("\n");

    printf("得分: %d \n", score);
}

void updateWithoutInput()   //Input irrelevant updates
{
    //碰到边界后，改变速度的方向
    static int speed = 0;   //速度因子，控制小球速度
    if(speed < 1){
        speed++;
    }else {
        speed = 0;
        //根据速度更新小球位置
        ball_x += ball_vx;
        ball_y += ball_vy;

        //碰到边界后，改变速度的方向
        if((ball_x == 1))
            ball_vx = -ball_vx;
        if(ball_x == high - 1){
            ball_vx = -ball_vx;
            score--;
        }
        if((ball_y == 0) || (ball_y == width))
            ball_vy = -ball_vy;

        //小球撞到挡板后反弹
        if(ball_x == high - 2 && (ball_y >= left && ball_y <= right))
        {
            ball_vx = -ball_vx;
            score++;
        }
    }
}

void updateWithInput()      //Input relevant updates
{
    char input;

    if(kbhit()){        //当按键时执行
        input = getch();

        switch(input){     //按键控制移动、射击
        case 'a':
        case 'A':
            if(position > 8)
                position--;
            break;
        case 'd':
        case 'D':
            if(position < width - 8)
                position++;
            break;
        default:
            break;
        }
    }
    left = position - radius;
    right = position + radius;
}

int main()
{
    startup();     //Initialization data
    while(!gameover)       //Game loop execution
    {
        show();     //Screen display
        updateWithoutInput();   //Input irrelevant updates
        updateWithInput();      //Input relevant updates
    }
    return 0;
}
