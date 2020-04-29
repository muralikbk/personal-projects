/*
 * input: an int i
 * return: a buffer containing a null-terminated
 *         string representation of i in base 10
 * Without using itoa or stringstream, etc.
 * e.g.
 * cout << int_to_str(10) << endl;
 * prints to cout:
 * 10
 */

#include <new>
#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

const int MAX_BUF_SIZE = 100;
char* int_to_str (int i) 
{
	char *str = new char[MAX_BUF_SIZE];
	memset(str, 0, MAX_BUF_SIZE);
	int sign = 1;
	if(i < 0) sign = -1;
	i = i * sign;
	int j = 0;
	
	do
	{
		str[j] = '0' + (i% 10);
		i = i/10;
		++j;
	}
	while( i != 0);

	if(sign == -1)
	{
		str[j] = '-';
		++j;
	}
	str[j] = '\0';
	j = 0;
	int len = strlen(str);
	
	for(; j < len/2 ; ++j)
	{
		char temp = str[j];
		str[j] = str[len - j - 1];
		str[len-j-1] = temp;
	}
	return str;
}

int main(int argc, char * argv[])
{
	char *str = int_to_str(35);
	cout << str << endl;
	delete[] str;
	char *str1 = int_to_str(-305);
	cout << str1 << endl;
	delete[] str1;
}
