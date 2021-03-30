#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//ȫ�ֱ�������
int gameover = 0;       //��Ϸ�Ƿ����
int high,width;         //��Ϸ����ߴ�

int ball_x,ball_y;      //С������
int ball_vx,ball_vy;    //С���ٶ�vx��vy

int target_x,target_y;      //Ŀ������
int target_vx,target_vy;    //Ŀ���ٶ�

int position_x,position_y;           //������������
int radius;             //����뾶��С
int left,right;        //�������ұ߽�

int rebound_num;
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
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    int i,j;

    for(i = 0;(i < high)&&(!gameover); i++){
        for(j = 0;j < width + 1; j++){
            if(i == ball_x && j == ball_y)
                printf("O");        //��ӡС��
            else if((i == target_x) && (j == target_y))
                printf("#");        //��ӡĿ��
            else if((i == position_x) && (j >= left) && (j <= right))
                printf("*");        //��ӡ����
            else
                printf(" ");
        }
        printf("�U\n");      //��ӡ�ұ߽�
    }
    for(j = 0;j < width + 1; j++)
        printf("�{");        //��ӡ�±߽�
    printf("\n");

    printf("��������: %d ��\n", rebound_num);
    printf("�÷�: %d \n", score);
    printf("�� L ��������Ϸ\n");
}

void updateWithoutInput()   //Input irrelevant updates
{
    static int ball_speed = 0;   //�ٶ����ӣ�����С���ٶ�
    static int target_speed = 0;   //�ٶ����ӣ�����Ŀ���ٶ�

    //С���Ŀ��ײ������󷴵�
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

    //�����߽�󣬸ı��ٶȵķ���
    if(target_speed < 6){
        target_speed++;
    }else {
        target_speed = 0;
        //�����ٶȸ���Ŀ��λ��
        target_x += target_vx;
        target_y += target_vy;

        //�����߽�󣬸ı��ٶȵķ���
        if((target_x == 0) || (target_x == high - 1))
            target_vx = -target_vx;
        if((target_y == 0) || (target_y == width))
            target_vy = -target_vy;

        //����Ŀ���÷�+1,����������Ŀ��
        if(ball_x == target_x && ball_y == target_y){
            score++;
            target_x = 1;
            target_y = rand() % (width + 1);
        }
    }

    //�����߽�󣬸ı��ٶȵķ���
    if(ball_speed < 3){
        ball_speed++;
    }else {
        ball_speed = 0;
        //�����ٶȸ���С��λ��
        ball_x += ball_vx;
        ball_y += ball_vy;

        //�����߽�󣬸ı��ٶȵķ���
        if((ball_x == 0) || (ball_x == high - 1))
            ball_vx = -ball_vx;
        if((ball_y == 0) || (ball_y == width))
            ball_vy = -ball_vy;

        //����Ŀ���÷�+1,����������Ŀ��
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

    if(kbhit()){        //������ʱִ��
        input = getch();

        switch(input){     //���������ƶ������
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
