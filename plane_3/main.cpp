#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>

#define High    25          //������Ϸ�ߴ�
#define Width   40
#define EnemyNum 5 // �л�����

using namespace std;

//ȫ�ֱ�������
int position_x,position_y;
int enemy_x[EnemyNum],enemy_y[EnemyNum];  // �л�λ��
int canvas[High][Width] = {0}; // ��ά����洢��Ϸ�����ж�Ӧ��Ԫ��
                        // 0Ϊ�ո�1Ϊ�ɻ�*��2Ϊ�ӵ�|��3Ϊ�л�@
int score; // �÷�
int BulletWidth; // �ӵ����
int EnemyMoveSpeed; // �л��ƶ��ٶ�

//�������ܣ�������ƶ���(x,y)λ��
void gotoxy(int x,int y);
//�������ܣ��������ع��
void HideCursor();


//��������:��ʼ����Ϸ����
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

//�������ܣ���ӡ��Ϸ����
void show()     //Screen display
{
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    for(int i = 0;i < High;i++){
        for(int j = 0;j < Width;j++){
            if (canvas[i][j]==0)
				printf(" ");   //   ����ո�
			else if (canvas[i][j]==1)
				printf("*");   //   ����ɻ�*
			else if (canvas[i][j]==2)
				printf("|");   //   ����ӵ�|
			else if (canvas[i][j]==3)
				printf("@");   //  ����ɻ�@
        }
        printf("��\n");      //&��ӡ�߽�
    }
    for(int j = 0;j < Width; j++)
        printf("�{");
    printf("\n�÷֣�%d\n",score);
    printf("��L����ͣ\n");
	Sleep(20);
}

//�������޹ص����ݸ���
void updateWithoutInput()   //Input irrelevant updates
{
    int i,j,k;
    int bulletFlag = 0;//�ж��ӵ��Ƿ���ел�
    static int speed = 0;
	if (speed < EnemyMoveSpeed)
		speed++;
    for (k=0;k<EnemyNum;k++)
    {
        if ((position_x==enemy_x[k]) && (position_y==enemy_y[k]))  // �л�ײ���һ�
        {
            printf("ʧ�ܣ�\n");
            Sleep(3000);
            system("pause");
            exit(0);
        }

        if (speed == EnemyMoveSpeed)
        {
            // �л�����
            for (k=0;k<EnemyNum;k++)
            {
                canvas[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k]++;
                speed = 0;
                if (enemy_x[k]>=High)   // �л��ܳ���ʾ��Ļ
                {
                    enemy_x[k] = 0;           // �����µķɻ�
                    enemy_y[k] = rand()%Width;
                    canvas[enemy_x[k]][enemy_y[k]] = 3;
                    score--;  // ����
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
                    if ((i==enemy_x[k]) && (j==enemy_y[k]))  // �ӵ����ел�
                    {
                        score++;                // ������1
                        canvas[i][j] = 0;
                        enemy_x[k] = 0;           // �����µķɻ�
                        enemy_y[k] = rand()%Width;
                        canvas[enemy_x[k]][enemy_y[k]] = 3;
                        bulletFlag = 1;
                        break;
                    }
                }
                if(!bulletFlag)
                {
                    // �ӵ������ƶ�
                    canvas[i][j] = 0;
                    if (i>0)
                        canvas[i-1][j] = 2;
                    for (k=0;k<EnemyNum;k++)
                    {
                        if (((i-1)==enemy_x[k]) && (j==enemy_y[k]))  // �ӵ����ел�
                        {
                            score++;                // ������1
                            canvas[i-1][j] = 0;
                            enemy_x[k] = 0;           // �����µķɻ�
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

	if (score%10 == 0 && EnemyMoveSpeed > 3)   // �ﵽһ�����ֺ󣬵л����
        EnemyMoveSpeed = 10 - score/10;
    if (score%10 == 0)   // �ﵽһ�����ֺ��ӵ�������
        BulletWidth = score/10;
}
//�������йص����ݸ���
void updateWithInput()      //Input relevant updates
{
    char input;
    int left = position_y - BulletWidth;
    int right = position_y + BulletWidth;
    int k;

    if(kbhit()){        //������ʱִ��
        input = getch();

        switch(input){     //���������ƶ������
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
			for (k = left;k <= right;k++) // ����ɢ��
				canvas[position_x-1][k] = 2; // �����ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
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
