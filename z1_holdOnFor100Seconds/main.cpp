#include<iostream>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>
#define MAX_X 36
#define MAX_Y 98
#define MIN_X 10
#define MIN_Y 10
#define MAX_NUM 50

using namespace std;

//ȫ�ֱ�������
int game_map[MAX_X][MAX_Y] = {0};     //��ѡ��ͼ��С
int enemy_x[MAX_NUM],enemy_y[MAX_NUM];      //��������
int enemy_num;                      //��������
int map_top=0,map_left=0,map_bottom,map_right;      //��ͼ�߽�����
int player_x,player_y;              //�������
float start_time,now_time,end_time;          //��Ϸ��ʼʱ�������ʱ��
int enemy_speed;                    //�����ٶ�����

//�������ܣ�������ƶ���(x,y)λ��
void gotoxy(int x,int y);
//�������ܣ��������ع��
void HideCursor();

//��ʼ�����뺯��
void start_input()
{
    cout<<"Ϊ��������Ϸ���飬�����뾡����ı߽����ʵ����ٶ�"<<endl;
    cout<<"�������ͼ�ұ߽�([10,98])���±߽�λ��([10,36])"<<endl;
    cin>>map_right>>map_bottom;
    if(map_right > MAX_Y)
        map_right = MAX_Y;
    else if(map_right < MIN_Y)
        map_right = MIN_Y;
    if(map_bottom > MAX_X)
        map_bottom = MAX_X;
    else if(map_bottom < MIN_X)
        map_bottom = MIN_X;
    cout<<"����������ٶȣ�[1:4])"<<endl;
    cin>>enemy_speed;
    enemy_speed = 5 - enemy_speed;
    if(enemy_speed > 4)
        enemy_speed = 4;
    else if(enemy_speed < 1)
        enemy_speed = 1;
}
//��������:��ʼ����Ϸ����
void startup()     //Initialization data
{
    start_input();

    //���ݵ�ͼ��С������������
    enemy_num = 50*(map_bottom-1)*(map_right-1)/((MAX_X-1)*(MAX_Y));

    //���߽�Ԫ�ظ���ʶ��
    for(int i = map_top;i <= map_bottom;i++){
        for(int j = map_left;j <= map_right;j++){
            if(i == 0 || i == map_bottom)
                game_map[i][j] = 3;
            else{
                if(j == 0 || j == map_right)
                    game_map[i][j] = 4;
            }
        }
    }

    //���������������λ��
    for(int k = 0;k < enemy_num;k++){
        enemy_x[k] = rand() % (map_bottom - 1) + 1;
        enemy_y[k] = rand() % (map_right - 1) + 1;
        game_map[enemy_x[k]][enemy_y[k]] = 2;
    }
    player_x = rand() % (map_bottom - 1) + 1;
    player_y = rand() % (map_bottom - 1) + 1;
    game_map[player_x][player_y] = 1;

    HideCursor();
    system("cls");//�����Ϸǰ����Ļ���
    start_time = clock();
}
//�������ܣ������Ϸʤ��
void winOrLose()
{
    system("cls");
    if(((end_time-start_time) / 1000.0) >= 100)
        printf("!!!You Win!!!\n");
    else
        printf("###You Lose###\n");
    exit(0);
}
//�������ܣ��жϵ����Ƿ�������
void enemyHitplayer()
{
    for(int k = 0;k < enemy_num;k++){
        if(game_map[enemy_x[k]][enemy_y[k]] == 1 || game_map[player_x][player_y] == 2){
            end_time = clock();
            winOrLose();
            break;
        }
    }
}
//�������ܣ���ӡ��Ϸ����
void show()     //Screen display
{
    gotoxy(0,0);    //����ƶ���ԭ�㣬�����ػ���ʵ������

    int i,j;

    now_time = clock();
    printf("���Ѽ��: %.3f s! \n", (now_time - start_time) / 1000.0);

    enemyHitplayer();

    for(i = 0;i <= map_bottom; i++){
        for(j = 0;j <= map_right; j++){
            if(game_map[i][j] == 0)
                printf(" ");        //��ӡС��
            else if(game_map[i][j] == 1)
                printf("@");        //��ӡ���@
            else if(game_map[i][j] == 2)
                printf("#");        //��ӡ����#
            else if(game_map[i][j] == 3)
                printf("�{");        //��ӡ���±߽�
            else if(game_map[i][j] == 4)
                printf("|");        //��ӡ���ұ߽�
        }
        printf("\n");      //��ӡ�ұ߽�
    }
}

