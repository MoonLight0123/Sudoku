#include<iostream>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<cstring>
#include<vector>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include<assert.h>
using namespace std;




int map[9][9];
int solveNum=0;
struct pos//坐标
{
    int row,col;
};

void inputSudoku(char *fileName)//输入一个数独
{
    ifstream infile(fileName);
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            infile>>map[i][j];
            if(map[i][j]>9||map[i][j]<0)
            {
                printf("wrong input number!");
            }
        }
    }
}

void outputSudoku(char *fileName)//输出一个数独
{
    string dirName(fileName);
	ofstream outfile;
	outfile.open(dirName, ios::app);
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            outfile<<map[i][j]<<' ';
        }
        outfile<<endl;
    }
    outfile<<"==========\n";
}

void printSudoku()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout<<map[i][j]<<' ';
        }
        cout<<endl;
    }
}

bool checkSudoku(int r,int c,int e)
{
    //check row
    for(int j=0;j<9;j++)
    {
        if(map[r][j]==e)
            return false;
    }

    //check col
    for(int i=0;i<9;i++)
    {
        if(map[i][c]==e)
            return false;
    }

    int starti=3*(r/3),startj=3*(c/3);
    for(int i=starti;i<starti+3;i++)
    {
        for(int j=startj;j<startj+3;j++)
        {
            if(map[i][j]==e)
                return false;
        }
    }

    return true;
}

pos getNextPositionToFill()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(map[i][j]==0)
                return {i,j};
        }
    }
    return {-1,-1};
}

bool solveSudoku(int r,int c)
{
    pos p=getNextPositionToFill();
    r=p.row,c=p.col;
    if(r==-1)
    {
        char outfile[20]="test0.txt";
        // outputSudoku(outfile);
        // printSudoku();
        return true;
    }
    for(int e=1;e<=9;e++)
    {
        if(checkSudoku(r,c,e))
        {
            map[r][c]=e;
            if(solveSudoku(r,c))
                return true;
            map[r][c]=0;
        }
    }
    return false;
}

bool solveSudokuForTest(int r,int c)
{
    pos p=getNextPositionToFill();
    r=p.row,c=p.col;
    if(r==-1)
    {
        char outfile[20]="test0.txt";
        // outputSudoku(outfile);
        solveNum++;
        if(solveNum>1)
            return true;
    }
    for(int e=1;e<=9;e++)
    {
        if(checkSudoku(r,c,e))
        {
            map[r][c]=e;
            solveSudokuForTest(r,c);
            map[r][c]=0;
        }
    }
    return false;
}

void RandomArray(int *arr)
{
	int count = 0;
	srand(time(NULL));
	while (count < 9)
	{
		int val = rand() % 9;
		if (!arr[val])
		{
			arr[val] = count + 1;
			++count;
		}
	}
}

bool solveSudokuForGen()
{
    int r = 0, c= 0;
    int arr[9] = {0};
    RandomArray(arr);
    pos p=getNextPositionToFill();
    r=p.row,c=p.col;
    if(r==-1)
    {
        char outfile[20]="test0.txt";
        outputSudoku(outfile);
        return true;
    }
    for(int e=1;e<=9;e++)
    {
        if(checkSudoku(r,c,arr[e]))
        {
            map[r][c]=arr[e];
            if(solveSudoku(r,c))
                return true;
            map[r][c]=0;
        }
    }
    return false;
}

void swapRowOrCol(int a, int b, bool isRow)
{
    int temp;
    if(isRow){
        for(int j = 0; j < 9; j++)
        {
            temp = map[a][j];
            map[a][j] = map[b][j];
            map[b][j] = temp;
        }
    }else{
        for(int i = 0; i < 9; i++)
        {
            temp = map[i][a];
            map[i][a] = map[i][b];
            map[i][b] = temp;
        }
    }
}

void selectBlankUnique(int num) // 没有保证唯一解的挖空，若要保证唯一解，每次挖空后计算解，看是否唯一
{
    srand(time(NULL));
    while (num)
    {
        int row = rand() % 9;
        int col = rand() % 9;
        if (map[row][col] != 0)
        {
            int temp = map[row][col];
            map[row][col] = 0;
            solveNum = 0;
            solveSudokuForTest(0,0);
            if(solveNum == 1)
                num--;
            else{
                map[row][col] = temp;
            }
        }
    }
}

void selectBlank(int num) // 保证唯一解
{
    srand(time(NULL));
    while (num)
    {
        int row = rand() % 9;
        int col = rand() % 9;
        if (map[row][col] != 0)
        {
            map[row][col] = 0;
            num--;
        }
    }
}

void createSudokuZhongPan(char *fileName)
{
    memset(map, 0, sizeof(map));
    solveSudokuForGen();
    int choice[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };// 交换小九宫格的行列不会改变数独可解性
    srand(time(NULL));
    for (int t = 0; t < 100; t++)
    {
        int i = rand() % 9;
        bool b = rand() % 2;
        swapRowOrCol(choice[i][0], choice[i][1], b);
    }
    // 注释以下打印
    // printSudoku();
    outputSudoku(fileName);
}

void createSudoku(int blank,char * fileName)
{
    memset(map, 0, sizeof(map));
    solveSudokuForGen();
    int choice[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };// 交换小九宫格的行列不会改变数独可解性
    srand(time(NULL));
    for (int t = 0; t < 100; t++)
    {
        int i = rand() % 9;
        bool b = rand() % 2;
        swapRowOrCol(choice[i][0], choice[i][1], b);
    }
    // 注释以下打印
    // printSudoku();
    selectBlankUnique(blank);
    outputSudoku(fileName);
}

int main(int argc,char *argv[])
{
    system("chcp 65001");//防止汉字乱码
    int o;
    bool haveParamN=false;//是否有n这个参数
    int nVal;//n的值 
    while(((o = getopt(argc, argv, "c:s:n:m:r:u")) != -1))
    {
        int num;//将要读入的参数
        switch (o)
        {
        case 'c':
            sscanf(optarg,"%d",&num);

            for(int i = 0;i< num ; i++)
            {
                char file[] = "ZhongPan.txt";
                createSudokuZhongPan(file);
            }
            // printf("需要创建%d个终盘",num);


            break;
        case 's'://给出路径，解数独，这部分已完成
            inputSudoku(optarg);
            solveSudoku(0,0);
            break;

        case 'n':
            sscanf(optarg,"%d",&num);
            haveParamN=true;
            nVal=num;

            if(optind==argc)
            {
                for(int i = 0;i < num; i++)
                {
                    char file[] = "WenTi.txt";
                    createSudoku(20,file);
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
                createSudoku(num*15, file);
            }


            break;

        case 'r': 

            if(!haveParamN)
            {
                printf("参数r必须和参数n一起使用,程序错误退出!");
                return 0;
            }
            sscanf(optarg,"%d",&num);
            assert(20<=num&&num<=55);

            for(int i  = 0; i < nVal; i++)
            {
                char file[] = "blank.txt";
                createSudoku(num, file);
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
                createSudoku(num, file);
            }
            break;


        default:
            printf("program should not reach here");
            break;
        }
    }
    return 0;
}