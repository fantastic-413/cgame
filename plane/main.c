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

    int isFried = 0;                    //是否发射激光

    int nx;
    int ny;
    int nextx = rand() % 5 + 1;         //靶子下一次的位置x
    int nexty = rand() % 40 + 3;        //靶子下一次的位置y
    srand((int)time(0));                //设置随机数种子
    int isHit = 0;

    int score = 0;                      //记录总分

    while(1){
        system("cls");                  //清屏
        if(isHit)
            score++;
        printf("You have get -- %d -- scores!/n",score);

        if(isHit == 0){                 //靶子位置nx,ny
            nx = nextx;
            ny = nexty;
        }else{
            nx = 0;
            ny = 0;
            nextx = rand() % 5 + 1;
            nexty = rand() % 40 + 3;
            isHit = 0;
        }
        for(i = 0;i < nx;i++){             //print  “+”
            printf("\n");
        }
        for(i = 0;i < ny;i++){
                printf(" ");
                if(i+1 == ny)
                    printf("+");
        }
        printf("\n");

        if(isFried == 0){
            for(i = 0;i < (x-nx);i++)        //未发射激光
                printf("\n");
        }else{
            for(i = 0;i < (x-nx);i++){
                for(j = 0;j < y;j++)    //发射激光
                    printf(" ");
                printf("  |\n");
            }
            isFried = 0;                //发射一次后消失
            if(y+2 == ny)
                isHit = 1;              //击中后设置isHit=1
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

        input = getch();                //字符指令
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
