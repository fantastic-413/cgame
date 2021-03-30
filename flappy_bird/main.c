#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//全局变量定义
int high,width;         //游戏画面尺寸

int bird_x,bird_y;      //小球坐标

int barl_y,barl_xTop,barl_xDown;      //障碍物坐标

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

    bird_x = 0;
    bird_y = width/5;

    barl_y = width - 1;
    barl_xTop = rand()%(high-16) + 8;
    if(barl_xTop <= high / 2)
    {
        barl_xDown = barl_xTop;
        barl_xTop -= 6;
    }else
        barl_xDown = barl_xTop + 6;

    score = 0;

    HideCursor();
}

void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    int i,j;

    for(i = 0;i < high; i++){
        for(j = 0;j < width + 1; j++){
            if(i == bird_x && j == bird_y)
                printf("@");        //输出小鸟@
            else if((j == barl_y) && (i <= barl_xTop || i>= barl_xDown))
                printf("*");        //输出障碍物*
            else
                printf(" ");
        }
        printf("║\n");      //打印右边界
    }
    for(j = 0;j < width + 1; j++)
        printf("▄");        //打印下边界
    printf("\n");

    printf("得分: %d \n", score);
    printf("按 L 键结束游戏\n");
}

void updateWithoutInput()   //Input irrelevant updates
{
    if(bird_x < high)
        bird_x++;
    else{
        printf("Game Over!\n");
        exit(0);
    }

    //障碍物移动与重新生成
    if(barl_y > 0)
        barl_y--;
    else
    {
        barl_y = width - 1;
        barl_xTop = rand()%(high-16) + 8;
        if(barl_xTop <= high / 2)
        {
            barl_xDown = barl_xTop;
            barl_xTop -= 6;
        }else
            barl_xDown = barl_xTop + 6;
    }

    if(bird_y == barl_y)
    {
        if(bird_x > barl_xTop && bird_x < barl_xDown)
            score++;
        else{
            printf("Game Over!\n");
            exit(0);
        }
    }
    Sleep(150);
}

void updateWithInput()      //Input relevant updates
{
    char input;

    if(kbhit()){        //当按键时执行
        input = getch();

        switch(input){     //按键控制移动、射击
        case ' ':
            if(bird_x > 1)
                bird_x -= 2;
            else if(bird_x == 1)
                bird_x--;
            break;
        case 'L':
        case 'l':
            printf("Game Over!\n");
            exit(0);
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

