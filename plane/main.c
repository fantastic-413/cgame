#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main()
{
    int i,j;
    int x = 10;
    int y = 20;
    char input;

    int isFried = 0;                    //�Ƿ��伤��

    int nx;
    int ny;
    int nextx = rand() % 5 + 1;         //������һ�ε�λ��x
    int nexty = rand() % 40 + 3;        //������һ�ε�λ��y
    srand((int)time(0));                //�������������
    int isHit = 0;

    int score = 0;                      //��¼�ܷ�

    while(1){
        system("cls");                  //����
        if(isHit)
            score++;
        printf("You have get -- %d -- scores!/n",score);

        if(isHit == 0){                 //����λ��nx,ny
            nx = nextx;
            ny = nexty;
        }else{
            nx = 0;
            ny = 0;
            nextx = rand() % 5 + 1;
            nexty = rand() % 40 + 3;
            isHit = 0;
        }
        for(i = 0;i < nx;i++){             //print  ��+��
            printf("\n");
        }
        for(i = 0;i < ny;i++){
                printf(" ");
                if(i+1 == ny)
                    printf("+");
        }
        printf("\n");

        if(isFried == 0){
            for(i = 0;i < (x-nx);i++)        //δ���伤��
                printf("\n");
        }else{
            for(i = 0;i < (x-nx);i++){
                for(j = 0;j < y;j++)    //���伤��
                    printf(" ");
                printf("  |\n");
            }
            isFried = 0;                //����һ�κ���ʧ
            if(y+2 == ny)
                isHit = 1;              //���к�����isHit=1
        }

        for(j = 0;j < y;j++)            //print  plane
            printf(" ");
        printf("  *\n");
        for(j = 0;j < y;j++)
            printf(" ");
        printf("*****\n");
        for(j = 0;j < y;j++)
            printf(" ");
        printf(" * *\n");

        input = getch();                //�ַ�ָ��
        switch(input){
        case 'a':
        case 'A':
            y--;
            break;
        case 's':
        case 'S':
            x++;
            break;
        case 'd':
        case 'D':
            y++;
            break;
        case 'w':
        case 'W':
            x--;
            break;
        case ' ':
            isFried = 1;
            break;
        default:
            break;
        }
    }
    return 0;
}
