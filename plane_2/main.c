#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//ȫ�ֱ�������
int position_x,position_y;   //�ɻ�λ��
int bullet_x,bullet_y;   //�ӵ�λ��
int enemy_x,enemy_y;    //�л�λ��
int width,high;     //��Ϸ����ߴ�
int score;      //�÷�

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
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    int i,j;

    for(i = 0;i < high; i++){
        for(j = 1;j < width; j++){
            if((i == position_x) && (j == position_y))
                printf("*");       //����ɻ�*
            else if ((i == bullet_x) && (j == bullet_y))
                printf("|");       //����ӵ�|
            else if ((i == enemy_x) && (j == enemy_y))
                printf("@");       //����л�@
            else
                printf(" ");       //����ո�
        }
        printf("\n");
    }
    printf("�÷֣�%d ��\n", score);
}

void updateWithoutInput()   //Input irrelevant updates
{
    if(bullet_x > -1)
        bullet_x--;         //�ӵ�����

    //���к�÷ּ�1���л��������ɣ��ӵ���ʧ
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

    if(kbhit()){        //������ʱִ��
        input = getch();

        switch(input){     //���������ƶ������
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
