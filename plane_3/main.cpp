#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>

#define High    25          //定义游戏尺寸
#define Width   40
#define EnemyNum 5 // 敌机个数

using namespace std;

//全局变量定义
int position_x,position_y;
int enemy_x[EnemyNum],enemy_y[EnemyNum];  // 敌机位置
int canvas[High][Width] = {0}; // 二维数组存储游戏画布中对应的元素
                        // 0为空格，1为飞机*，2为子弹|，3为敌机@
int score; // 得分
int BulletWidth; // 子弹宽度
int EnemyMoveSpeed; // 敌机移动速度

//函数功能：将光标移动到(x,y)位置
void gotoxy(int x,int y);
//函数功能：用于隐藏光标
void HideCursor();


//函数功能:初始化游戏数据
void startup()     //Initialization data
{
    position_x = High - 1;
    position_y = Width/2;
    canvas[position_x][position_y] = 1;

    int k;
	for (k=0;k<EnemyNum;k++)
	{
		enemy_x[k] = 0;
		enemy_y[k] = rand()%Width;
		canvas[enemy_x[k]][enemy_y[k]] = 3;
	}
	score = 0;
	BulletWidth = 0;
	EnemyMoveSpeed = 10;

    HideCursor();
}

//函数功能：打印游戏界面
void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    for(int i = 0;i < High;i++){
        for(int j = 0;j < Width;j++){
            if (canvas[i][j]==0)
				printf(" ");   //   输出空格
			else if (canvas[i][j]==1)
				printf("*");   //   输出飞机*
			else if (canvas[i][j]==2)
				printf("|");   //   输出子弹|
			else if (canvas[i][j]==3)
				printf("@");   //  输出飞机@
        }
        printf("▌\n");      //&打印边界
    }
    for(int j = 0;j < Width; j++)
        printf("▄");
    printf("\n得分：%d\n",score);
    printf("按L键暂停\n");
	Sleep(20);
}

//与输入无关的数据更新
void updateWithoutInput()   //Input irrelevant updates
{
    int i,j,k;
    int bulletFlag = 0;//判断子弹是否击中敌机
    static int speed = 0;
	if (speed < EnemyMoveSpeed)
		speed++;
    for (k=0;k<EnemyNum;k++)
    {
        if ((position_x==enemy_x[k]) && (position_y==enemy_y[k]))  // 敌机撞到我机
        {
            printf("失败！\n");
            Sleep(3000);
            system("pause");
            exit(0);
        }

        if (speed == EnemyMoveSpeed)
        {
            // 敌机下落
            for (k=0;k<EnemyNum;k++)
            {
                canvas[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k]++;
                speed = 0;
                if (enemy_x[k]>=High)   // 敌机跑出显示屏幕
                {
                    enemy_x[k] = 0;           // 产生新的飞机
                    enemy_y[k] = rand()%Width;
                    canvas[enemy_x[k]][enemy_y[k]] = 3;
                    score--;  // 减分
                }else
                    canvas[enemy_x[k]][enemy_y[k]] = 3;
            }
        }
    }
	for (i=0;i<High;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (canvas[i][j]==2)
			{
                for (k=0;k<EnemyNum;k++)
                {
                    if ((i==enemy_x[k]) && (j==enemy_y[k]))  // 子弹击中敌机
                    {
                        score++;                // 分数加1
                        canvas[i][j] = 0;
                        enemy_x[k] = 0;           // 产生新的飞机
                        enemy_y[k] = rand()%Width;
                        canvas[enemy_x[k]][enemy_y[k]] = 3;
                        bulletFlag = 1;
                        break;
                    }
                }
                if(!bulletFlag)
                {
                    // 子弹向上移动
                    canvas[i][j] = 0;
                    if (i>0)
                        canvas[i-1][j] = 2;
                    for (k=0;k<EnemyNum;k++)
                    {
                        if (((i-1)==enemy_x[k]) && (j==enemy_y[k]))  // 子弹击中敌机
                        {
                            score++;                // 分数加1
                            canvas[i-1][j] = 0;
                            enemy_x[k] = 0;           // 产生新的飞机
                            enemy_y[k] = rand()%Width;
                            canvas[enemy_x[k]][enemy_y[k]] = 3;
                            break;
                        }
                    }
                }
                bulletFlag = 0;
			}
		}
	}

	if (score%10 == 0 && EnemyMoveSpeed > 3)   // 达到一定积分后，敌机变快
        EnemyMoveSpeed = 10 - score/10;
    if (score%10 == 0)   // 达到一定积分后，子弹变厉害
        BulletWidth = score/10;
}
//与输入有关的数据更新
void updateWithInput()      //Input relevant updates
{
    char input;
    int left = position_y - BulletWidth;
    int right = position_y + BulletWidth;
    int k;

    if(kbhit()){        //当按键时执行
        input = getch();

        switch(input){     //按键控制移动、射击
        case 'a':
        case 'A':
            if(position_y > 0)
            {
                canvas[position_x][position_y] = 0;
                position_y--;
                canvas[position_x][position_y] = 1;
            }
            break;
        case 's':
        case 'S':
            if(position_x < High - 1)
            {
                canvas[position_x][position_y] = 0;
                position_x++;
                canvas[position_x][position_y] = 1;
            }
            break;
        case 'd':
        case 'D':
            if(position_y < Width - 1)
            {
                canvas[position_x][position_y] = 0;
                position_y++;
                canvas[position_x][position_y] = 1;
            }
            break;
        case 'w':
        case 'W':
            if(position_x > 0)
            {
                canvas[position_x][position_y] = 0;
                position_x--;
                canvas[position_x][position_y] = 1;
            }
            break;
        case ' ':
			if (left < 0)
				left = 0;
			if (right > Width-1)
				right = Width-1;
			for (k = left;k <= right;k++) // 发射散弹
				canvas[position_x-1][k] = 2; // 发射子弹的初始位置在飞机的正上方
            break;
        case 'L':
        case 'l':
            system("pause");
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
