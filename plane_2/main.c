#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量定义
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
    high = 29;
    width = 120;

    position_x = high/2;
    position_y = width/2;

    bullet_x = -1;
    bullet_y = position_y;

    enemy_x = 0;
    enemy_y = position_y;

    score = 0;

    HideCursor();
}

void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    int i,j;

    for(i = 0;i < high; i++){
        for(j = 1;j < width; j++){
            if((i == position_x) && (j == position_y))
                printf("*");       //输出飞机*
            else if ((i == bullet_x) && (j == bullet_y))
                printf("|");       //输出子弹|
            else if ((i == enemy_x) && (j == enemy_y))
                printf("@");       //输出敌机@
            else
                printf(" ");       //输出空格
        }
        printf("\n");
    }
    printf("得分：%d 分\n", score);
}

void updateWithoutInput()   //Input irrelevant updates
{
    if(bullet_x > -1)
        bullet_x--;         //子弹上升

    //击中后得分加1，敌机重新生成，子弹消失
    if((bullet_x == enemy_x)&&(bullet_y == enemy_y)){
        score++;
        enemy_x = 0;
        enemy_y = rand() % width;
        bullet_x = -1;
    }

    static int speed = 0;
    if(enemy_x > high){
        enemy_x = 0;
        enemy_y = rand() % width;
    }
    else {
        if(speed < 5)
            speed++;
        else{
            enemy_x++;
            speed = 0;

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
            position_y--;
            break;
        case 's':
        case 'S':
            position_x++;
            break;
        case 'd':
        case 'D':
            position_y++;
            break;
        case 'w':
        case 'W':
            position_x--;
            break;
        case ' ':
            bullet_x = position_x - 1;
            bullet_y = position_y;
            break;
        default:
            break;
        }
    }
}

int main()
{
    startup();     //Initialization data
    while(1)       //Game loop execution
    {
        show();     //Screen display
        updateWithoutInput();   //Input irrelevant updates
        updateWithInput();      //Input relevant updates
    }
    return 0;
}
