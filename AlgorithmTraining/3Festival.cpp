#include <iostream>
#include <stdio.h>
#include <vector>
#include <random>

#define maxCase	100
#define	maxN	1000 //10

typedef	int* ArrPtr;

void Festival()
{
	/* Input */
	int numCase;	// C <= 100
	int numN[maxCase];	// 1 <= N <= 1000
	int numL[maxCase];	// 1 <= L <= N

	scanf("%d", &numCase);
	// 1. int or char? (value is positive integer <= 100)	=> no difference
	// 2. local variable via dynamic array  vs.  global variable via static array(fixed size)	=> no difference
	ArrPtr arrFestAll = new int[numCase * maxN];
	for (int i = 0; i < numCase; i++)
	{
		scanf("%d %d", &numN[i], &numL[i]);
		ArrPtr curFest = arrFestAll + i * maxN;

		scanf("%d", &curFest[0]);
		for (int j = 1; j < numN[i]; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			curFest[j] = curFest[j - 1] + tmp;
		}
	}

	/* algorithm */
	for (int i = 0; i < numCase; i++)
	{
		ArrPtr curFest = arrFestAll + i * maxN;

		int minLen = numL[i];
		int minSum = curFest[minLen - 1];
		int curLen, curSum, startMax;
		for (int len = numL[i]; len <= numN[i]; len++)
		{
			curLen = len;
			startMax = numN[i] - len;

			curSum = curFest[len - 1];
			if (minSum * curLen > curSum * minLen)
			{
				minLen = curLen;
				minSum = curSum;
			}
			for (int startIdx = 1; startIdx <= startMax; startIdx++)
			{
				curSum = curFest[startIdx + len - 1] - curFest[startIdx - 1];
				if (minSum * curLen > curSum * minLen)
				{
					minLen = curLen;
					minSum = curSum;
				}
			}
		}
		// 3. Separate or not the output part with algorithm loop => no difference
		printf("%.8f\n", (double)minSum / minLen);
	}

	delete[] arrFestAll;
}

