#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//ȫ�ֱ�������
int gameover = 0;       //��Ϸ�Ƿ����
int high,width;         //��Ϸ����ߴ�

int ball_x,ball_y;      //С������
int ball_vx,ball_vy;    //С���ٶ�vx��vy

int position;           //������������
int radius;             //����뾶��С
int left,right;        //�������ұ߽�

int score;              //�÷�



void gotoxy(int x,int y)  //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor()       //�������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
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
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    int i,j;

    //�÷�Ϊ������Ϸ����
    if(score < 0){
        system("cls");
        printf("GAME OVER! YOU LOSE!\n");
        gameover = 1;
    }

    for(i = 0;(i < high)&&(!gameover); i++){
        for(j = 0;j < width + 1; j++){
            if(i == ball_x && j == ball_y)
                printf("O");        //��ӡС��
            else if((i == high - 1) && (j >= left) && (j <= right))
                printf("*");        //��ӡ����
            else
                printf(" ");
        }
        printf("�U\n");      //��ӡ�ұ߽�
    }
    for(j = 0;j < width + 1; j++)
        printf("�{");        //��ӡ�±߽�
    printf("\n");

    printf("�÷�: %d \n", score);
}

void updateWithoutInput()   //Input irrelevant updates
{
    //�����߽�󣬸ı��ٶȵķ���
    static int speed = 0;   //�ٶ����ӣ�����С���ٶ�
    if(speed < 1){
        speed++;
    }else {
        speed = 0;
        //�����ٶȸ���С��λ��
        ball_x += ball_vx;
        ball_y += ball_vy;

        //�����߽�󣬸ı��ٶȵķ���
        if((ball_x == 1))
            ball_vx = -ball_vx;
        if(ball_x == high - 1){
            ball_vx = -ball_vx;
            score--;
        }
        if((ball_y == 0) || (ball_y == width))
            ball_vy = -ball_vy;

        //С��ײ������󷴵�
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

    if(kbhit()){        //������ʱִ��
        input = getch();

        switch(input){     //���������ƶ������
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
