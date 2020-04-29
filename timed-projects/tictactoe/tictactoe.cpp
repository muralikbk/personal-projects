/*
	Create a tic tac toe application. 
	The application takes a token and position as input and prints the board.
	The application does not check for win conditions.
*/

#include <iostream>



using namespace std;

const char X = 'X';
const char O = 'O';
const char NIL = '-';

class TicTacToe
{
	char board[3][3];

	public:
	bool isBoardFull()
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(board[i][j] == NIL)
				{
					return false;
				}
			}
		}
		return true;
	}
	
	void initialize()
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				board[i][j] = NIL;
			}
		}

	}

	bool addToken(int x, int y, char token)
	{
		if( x < 1 || x > 3 || y < 1 || y > 3)
		{
			cout << "Invalid space!" << endl;
			return false;
		}

		if(board[x-1][y-1] != NIL)
		{
			cout << "Space not empty!" << endl;
			return false;
		}
		
		board[x-1][y-1] = token;

		return true;
	}

	void printBoard()
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				cout << board[i][j];
				if(j != 2) cout << "|";
			}
			cout << endl;
		}		
		cout << "----------------" << endl;
	}

	bool makeMove(char token)
	{
		//Check if a move can be made
		if(true == isBoardFull())
		{
			cout << "Board is Full!" << endl;
			return false;
		}
		for(int i = 0; i < 3; i ++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(board[i][j] == NIL)
				{
					board[i][j] = token;
					return true;
				}
			}
		}
	}
	

	TicTacToe()
	{
		initialize();
	}

};

int main(int argc, char *argv[])
{
	TicTacToe T;
	T.printBoard();
	T.addToken(1,2,X);
	T.printBoard();
	int test = 0;
	while(test < 12)
	{
		if(T.makeMove(O);
		++test;
		T.printBoard();
	}
	T.printBoard();
	return 0;
}
