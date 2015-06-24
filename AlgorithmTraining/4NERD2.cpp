#include <iostream>
#include <map>

#include "Simulator.hpp"

inline int getInt() 
{
//#define getchar getchar_unlocked
	register int s = 0, ch;
	for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	for (s = ch - '0', ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar())
		s = s * 10 + ch - '0';
	return s;
}

void Nerd2()
{
	typedef std::map<int, int> RBTreeInt;
	int numCase, numN;
	numCase = getInt();
	for (int c = 0; c < numCase; c++)
	{
 		numN = getInt();
		int sum = 0;
		RBTreeInt treeData;
		for (int i = 0; i < numN; i++)
		{
			int curX = getInt();
			int curY = getInt();
			RBTreeInt::iterator itLowerBound = treeData.lower_bound(curX);
			if (itLowerBound != treeData.end() && itLowerBound->second > curY)	// cannot be inserted
			{
				sum += treeData.size();
				continue;
			}

			if (itLowerBound != treeData.begin())	// erase invalidated data
			{
				itLowerBound--;
				RBTreeInt::iterator itTmp;
				while (itLowerBound->second < curY)
				{
					if (itLowerBound == treeData.begin())
					{
						treeData.erase(itLowerBound);
						break;
					}
					itTmp = itLowerBound;
					itTmp--;
					treeData.erase(itLowerBound);
					itLowerBound = itTmp;
				}
			}

			treeData[curX] = curY;	// insert cur data
			sum += treeData.size();
		}
		printf("%d\n", sum);
	}
}

//int main()
//{
//
//// 	Simulator<int, int> mySimulator(pData, 50, 50000, 2, 1);
//// 	mySimulator.Generator(0, 100000);
//// 	mySimulator.CompareResult(&Nerd2, &Nerd2);
//
//	Nerd2();
// 	system("pause");
//	return 0;
//}