void FestivalTest()
{
	/* Input */
	int numCase = maxCase;
	int numN[maxCase];	// 1 <= N <= 1000
	int numL[maxCase];	// 1 <= L <= N
	double answer[maxCase];
	ArrPtr arrFestAll = new int[numCase * maxN];

	std::random_device randDev;
	std::mt19937 generator(randDev());
	std::uniform_int_distribution<int> distN(1, maxN);
	std::uniform_int_distribution<int> distVal(1, 10);

	for (int i = 0; i < numCase; i++)
	{
		numN[i] = distN(generator);
		std::uniform_int_distribution<int> distL(1, numN[i]);
		numL[i] = distL(generator);
		ArrPtr curFest = arrFestAll + i * maxN;
		for (int j = 0; j < numN[i]; j++)
		{
			curFest[j] = distVal(generator);
		}
	}

	for (int i = 0; i < numCase; i++)
	{
		std::cout << "casenum is : " << i << std::endl;
		system("pause");

		/* Algorithm _ old */
		typedef struct _Node
		{
			int startIdx;
			int size;
			double avgVal;
			_Node()
			{
				avgVal = 0;
			}
		} Node;

		double minAvg;

		ArrPtr curFest = arrFestAll + i * maxN;
		int maxLen = numN[i] - numL[i] + 1;
		Node* pNodes = new Node[maxLen * maxLen];

		//calculate the initial entry Node(00)
		for (int j = 0; j < numL[i]; j++)
		{
			pNodes[0].avgVal += curFest[j];
		}
		pNodes[0].avgVal /= numL[i];
		pNodes[0].startIdx = 0;
		pNodes[0].size = numL[i];
		minAvg = pNodes[0].avgVal;

		//dynamic process
		for (int row = 1; row < maxLen; row++)
		{
			Node* curNodes = pNodes + row * maxLen;
			Node* prevRowNode = curNodes - maxLen;

			//calculate the initial Node of each row
			curNodes[0].avgVal = (prevRowNode[0].avgVal * prevRowNode[0].size + curFest[prevRowNode[0].size]) / (prevRowNode[0].size + 1);
			curNodes[0].startIdx = 0;
			curNodes[0].size = prevRowNode[0].size + 1;
			minAvg = (minAvg > curNodes[0].avgVal) ? curNodes[0].avgVal : minAvg;

			for (int col = 1; col <= row; col++)
			{
				curNodes[col].avgVal = (curNodes[col - 1].avgVal * curNodes[col - 1].size - curFest[curNodes[col - 1].startIdx]) / (curNodes[col - 1].size - 1);
				curNodes[col].startIdx = curNodes[col - 1].startIdx + 1;
				curNodes[col].size = curNodes[col - 1].size - 1;
				minAvg = (minAvg > curNodes[col].avgVal) ? curNodes[col].avgVal : minAvg;
			}
		}
		delete[] pNodes;


		/* Algorithm new */
		curFest = arrFestAll + i * maxN;
		double minAvg2;
		int finalStart, finalEnd;
		finalStart = 0;
		finalEnd = numN[i] - 1;
		while (true)
		{
			//forward process
			int endIdx = numL[i] - 1 + finalStart;
			double curAvg = 0;
			for (int j = finalStart; j <= endIdx; j++)
			{
				curAvg += curFest[j];
			}
			curAvg /= numL[i];
			minAvg2 = curAvg;
			for (int j = endIdx + 1; j <= finalEnd; j++)
			{
				curAvg = (curAvg * (j - finalStart) + curFest[j]) / (j - finalStart + 1);
				if (minAvg2 > curAvg)
				{
					minAvg2 = curAvg;
					endIdx = j;
				}
			}

			//backward process
			int startIdx = endIdx - numL[i] + 1;
			curAvg = 0;
			for (int j = endIdx; j >= startIdx; j--)
			{
				curAvg += curFest[j];
			}
			curAvg /= numL[i];
			minAvg2 = curAvg;
			for (int j = startIdx - 1; j >= finalStart; j--)
			{
				curAvg = (curAvg * (endIdx - j) + curFest[j]) / (endIdx - j + 1);
				if (minAvg2 > curAvg)
				{
					minAvg2 = curAvg;
					startIdx = j;
				}
			}

			if (finalStart == startIdx && finalEnd == endIdx)
			{
				break;
			}
			else
			{
				finalStart = startIdx;
				finalEnd = endIdx;
			}
		}
		
		if (minAvg != minAvg2)
		{
			std::cout << "curList" << std::endl;
			for (int j = 0; j < numN[i]; j++)
			{
				std::cout << curFest[j] << " ";
			}
			std::cout << std::endl;
			std::cout << "numL is " << numL[i] << std::endl;
			printf("true : %.8f,  false : %.8f\n", minAvg, minAvg2);
		}
	}

	delete[] arrFestAll;
}

// int main()
// {
// 	Festival();
// 	//FestivalTest();
// 	system("pause");
// 	return 0;
// }


