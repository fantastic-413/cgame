#include <stdio.h>
#include <stdlib.h>                     //systemͷ�ļ�
#include <windows.h>                    //Sleepͷ�ļ�

int main()
{
    int i,j;
    int x = 0;
    int y = 5;
    int velocity_x = 1;
    int velocity_y = 1;//�ٶ�
    int left = 0;
    int right = 20;
    int top = 0;
    int bottom = 10;

    while(1)
    {
        x = x + velocity_x;
        y = y + velocity_y;
        system("cls");                  //����

        for(i = 0; i <= right+1;i++)    //�ϱ߿�
            printf("-");
        printf("\n|");

        for(i = 0;i < x;i++){           //x����(�ڼ��У�
            for(j = 0;j <= right;j++){
                printf(" ");
            }
            printf("|\n|");             //����߿�
        }

        for(j = 0;j < y;j++){           //Y���꣨�ڼ��У�
            printf(" ");
        }
        printf("O");                    //С��

        for(j = 0;j <= right-y-1;j++){
                printf(" ");
        }
        printf("|\n|");
        for(i = 0;i < bottom-x;i++){
            for(j = 0;j <= right;j++){
                printf(" ");
            }
            printf("|\n|");             //����߿�
        }

        for(i = 0; i <= right+1;i++)    //�±߿�
            printf("-");

        Sleep(200);                     //˯�ߣ�����С���ٶ�

        if(x == top || x == bottom){
            velocity_x = -velocity_x;
            //printf("\a");               //����
        }
        if(y == right || y== left){
            velocity_y = -velocity_y;
            //printf("\a");               //����
        }
    }
    return 0;
}
