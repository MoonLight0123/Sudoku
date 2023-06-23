#include "sudoku.h"

int main(int argc,char *argv[])
{
    system("chcp 65001");//防止汉字乱码
    int o;
    bool haveParamN=false;//是否有n这个参数
    int nVal;//n的值 
    Sudoku sudoku;
    while(((o = getopt(argc, argv, "c:s:n:m:r:u")) != -1))
    {
        int num;//将要读入的参数
        int num2;
        switch (o)
        {
        case 'c':
            sscanf(optarg,"%d",&num);

            for(int i = 0;i< num ; i++)
            {
                char file[] = "result0.txt";
                sudoku.createSudokuZhongPan(file);
            }
            // printf("需要创建%d个终盘",num);


            break;
        case 's'://给出路径，解数独，这部分已完成
            sudoku.inputSudoku(optarg);
            sudoku.solveSudoku(0,0);
            break;

        case 'n':
            sscanf(optarg,"%d",&num);
            haveParamN=true;
            nVal=num;

            if(optind==argc)
            {
                for(int i = 0;i < num; i++)
                {
                    char file[] = "RandomSudokuQuestion.txt";
                    sudoku.createSudoku(20,file);
                }
            }
            break;
        case 'm':

            if(!haveParamN)
            {
                printf("参数m必须和参数n一起使用,程序错误退出!");
                return 0;
            }
            sscanf(optarg,"%d",&num);
            assert(num==1||num==2||num==3);


            for(int i  = 0; i < num; i++)
            {
                char file[] = "level.txt";
                sudoku.createSudoku(num*15, file);
            }


            break;

        case 'r': 

            if(!haveParamN)
            {
                printf("参数r必须和参数n一起使用,程序错误退出!");
                return 0;
            }
            sscanf(optarg,"%d",&num);
            sscanf(optarg,"%d",&num2);
            assert(20<=num&&num<=55&&20<=num2&&num2<=55);
            
            for(int i  = 0; i < nVal; i++)
            {
                char file[] = "blank.txt";
                int blankNum=rand()%(num2-num+1)+num;
                sudoku.createSudoku(blankNum, file);
            }
            break;

        case 'u':

            if(!haveParamN)
            {
                printf("参数u必须和参数n一起使用,程序错误退出!");
                return 0;
            }

            for(int i  = 0; i < nVal; i++)
            {
                char file[] = "unique.txt";
                sudoku.createSudoku(num, file);
            }
            break;


        default:
            printf("program should not reach here");
            break;
        }
    }
    return 0;
}