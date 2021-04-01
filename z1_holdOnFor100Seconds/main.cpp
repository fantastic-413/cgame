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

//全局变量定义
int game_map[MAX_X][MAX_Y] = {0};     //可选地图大小
int enemy_x[MAX_NUM],enemy_y[MAX_NUM];      //敌人坐标
int enemy_num;                      //敌人数量
int map_top=0,map_left=0,map_bottom,map_right;      //地图边界坐标
int player_x,player_y;              //玩家坐标
float start_time,now_time,end_time;          //游戏开始时间与结束时间
int enemy_speed;                    //敌人速度因子

//函数功能：将光标移动到(x,y)位置
void gotoxy(int x,int y);
//函数功能：用于隐藏光标
void HideCursor();

//初始化输入函数
void start_input()
{
    cout<<"为了您的游戏体验，请输入尽量大的边界与适当的速度"<<endl;
    cout<<"请输入地图右边界([10,98])与下边界位置([10,36])"<<endl;
    cin>>map_right>>map_bottom;
    if(map_right > MAX_Y)
        map_right = MAX_Y;
    else if(map_right < MIN_Y)
        map_right = MIN_Y;
    if(map_bottom > MAX_X)
        map_bottom = MAX_X;
    else if(map_bottom < MIN_X)
        map_bottom = MIN_X;
    cout<<"请输入敌人速度（[1:4])"<<endl;
    cin>>enemy_speed;
    enemy_speed = 5 - enemy_speed;
    if(enemy_speed > 4)
        enemy_speed = 4;
    else if(enemy_speed < 1)
        enemy_speed = 1;
}
//函数功能:初始化游戏数据
void startup()     //Initialization data
{
    start_input();

    //依据地图大小给出敌人数量
    enemy_num = 50*(map_bottom-1)*(map_right-1)/((MAX_X-1)*(MAX_Y));

    //给边界元素赋标识数
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

    //随机生成玩家与敌人位置
    for(int k = 0;k < enemy_num;k++){
        enemy_x[k] = rand() % (map_bottom - 1) + 1;
        enemy_y[k] = rand() % (map_right - 1) + 1;
        game_map[enemy_x[k]][enemy_y[k]] = 2;
    }
    player_x = rand() % (map_bottom - 1) + 1;
    player_y = rand() % (map_bottom - 1) + 1;
    game_map[player_x][player_y] = 1;

    HideCursor();
    system("cls");//清除游戏前的屏幕输出
    start_time = clock();
}
//函数功能：输出游戏胜负
void winOrLose()
{
    system("cls");
    if(((end_time-start_time) / 1000.0) >= 100)
        printf("!!!You Win!!!\n");
    else
        printf("###You Lose###\n");
    exit(0);
}
//函数功能：判断敌人是否击中玩家
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
//函数功能：打印游戏界面
void show()     //Screen display
{
    gotoxy(0,0);    //光标移动到原点，以下重画来实现清屏

    int i,j;

    now_time = clock();
    printf("你已坚持: %.3f s! \n", (now_time - start_time) / 1000.0);

    enemyHitplayer();

    for(i = 0;i <= map_bottom; i++){
        for(j = 0;j <= map_right; j++){
            if(game_map[i][j] == 0)
                printf(" ");        //打印小球
            else if(game_map[i][j] == 1)
                printf("@");        //打印玩家@
            else if(game_map[i][j] == 2)
                printf("#");        //打印敌人#
            else if(game_map[i][j] == 3)
                printf("▄");        //打印上下边界
            else if(game_map[i][j] == 4)
                printf("|");        //打印左右边界
        }
        printf("\n");      //打印右边界
    }
}

//函数功能：实现敌人向玩家追逐
void enemy_chase()
{
    for(int k = 0;k < enemy_num;k++){
        game_map[enemy_x[k]][enemy_y[k]] = 0;
        //敌人向玩家前进
        if (enemy_x[k] > player_x && enemy_x[k] > map_top+1)
			enemy_x[k]--;
		else if (enemy_x[k] < player_x && enemy_x[k] < map_bottom-1)
			enemy_x[k]++;
		if (enemy_y[k] > player_y && enemy_y[k] > map_left+1)
			enemy_y[k]--;
		else if (enemy_y[k] < player_y && enemy_y[k] < map_right-1)
			enemy_y[k]++;
        //敌人无法出边界
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
//函数功能：防止敌人重合
void deal_enemyCoincide()
{
    for(int a = 0; a < enemy_num;a++){
        for(int b = 0; b < enemy_num;b++){
            if(a != b && enemy_x[a] == enemy_x[b] && enemy_y[a] == enemy_y[b]){
                game_map[enemy_x[a]][enemy_y[a]] = 0;
                enemy_x[a] += rand() % 3 - 1;
                enemy_y[a] += rand() % 3 - 1;
                //敌人无法出边界
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
//与输入无关的数据更新
void updateWithoutInput()   //Input irrelevant updates
{
    static int enemy_speed_num = 0;
    static int time_speed = 12;           //时间速度因子，速度随时间加快
    static int area_speed = (int)sqrt((MAX_X-1)*(MAX_Y)/((map_bottom-1)*(map_right-1)));        //面积速度因子，面积越大速度越快
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
//与输入有关的数据更新
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
	//玩家无法出边界
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
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
