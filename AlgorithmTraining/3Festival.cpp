#include <iostream>
#include <stdio.h>
#define maxCase	100
#define	maxN	1000

typedef	int* ArrPtr;

void Festival()
{
	/* Input */
	int numCase;	// C <= 100
	int numN[maxCase];	// 1 <= N <= 1000
	int numL[maxCase];	// 1 <= L <= N
	double answer[maxCase];

	scanf("%d", &numCase);
	// 1. int or char? (value is positive integer <= 100)
	// 2. local variable via dynamic array  vs.  global variable via static array(fixed size)
	ArrPtr arrFestAll = new int[numCase * maxN];
	for (int i = 0; i < numCase; i++)
	{
		scanf("%d %d", &numN[i], &numL[i]);
		ArrPtr curFest = arrFestAll + i * maxN;
		for (int j = 0; j < numN[i]; j++)
		{
			scanf("%d", &curFest[j]);
		}
	}

	/* algorithm */
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
	for (int i = 0; i < numCase; i++)
	{
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
		answer[i] = minAvg;
		delete[] pNodes;
	}

	/* output */
	// 3. Separate or not the output part with algorithm loop => separate is faster
	for (int i = 0; i < numCase; i++)
	{
		printf("%.8f\n", answer[i]);
	}

	delete[] arrFestAll;
}

int main()
{
	Festival();
	system("pause");
	return 0;
}