// 	typedef struct _Node
// 	{
// 		int startIdx;
// 		int size;
// 		double avgVal;
// 		_Node()
// 		{
// 			avgVal = 0;
// 		}
// 	} Node;
// 	for (int i = 0; i < numCase; i++)
// 	{
// 		double minAvg;
// 
// 		ArrPtr curFest = arrFestAll + i * maxN;
// 		int maxLen = numN[i] - numL[i] + 1;
// 		Node* pNodes = new Node[maxLen * maxLen];
// 
// 		//calculate the initial entry Node(00)
// 		for (int j = 0; j < numL[i]; j++)
// 		{
// 			pNodes[0].avgVal += curFest[j];
// 		}
// 		pNodes[0].avgVal /= numL[i];
// 		pNodes[0].startIdx = 0;
// 		pNodes[0].size = numL[i];
// 		minAvg = pNodes[0].avgVal;
// 
// 		//dynamic process
// 		for (int row = 1; row < maxLen; row++)
// 		{
// 			Node* curNodes = pNodes + row * maxLen;
// 			Node* prevRowNode = curNodes - maxLen;
// 
// 			//calculate the initial Node of each row
// 			curNodes[0].avgVal = (prevRowNode[0].avgVal * prevRowNode[0].size + curFest[prevRowNode[0].size]) / (prevRowNode[0].size + 1);
// 			curNodes[0].startIdx = 0;
// 			curNodes[0].size = prevRowNode[0].size + 1;
// 			minAvg = (minAvg > curNodes[0].avgVal) ? curNodes[0].avgVal : minAvg;
// 
// 			for (int col = 1; col <= row; col++)
// 			{
// 				curNodes[col].avgVal = (curNodes[col - 1].avgVal * curNodes[col - 1].size - curFest[curNodes[col - 1].startIdx]) / (curNodes[col - 1].size - 1);
// 				curNodes[col].startIdx = curNodes[col - 1].startIdx + 1;
// 				curNodes[col].size = curNodes[col - 1].size - 1;
// 				minAvg = (minAvg > curNodes[col].avgVal) ? curNodes[col].avgVal : minAvg;
// 			}
// 		}
// 
// 		answer[i] = minAvg;
// 		delete[] pNodes;
// 	}
//
// 	for (int i = 0; i < numCase; i++)
// 	{
// 		ArrPtr curFest = arrFestAll + i * maxN;
// 
// 		//forward process
// 		int endIdx = numL[i] - 1;
// 		double curAvg = 0;
// 		double minAvg;
// 		for (int j = 0; j < numL[i]; j++)
// 		{
// 			curAvg += curFest[j];
// 		}
// 		curAvg /= numL[i];
// 		minAvg = curAvg;
// 		for (int j = numL[i]; j < numN[i]; j++)
// 		{
// 			curAvg = (curAvg * j + curFest[j]) / (j + 1);
// 			if (minAvg > curAvg)
// 			{
// 				minAvg = curAvg;
// 				endIdx = j;
// 			}
// 		}
// 
// 		//backward process
// 		int startIdx = endIdx - numL[i] + 1;
// 		curAvg = 0;
// 		for (int j = endIdx; j >= startIdx; j--)
// 		{
// 			curAvg += curFest[j];
// 		}
// 		curAvg /= numL[i];
// 		minAvg = curAvg;
// 		for (int j = startIdx - 1; j >= 0; j--)
// 		{
// 			curAvg = (curAvg * (endIdx - j) + curFest[j]) / (endIdx - j + 1);
// 			if (minAvg > curAvg)
// 			{
// 				minAvg = curAvg;
// 				//startIdx = j;
// 			}
// 		}
// 		answer[i] = minAvg;
// 	}
//
// 	for (int i = 0; i < numCase; i++)
// 	{
// 		ArrPtr curFest = arrFestAll + i * maxN;
// 		
// 		double minAvg;
// 		int finalStart, finalEnd;
// 		finalStart = 0;
// 		finalEnd = numN[i] - 1;
// 		while (true)
// 		{
// 			//forward process
// 			int endIdx = numL[i] - 1 + finalStart;
// 			double curAvg = 0;
// 			for (int j = finalStart; j <= endIdx; j++)
// 			{
// 				curAvg += curFest[j];
// 			}
// 			curAvg /= numL[i];
// 			minAvg = curAvg;
// 			for (int j = endIdx + 1; j <= finalEnd; j++)
// 			{
// 				curAvg = (curAvg * (j - finalStart) + curFest[j]) / (j - finalStart + 1);
// 				if (minAvg > curAvg)
// 				{
// 					minAvg = curAvg;
// 					endIdx = j;
// 				}
// 			}
// 
// 			//backward process
// 			int startIdx = endIdx - numL[i] + 1;
// 			curAvg = 0;
// 			for (int j = endIdx; j >= startIdx; j--)
// 			{
// 				curAvg += curFest[j];
// 			}
// 			curAvg /= numL[i];
// 			minAvg = curAvg;
// 			for (int j = startIdx - 1; j >= finalStart; j--)
// 			{
// 				curAvg = (curAvg * (endIdx - j) + curFest[j]) / (endIdx - j + 1);
// 				if (minAvg > curAvg)
// 				{
// 					minAvg = curAvg;
// 					startIdx = j;
// 				}
// 			}
// 
// 			if (finalStart == startIdx && finalEnd == endIdx)
// 			{
// 				break;
// 			}
// 			else
// 			{
// 				finalStart = startIdx;
// 				finalEnd = endIdx;
// 			}
// 		}
// 		answer[i] = minAvg;
// 	}