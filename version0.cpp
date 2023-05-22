#include<iostream>
#include<fstream>
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

int main()
{
    char inputfile[20]="test.txt";
    // char outfile[20]="test0.txt";
    inputSudoku(inputfile);
    solveSudoku(0,0);
    // outputSudoku(outfile);


    return 0;
}