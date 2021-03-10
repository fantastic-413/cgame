#include <stdio.h>
#include <stdlib.h>                     //system头文件
#include <windows.h>                    //Sleep头文件

int main()
{
    int i,j;
    int x = 0;
    int y = 5;
    int velocity_x = 1;
    int velocity_y = 1;//速度
    int left = 0;
    int right = 20;
    int top = 0;
    int bottom = 10;

    while(1)
    {
        x = x + velocity_x;
        y = y + velocity_y;
        system("cls");                  //清屏

        for(i = 0; i <= right+1;i++)    //上边框
            printf("-");
        printf("\n|");

        for(i = 0;i < x;i++){           //x坐标(第几行）
            for(j = 0;j <= right;j++){
                printf(" ");
            }
            printf("|\n|");             //两侧边框
        }

        for(j = 0;j < y;j++){           //Y坐标（第几列）
            printf(" ");
        }
        printf("O");                    //小球

        for(j = 0;j <= right-y-1;j++){
                printf(" ");
        }
        printf("|\n|");
        for(i = 0;i < bottom-x;i++){
            for(j = 0;j <= right;j++){
                printf(" ");
            }
            printf("|\n|");             //两侧边框
        }

        for(i = 0; i <= right+1;i++)    //下边框
            printf("-");

        Sleep(200);                     //睡眠，减慢小球速度

        if(x == top || x == bottom){
            velocity_x = -velocity_x;
            //printf("\a");               //响铃
        }
        if(y == right || y== left){
            velocity_y = -velocity_y;
            //printf("\a");               //响铃
        }
    }
    return 0;
}
