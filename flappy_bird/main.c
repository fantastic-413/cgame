#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//ȫ�ֱ�������
int high,width;         //��Ϸ����ߴ�

int bird_x,bird_y;      //С������

int barl_y,barl_xTop,barl_xDown;      //�ϰ�������

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
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    int i,j;

    for(i = 0;i < high; i++){
        for(j = 0;j < width + 1; j++){
            if(i == bird_x && j == bird_y)
                printf("@");        //���С��@
            else if((j == barl_y) && (i <= barl_xTop || i>= barl_xDown))
                printf("*");        //����ϰ���*
            else
                printf(" ");
        }
        printf("�U\n");      //��ӡ�ұ߽�
    }
    for(j = 0;j < width + 1; j++)
        printf("�{");        //��ӡ�±߽�
    printf("\n");

    printf("�÷�: %d \n", score);
    printf("�� L ��������Ϸ\n");
}

void updateWithoutInput()   //Input irrelevant updates
{
    if(bird_x < high)
        bird_x++;
    else{
        printf("Game Over!\n");
        exit(0);
    }

    //�ϰ����ƶ�����������
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

    if(kbhit()){        //������ʱִ��
        input = getch();

        switch(input){     //���������ƶ������
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

