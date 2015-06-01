#include <iostream>

inline int getInt() 
{
//#define getchar getchar_unlocked
	register int s = 0, ch;
	for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	for (s = ch - '0', ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar())
		s = s * 10 + ch - '0';
	return s;
}

int pData[50000 * 2];
void Nerd2()
{
	int numCase, numN;
	numCase = getInt();
	for (; numCase--;)
	{
		numN = getInt();
		for (int i = 0; i < numN; i++)
		{
			pData[2 * i] = getInt();
			pData[2 * i + 1] = getInt();
		}



	}
}

int main()
{
	Nerd2();
	system("pause");
	return 0;
}