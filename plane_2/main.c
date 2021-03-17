#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量定义
int gameover = 0;
int position_x,position_y;   //飞机位置
int bullet_x,bullet_y;   //子弹位置
int enemy_x,enemy_y;    //敌机位置
int width,high;     //游戏画面尺寸
int score;      //得分

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

    position_x = high/2;
    position_y = width/2;

    bullet_x = -1;
    bullet_y = position_y;

    enemy_x = 0;
    enemy_y = rand() % (width-4)+2;

    score = 0;

    HideCursor();
}

void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    int i,j;

    for(i = 0;(i < high)&&(!gameover); i++){
        for(j = 0;j < width; j++){
            if((i == position_x) && (j == position_y))
                printf("*");       //输出飞机
            else if(((i == position_x) && (j == position_y))||((i == position_x+1) && (j == position_y))
                    ||((i == position_x+1) && (j == position_y-1))||((i == position_x+1) && (j == position_y-2))
                    ||((i == position_x+1) && (j == position_y+1))||((i == position_x+1) && (j == position_y+2))
                    ||((i == position_x+2) && (j == position_y-1))||((i == position_x+2) && (j == position_y+1)))
                printf("*");
            else if ((i == bullet_x) && (j == bullet_y))
                printf("|");       //输出子弹|
            else if ((i == enemy_x) && (j == enemy_y))
                printf("@");       //输出敌机@
            else
                printf(" ");       //输出空格
        }
        printf("▌\n");      //&打印边界
    }
    for(j = 0;j < width; j++)
        printf("▄");
    printf("\n");
    printf("得分：%d \n", score);
    printf("按 L 键结束游戏\n");
}

void updateWithoutInput()   //Input irrelevant updates
{
    if(bullet_x > -1)
        bullet_x--;         //子弹上升

    //击中后得分加1，敌机重新生成，子弹消失
    if((bullet_x == enemy_x)&&(bullet_y == enemy_y)){
        score++;
        enemy_x = 0;
        enemy_y = rand() % (width-4)+2;
        bullet_x = -1;
    }
    //敌机撞上本机后敌机消失，得分-1
    if(((enemy_x == position_x) && (enemy_y == position_y))||((enemy_x == position_x+1) && (enemy_y == position_y))
        ||((enemy_x == position_x+1) && (enemy_y == position_y-1))||((enemy_x == position_x+1) && (enemy_y == position_y-2))
        ||((enemy_x == position_x+1) && (enemy_y == position_y+1))||((enemy_x == position_x+1) && (enemy_y == position_y+2))
        ||((enemy_x == position_x+2) && (enemy_y == position_y-1))||((enemy_x == position_x+2) && (enemy_y == position_y+1))){
        score--;
        enemy_x = 0;
        enemy_y = rand() % (width-4)+2;
        bullet_x = -1;
    }

    static int speed = 0;           //敌机下落速度因子
    if(enemy_x > high){             //敌机下落到最后则敌机消失，得分-1
        enemy_x = 0;
        enemy_y = rand() % (width-4)+2;
        score--;
    }
    else {
        if(speed < 8)
            speed++;
        else{
            enemy_x++;
            speed = 0;

        }
    }

    //击中后得分加1，敌机重新生成，子弹消失
    if((bullet_x == enemy_x)&&(bullet_y == enemy_y)){
        score++;
        enemy_x = 0;
        enemy_y = rand() % (width-4)+2;
        bullet_x = -1;
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
            if(position_y > 2)
                position_y--;
            break;
        case 's':
        case 'S':
            if(position_x < high - 3)
                position_x++;
            break;
        case 'd':
        case 'D':
            if(position_y < width - 3)
                position_y++;
            break;
        case 'w':
        case 'W':
            if(position_x > 2)
                position_x--;
            break;
        case ' ':
            bullet_x = position_x - 1;
            bullet_y = position_y;
            break;
        case 'L':
        case 'l':
            gameover = 1;
            printf("Game Over!\n");
        default:
            break;
        }
    }
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