//�������ܣ�ʵ�ֵ��������׷��
void enemy_chase()
{
    for(int k = 0;k < enemy_num;k++){
        game_map[enemy_x[k]][enemy_y[k]] = 0;
        //���������ǰ��
        if (enemy_x[k] > player_x && enemy_x[k] > map_top+1)
			enemy_x[k]--;
		else if (enemy_x[k] < player_x && enemy_x[k] < map_bottom-1)
			enemy_x[k]++;
		if (enemy_y[k] > player_y && enemy_y[k] > map_left+1)
			enemy_y[k]--;
		else if (enemy_y[k] < player_y && enemy_y[k] < map_right-1)
			enemy_y[k]++;
        //�����޷����߽�
        if (enemy_y[k] < map_left + 1)
            enemy_y[k] = map_left + 1;
        else if (enemy_y[k] > map_right - 1)
            enemy_y[k] = map_right - 1;
        if (enemy_x[k] < map_top + 1)
            enemy_x[k] = map_top + 1;
        else if (enemy_x[k] > map_bottom - 1)
            enemy_x[k] = map_bottom - 1;

        game_map[enemy_x[k]][enemy_y[k]] = 2;
    }
}
//�������ܣ���ֹ�����غ�
void deal_enemyCoincide()
{
    for(int a = 0; a < enemy_num;a++){
        for(int b = 0; b < enemy_num;b++){
            if(a != b && enemy_x[a] == enemy_x[b] && enemy_y[a] == enemy_y[b]){
                game_map[enemy_x[a]][enemy_y[a]] = 0;
                enemy_x[a] += rand() % 3 - 1;
                enemy_y[a] += rand() % 3 - 1;
                //�����޷����߽�
                if (enemy_y[a] < map_left + 1)
                    enemy_y[a] = map_left + 1;
                else if (enemy_y[a] > map_right - 1)
                    enemy_y[a] = map_right - 1;
                if (enemy_x[a] < map_top + 1)
                    enemy_x[a] = map_top + 1;
                else if (enemy_x[a] > map_bottom - 1)
                    enemy_x[a] = map_bottom - 1;
                game_map[enemy_x[a]][enemy_y[a]] = 2;
            }

        }
    }
}
//�������޹ص����ݸ���
void updateWithoutInput()   //Input irrelevant updates
{
    static int enemy_speed_num = 0;
    static int time_speed = 12;           //ʱ���ٶ����ӣ��ٶ���ʱ��ӿ�
    static int area_speed = (int)sqrt((MAX_X-1)*(MAX_Y)/((map_bottom-1)*(map_right-1)));        //����ٶ����ӣ����Խ���ٶ�Խ��
    int speed_factor = ((now_time - start_time) / 1000.0)/10;

    if(enemy_speed_num == time_speed*enemy_speed*area_speed){
        enemy_chase();
        enemy_speed_num = 0;
        deal_enemyCoincide();
        if(speed_factor < 11)
            time_speed = 12 - speed_factor;
        else
            time_speed = 1;
    }
    else
        enemy_speed_num++;
}
//�������йص����ݸ���
void updateWithInput()      //Input relevant updates
{
    game_map[player_x][player_y] = 0;
    if (kbhit())
	{
		if ((GetAsyncKeyState(0x41) & 0x8000) ? 1 : 0)//a
			player_y -= 2;
		else	if ((GetAsyncKeyState(0x44) & 0x8000) ? 1 : 0)//d
			player_y += 2;
		if ((GetAsyncKeyState(0x57) & 0x8000) ? 1 : 0)//w
			player_x -= 2;
		else if ((GetAsyncKeyState(0x53) & 0x8000) ? 1 : 0)//s
			player_x += 2;
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	//����޷����߽�
	if (player_y < map_left + 1)
		player_y = map_left + 1;
	else if (player_y > map_right - 1)
		player_y = map_right - 1;
	if (player_x < map_top + 1)
		player_x = map_top + 1;
	else if (player_x > map_bottom - 1)
		player_x = map_bottom - 1;

    game_map[player_x][player_y] = 1;
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
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
