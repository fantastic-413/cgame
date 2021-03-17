#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//ȫ�ֱ�������
int gameover = 0;
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
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    int i,j;

    for(i = 0;(i < high)&&(!gameover); i++){
        for(j = 0;j < width; j++){
            if((i == position_x) && (j == position_y))
                printf("*");       //����ɻ�
            else if(((i == position_x) && (j == position_y))||((i == position_x+1) && (j == position_y))
                    ||((i == position_x+1) && (j == position_y-1))||((i == position_x+1) && (j == position_y-2))
                    ||((i == position_x+1) && (j == position_y+1))||((i == position_x+1) && (j == position_y+2))
                    ||((i == position_x+2) && (j == position_y-1))||((i == position_x+2) && (j == position_y+1)))
                printf("*");
            else if ((i == bullet_x) && (j == bullet_y))
                printf("|");       //����ӵ�|
            else if ((i == enemy_x) && (j == enemy_y))
                printf("@");       //����л�@
            else
                printf(" ");       //����ո�
        }
        printf("��\n");      //&��ӡ�߽�
    }
    for(j = 0;j < width; j++)
        printf("�{");
    printf("\n");
    printf("�÷֣�%d \n", score);
    printf("�� L ��������Ϸ\n");
}

void updateWithoutInput()   //Input irrelevant updates
{
    if(bullet_x > -1)
        bullet_x--;         //�ӵ�����

    //���к�÷ּ�1���л��������ɣ��ӵ���ʧ
    if((bullet_x == enemy_x)&&(bullet_y == enemy_y)){
        score++;
        enemy_x = 0;
        enemy_y = rand() % (width-4)+2;
        bullet_x = -1;
    }
    //�л�ײ�ϱ�����л���ʧ���÷�-1
    if(((enemy_x == position_x) && (enemy_y == position_y))||((enemy_x == position_x+1) && (enemy_y == position_y))
        ||((enemy_x == position_x+1) && (enemy_y == position_y-1))||((enemy_x == position_x+1) && (enemy_y == position_y-2))
        ||((enemy_x == position_x+1) && (enemy_y == position_y+1))||((enemy_x == position_x+1) && (enemy_y == position_y+2))
        ||((enemy_x == position_x+2) && (enemy_y == position_y-1))||((enemy_x == position_x+2) && (enemy_y == position_y+1))){
        score--;
        enemy_x = 0;
        enemy_y = rand() % (width-4)+2;
        bullet_x = -1;
    }

    static int speed = 0;           //�л������ٶ�����
    if(enemy_x > high){             //�л����䵽�����л���ʧ���÷�-1
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

    //���к�÷ּ�1���л��������ɣ��ӵ���ʧ
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

    if(kbhit()){        //������ʱִ��
        input = getch();

        switch(input){     //���������ƶ������
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
