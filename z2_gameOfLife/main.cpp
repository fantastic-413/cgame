#include<iostream>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#define HIGH    35          //定义游戏尺寸
#define WIDTH   80

using namespace std;

//全局变量定义
int cells[HIGH][WIDTH];
int speed = 256;

//函数功能：将光标移动到(x,y)位置
void gotoxy(int x,int y);
//函数功能：用于隐藏光标
void HideCursor();


//函数功能:初始化游戏数据
void startup()     //Initialization data
{
    //初始化细胞
    for(int i = 0;i < HIGH;i++){
        for(int j = 0;j < WIDTH;j++){
            cells[i][j] = rand() % 2;
        }
    }

    HideCursor();
}

//函数功能：打印游戏界面
void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    for(int i = 0;i < HIGH;i++){
        for(int j = 0;j < WIDTH;j++){
            if(cells[i][j] == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("按下 A 或 D 键加快速度\n");
    printf("按下 W 或 S 键减慢速度\n");
}

//与输入无关的数据更新
void updateWithoutInput()   //Input irrelevant updates
{
    int neibour_liveNum;
    int tempCells[HIGH][WIDTH];

    for(int i = 0;i < HIGH;i++){
        for(int j = 0;j < WIDTH;j++){
                neibour_liveNum = 0;
                //判断细胞生死
                if(i != 0){
                    neibour_liveNum += cells[i-1][j];
                    if(j != 0)
                        neibour_liveNum += cells[i-1][j-1];
                    if(j != WIDTH - 1)
                        neibour_liveNum += + cells[i-1][j+1];
                }
                if(i != HIGH){
                    neibour_liveNum += cells[i+1][j];
                    if(j != 0)
                        neibour_liveNum += cells[i+1][j-1];
                    if(j != WIDTH - 1)
                        neibour_liveNum += + cells[i+1][j+1];
                }
                if(j != 0){
                    neibour_liveNum += cells[i][j-1];
                }
                if(j != WIDTH - 1){
                    neibour_liveNum += cells[i][j+1];
                }
                //进行细胞更替
                if(neibour_liveNum == 3)
                    tempCells[i][j] = 1;
                else if(neibour_liveNum == 2)
                    tempCells[i][j] = cells[i][j];
                else
                    tempCells[i][j] = 0;
        }
    }

    for(int i = 0;i < HIGH;i++){
        for(int j = 0;j < WIDTH;j++){
            cells[i][j] = tempCells[i][j];
        }
    }

    Sleep(speed);
}
//与输入有关的数据更新
void updateWithInput()      //Input relevant updates
{
    if (kbhit())
	{
		if ((GetAsyncKeyState(0x41) & 0x8000) ? 1 : 0)//a
            if(speed != 1)
                speed /= 2;
		else if ((GetAsyncKeyState(0x44) & 0x8000) ? 1 : 0)//d
            if(speed != 1)
                speed /= 2;
		if ((GetAsyncKeyState(0x57) & 0x8000) ? 1 : 0)//w
            speed *= 2;
		else if ((GetAsyncKeyState(0x53) & 0x8000) ? 1 : 0)//s
            speed *= 2;
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	fflush(stdin);
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


//函数功能：将光标移动到(x,y)位置
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

//函数功能：用于隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
