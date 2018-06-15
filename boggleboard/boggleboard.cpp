/* 

# * Create an application that prints all the words in a Boggle board represented by a 2D matrix.
#   * Input: Board represented as 2D matrix.
#   * Input: List of valid words.
#   * Output: Words contained in the boggle board.
#   * Notes:
#     * Can’t re-use the same letter for a given word.
#     * Letters can’t be connected diagonally.
#     * Print the word every time it appears
#     * Runnable solution

# Example:

# Inputs:
# - Board:
#   [
#     ["d", "b", "c"],
#     ["a", "c", "a"],
#     ["b", "a", "t"]
#   ]
# - List of valid words: ["cab", "cat", "bat"]

# Output:
# "cab"
# "cab"
# "cat"
# "cat"
# "cat"
# "bat"

Note: 1) For the output in this case, I am adding more details.

2) The wordtree is a tree of this format (like a trie). This optimizes searching
      [root]
      /   \
     c    b
    /     \
   a      a
  / \     \
  b  t    t

3) Time complexity

*/


#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;
const char STOP = '\0';


const string UP = "\u2191 ";
const string DOWN = "\u2193 ";
const string LEFT = "\u2190 ";
const string RIGHT = "\u2192 ";
//If the arrows do not display correctly, comment the lines above and uncomment below section
/*
const string UP = "(U)";
const string DOWN = "(D)";
const string LEFT = "(L)";
const string RIGHT = "(R)";
*/


struct node
{
  char c;
  map<char, node> child; 
};


void buildTree(map<char, node> &wordTree, const vector<string> &wordlist)
{
	for(unsigned int i = 0; i < wordlist.size(); i++)
	{
		map<char, node> *current = &wordTree;
		string word = wordlist[i];
		if(word.length() == 0)
		{
			continue;
		}
		cout << "Adding word to tree:" << word << " as ";
		for(unsigned int j = 0; j < word.length(); j++)
		{
			char c = word[j];
			if(current->count(c) == 0)
			{
				//Indicates character is being newly added
				cout << "*";
				node temp; 
				temp.c = c;
				(*current)[temp.c] = temp;
			}
			cout << c << " ";
			current = &(*current)[c].child;
		}
		if(current->count(STOP) == 0)
		{
			node temp;
			temp.c = STOP;
			(*current)[temp.c] = temp;
		}
		cout << endl;
	}
}

void printMap(const map<char, node> &current, string prefix = "")
{

	for(map<char, node>::const_iterator it = current.begin();
		it != current.end(); ++it)
	{
		if(it->first == STOP)
		{
			cout << prefix << endl;
		}
		else
		{
			printMap((it->second).child, prefix + it->first);
		}
	}
}

bool valid_x_y(int x, int y, const vector< vector<string> > &board)
{
	if( board.size() > 0 
		&& 0 <= x && x < board.size()
		&& 0 <= y && y < board[1].size() )
	{
		return true;
	}

	return false;
}

void traceWord( const vector< vector<string> > &board, 
					const map<char,node> &nodemap, 
					vector<string> &output,
					vector<string> &detailedOutput,
					unsigned x, unsigned y, 
					string route = "", string word = "", string previousDir = "")
{
	if( nodemap.size() == 0)
	{
		//This condition shouldn't be triggered!
		return;
	}
	
	//If we are starting at this location, set up init
	if( route.length() == 0)
	{
		stringstream ss;
		ss << "(" << x << "," << y << ") - ";
		route = ss.str();
	}

	//The char at the current location being processed
	char c = board[x][y][0];

	//If character is available in the wordmap, process it.
	if( nodemap.count(c) == 1)
	{
		word = word + c;
		const map<char,node> &child = nodemap.at(c).child;
		
		if(child.count(STOP) == 1)
		{
			output.push_back(word);
			stringstream ss;
			ss << "Found word <" << word << "> with the route: " << route << ".";
			detailedOutput.push_back(ss.str());
		}

		//For each child, look in all 4 directions (except the direction we reached the child from)
		// and go deeper
		int next_x, next_y;
		//UP
		if(previousDir != UP)
		{
			next_x = x - 1;
			next_y = y ;
			if(true == valid_x_y(next_x, next_y, board))
			{
				traceWord(board, child, output, detailedOutput, next_x, next_y, 
							route + UP, word, UP);
			}
		}
		
		//LEFT
		if(previousDir != LEFT)
		{
			next_x = x;
			next_y = y - 1;
			if(true == valid_x_y(next_x, next_y, board))
			{
				traceWord(board, child, output, detailedOutput, next_x, next_y, 
							route + LEFT, word);
			}
		}
		
		//RIGHT
		if(previousDir != RIGHT)
		{
			next_x = x ;
			next_y = y + 1;
			if(true == valid_x_y(next_x, next_y, board))
			{
				traceWord(board, child, output, detailedOutput, next_x, next_y, 
							route + RIGHT, word);
			}
		}
		
		//DOWN
		if(previousDir != DOWN)
		{
			next_x = x + 1;
			next_y = y ;
			if(true == valid_x_y(next_x, next_y, board))
			{
				traceWord(board, child, output, detailedOutput, next_x, next_y, 
							route + DOWN, word);
			}
		}
	}

}

void findAndListWords( const vector< vector<string> > &board, 
					const map<char,node> &wordTree, 
					vector<string> &output,
					vector<string> &detailedOutput)
{
	string word = "";

	for(unsigned i = 0; i < board.size(); i++)
	{
		for(unsigned j = 0; j < board[i].size(); j++)
		{
			//We are processing for i,j. We start there and keep going till we cannot anymore.
			traceWord(board, wordTree, output, detailedOutput, i, j);
		}
	}
	  
}


int main() 
{

	cout << endl << endl << "----- BOGGLE BOARD EXAMPLE -------" << endl << endl;

	vector<string> words = { "at","cab", "cat", "bat" };
	map<char, node> wordTree;
	buildTree(wordTree, words);

	cout << "Words:" << endl;
	printMap(wordTree);

	//Board is assumed to have all rows of the same length
	//Board is assumed to contain strings of length 1 depicting a lowercase alphabet
	const vector< vector<string> > board = {
	{"d", "b", "c"},
	{"a", "c", "a"},
	{"b", "a", "t"}
	};

	//Printing the board
	cout << endl << endl << "The board:" << endl;
	for(unsigned i = 0; i < board.size(); i++)
	{
		for(unsigned j = 0; j < board[i].size(); j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}

	vector<string> output, detailedOutput;

	findAndListWords(board, wordTree, output, detailedOutput);

	cout << endl << endl << "The result:" << endl;

	//If only words are needed, change detailedOutput to output in below block
	for(unsigned i = 0; i < detailedOutput.size(); ++i)
	{
		cout << detailedOutput[i] << endl;
	}


	return 0;
}


