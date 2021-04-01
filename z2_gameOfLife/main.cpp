#include<iostream>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#define HIGH    35          //������Ϸ�ߴ�
#define WIDTH   80

using namespace std;

//ȫ�ֱ�������
int cells[HIGH][WIDTH];
int speed = 256;

//�������ܣ�������ƶ���(x,y)λ��
void gotoxy(int x,int y);
//�������ܣ��������ع��
void HideCursor();


//��������:��ʼ����Ϸ����
void startup()     //Initialization data
{
    //��ʼ��ϸ��
    for(int i = 0;i < HIGH;i++){
        for(int j = 0;j < WIDTH;j++){
            cells[i][j] = rand() % 2;
        }
    }

    HideCursor();
}

//�������ܣ���ӡ��Ϸ����
void show()     //Screen display
{
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    for(int i = 0;i < HIGH;i++){
        for(int j = 0;j < WIDTH;j++){
            if(cells[i][j] == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("���� A �� D ���ӿ��ٶ�\n");
    printf("���� W �� S �������ٶ�\n");
}

//�������޹ص����ݸ���
void updateWithoutInput()   //Input irrelevant updates
{
    int neibour_liveNum;
    int tempCells[HIGH][WIDTH];

    for(int i = 0;i < HIGH;i++){
        for(int j = 0;j < WIDTH;j++){
                neibour_liveNum = 0;
                //�ж�ϸ������
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
                //����ϸ������
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
//�������йص����ݸ���
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


//�������ܣ�������ƶ���(x,y)λ��
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

//�������ܣ��������ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  //�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
