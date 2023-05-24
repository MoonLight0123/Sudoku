#include<iostream>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<cstring>
#include<vector>

#include <algorithm>
using namespace std;


int map[9][9];
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
	remove(dirName.c_str());
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
        outputSudoku(outfile);
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

void selectBlank(int num) // 没有保证唯一解的挖空，若要保证唯一解，每次挖空后计算解，看是否唯一
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

void createSudoku(int blank)
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
    printSudoku();
    printf("=================\n");
    selectBlank(blank);
}

int main()
{
    //char inputfile[20]="test.txt";
    // char outfile[20]="test0.txt";
    //inputSudoku(inputfile);
    //solveSudoku(0,0);
    // outputSudoku(outfile);
createSudoku(40);
printSudoku();
printf("=================\n");
solveSudoku(0,0);
printSudoku();
    return 0;
}
