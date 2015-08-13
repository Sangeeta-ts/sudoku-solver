#include<iostream>

#define UNASSIGNED 0    // empty cell
#define N 9             // size of grid

using namespace std;

int grid[9][9];

 
void initialise_Grid(int);
void Print_Grid(int grid[N][N]);
bool FindUnassignedLocation(int grid[N][N], int &, int &);
bool UsedInRow(int grid[N][N], int, int);
bool UsedInCol(int grid[N][N], int, int);
bool UsedInBox(int grid[N][N], int, int, int);
bool isSafe(int grid[N][N], int, int, int);
bool SolveSudoku(int grid[N][N]);


int main()
{
     int i;

    

    cout<<"enter the sudoku puzzle: use 0 if the colum is empty:\n";
    for(i=0; i<9; i++)
    {
      initialise_Grid(i) ;
    }
     
    //display the input
    cout<<"\nTHE ENTERED SUDOKU IS:\n";
    Print_Grid(grid);

    cout<<"\n \n";
    if (SolveSudoku(grid) == true)
    {   
          cout<<"THE SOLVED SUDOKU IS:\n";
          Print_Grid(grid);
     }
     
     else
         cout<<"No solution exists\n";
 
    

   return 0;
}


void initialise_Grid(int row) // function to read input from user
{   
    unsigned num,i;

    cout<<"enter the row:'"<<row+1<<"'\n";
    for(i=0; i<9; i++)
    {
       cin>>num;
       
       if(num<0||num>9)
             cout<<"error! invalid input: enter a number < or = 9 and > or = 0 \n";
       else
             grid[row][i]=num;
    
    }

}

void Print_Grid(int grid[N][N])  //function to display the Sudoku
{
        unsigned i,j;

        for(i=0;i<9; i++)
        {   
            if(i%3==0)
            cout<<"\t\t‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐\n";    
            cout<<"\t\t";

            for(j=0; j<9; j++)
            {   
                    if(j%3==0)
                       cout<<"| ";
                         
                        cout<<grid[i][j]<<" ";

                    
                    if(j==8)
                    cout<<"|";  
             }
             cout<<"\n";
            if(i==8)
            cout<<"\t\t‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐\n";    
         }
}



bool FindUnassignedLocation(int grid[N][N], int &row, int &col)  
/*Searches the grid to find an entry that is still unassigned*/
{
	for(row = 0; row < N; row++)
        {
	    for(col = 0; col < N; col++)
            {
		if(grid[row][col] == UNASSIGNED)
				return true;
	    }
	}
        return false;
}

bool UsedInRow(int grid[N][N], int row, int num) 
/* Returns whether any assigned entry in the specified row matches the given number*/
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}


bool UsedInCol(int grid[N][N], int col, int num) 
/*Returns whether any assigned entry in the specified column matches the given number*/
  
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
/* Returns whether any assigned entry within the specified 3x3 box matches the given number. */
  
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num)
/* Returns whether it will be legal to assign num to the given row,col location.*/ 
 
{
	return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row%3 , col - col%3, num);
}


bool SolveSudoku(int grid[N][N])
/*function that solves the puzzle i.e.,assign values to all unassigned locations for Sudoku solution*/
{
    int row, col;
 
    
    if (!FindUnassignedLocation(grid, row, col))
       return true; 
 
   
    for (int num = 1; num <= 9; num++)
    {
        
        if (isSafe(grid, row, col, num))
        {
            
            grid[row][col] = num;
 
            
            if (SolveSudoku(grid))
                return true;
 
            
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}
