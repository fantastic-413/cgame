#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//全局变量定义
int gameover = 0;       //游戏是否结束
int high,width;         //游戏画面尺寸

int ball_x,ball_y;      //小球坐标
int ball_vx,ball_vy;    //小球速度vx，vy

int target_x,target_y;      //目标坐标
int target_vx,target_vy;    //目标速度

int position_x,position_y;           //挡板中心坐标
int radius;             //挡板半径大小
int left,right;        //挡板左右边界

int rebound_num;
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
    width = 40;

    ball_x = 1;
    ball_y = rand() % (width + 1);

    ball_vx = 1;
    ball_vy = 1;

    target_x = 1;
    target_y = rand() % (width + 1);

    target_vx = 1;
    target_vy = 1;

    position_x = high - 1;
    position_y = width/2;
    radius = 8;
    left = position_y - radius;
    right = position_y + radius;

    rebound_num = 0;
    score = 0;

    HideCursor();
}

void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    int i,j;

    for(i = 0;(i < high)&&(!gameover); i++){
        for(j = 0;j < width + 1; j++){
            if(i == ball_x && j == ball_y)
                printf("O");        //打印小球
            else if((i == target_x) && (j == target_y))
                printf("#");        //打印目标
            else if((i == position_x) && (j >= left) && (j <= right))
                printf("*");        //打印挡板
            else
                printf(" ");
        }
        printf("║\n");      //打印右边界
    }
    for(j = 0;j < width + 1; j++)
        printf("▄");        //打印下边界
    printf("\n");

    printf("反弹次数: %d 次\n", rebound_num);
    printf("得分: %d \n", score);
    printf("按 L 键结束游戏\n");
}

void updateWithoutInput()   //Input irrelevant updates
{
    static int ball_speed = 0;   //速度因子，控制小球速度
    static int target_speed = 0;   //速度因子，控制目标速度

    //小球或目标撞到挡板后反弹
    if(((ball_x == position_x - 1)) && (ball_y >= left && ball_y <= right))
    {
        if(ball_vx > 0){
            ball_vx = -ball_vx;
        }
        if(ball_speed == 3)
                rebound_num++;
    }

    if(((target_x == position_x - 1)) && (target_y >= left && target_y <= right))
    {
        if(target_vx > 0){
            target_vx = -target_vx;
        }
        if(target_speed == 6)
                rebound_num++;
    }

    //碰到边界后，改变速度的方向
    if(target_speed < 6){
        target_speed++;
    }else {
        target_speed = 0;
        //根据速度更新目标位置
        target_x += target_vx;
        target_y += target_vy;

        //碰到边界后，改变速度的方向
        if((target_x == 0) || (target_x == high - 1))
            target_vx = -target_vx;
        if((target_y == 0) || (target_y == width))
            target_vy = -target_vy;

        //击中目标后得分+1,并重新生成目标
        if(ball_x == target_x && ball_y == target_y){
            score++;
            target_x = 1;
            target_y = rand() % (width + 1);
        }
    }

    //碰到边界后，改变速度的方向
    if(ball_speed < 3){
        ball_speed++;
    }else {
        ball_speed = 0;
        //根据速度更新小球位置
        ball_x += ball_vx;
        ball_y += ball_vy;

        //碰到边界后，改变速度的方向
        if((ball_x == 0) || (ball_x == high - 1))
            ball_vx = -ball_vx;
        if((ball_y == 0) || (ball_y == width))
            ball_vy = -ball_vy;

        //击中目标后得分+1,并重新生成目标
        if(ball_x == target_x && ball_y == target_y){
            score++;
            target_x = 1;
            target_y = rand() % (width + 1);
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
            if(position_y > 8)
                position_y--;
            break;
        case 's':
        case 'S':
            if(position_x < high - 1)
                position_x++;
            break;
        case 'd':
        case 'D':
            if(position_y < width - 8)
                position_y++;
            break;
        case 'w':
        case 'W':
            if(position_x > 2)
                position_x--;
            break;
        case 'L':
        case 'l':
            gameover = 1;
            printf("Game Over!\n");
        default:
            break;
        }
    }
    left = position_y - radius;
    right = position_y + radius;
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
