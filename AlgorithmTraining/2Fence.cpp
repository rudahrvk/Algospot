#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

// int recFence(int* arrFence, int leftIdx, int rightIdx, int curMax)
// {
// 	if(leftIdx >= rightIdx)
// 	{
// 		return curMax;
// 	}
// 
// 	int width = rightIdx - leftIdx;
// 	int height = 10001;		//max limit of height is 10000
// 	int pivotIdx = leftIdx;
// 	
// 	//find min height(pivot) in the subArr
// 	for(int i = leftIdx; i < rightIdx; i++)
// 	{
// 		if(height > arrFence[i])
// 		{
// 			height = arrFence[i];
// 			pivotIdx = i;
// 		}
// 	}
// 	int newRegion = width * height;
// 	int newMax = (newRegion > curMax) ? newRegion : curMax;
// 	newMax = recFence(arrFence, leftIdx, pivotIdx, newMax);
// 	newMax = recFence(arrFence, pivotIdx + 1, rightIdx, newMax);
// 
// 	return newMax;
// }

void Fence()
{
	/* input handling */
	int numCase;	// numCase <= 50
	int maxBoard = 20000;
	int numBoard[50];
	int answer[50];
	int* arrFenceAll = new int[ 50 * maxBoard ];
	scanf("%d", &numCase);
	for(int i = 0; i < numCase; i++)
	{
		//std::cin >> numBoard[i];
		scanf("%d", &numBoard[i]);
		int* pCurFence = arrFenceAll + i * maxBoard;
		for(int j = 0; j < numBoard[i]; j++)
		{
			//std::cin >> pCurFence[j];
			scanf("%d", &pCurFence[j]);
		}
	}

	/* algorithm */
// 	for(int i = 0; i < numCase; i++)
// 	{
// 		int* pCurFence = arrFenceAll + i * maxBoard;
// 		answer[i] = recFence(pCurFence, 0, numBoard[i], 0);
// 	}

// 	for (int i = 0; i < numCase; i++)
// 	{
// 		int* pCurFence = arrFenceAll + i * maxBoard;
// 		int curMaxRegion = 0;
// 		std::vector<std::pair<int, int> > sideIdxs;	// (startIdx, endIdx)
// 		sideIdxs.push_back(std::make_pair(0, numBoard[i]));
// 		while (!sideIdxs.empty())
// 		{
// 			std::vector<std::pair<int, int> > tmpIdxs; 
// 			for (int j = 0; j < sideIdxs.size(); j++)
// 			{
// 				int width = sideIdxs[j].second - sideIdxs[j].first;
// 				int minIdx = std::distance(pCurFence, std::min_element(pCurFence + sideIdxs[j].first, pCurFence + sideIdxs[j].second));
// 				int height = pCurFence[minIdx];
// 				int newMax = width * height;
// 				curMaxRegion = (newMax > curMaxRegion) ? newMax : curMaxRegion;
// 
// 				int leftStart = sideIdxs[j].first;
// 				int leftEnd = minIdx;
// 				int rightStart = minIdx + 1;
// 				int rightEnd = sideIdxs[j].second;
// 
// 				if (leftStart < leftEnd)
// 					tmpIdxs.push_back(std::make_pair(leftStart, leftEnd));
// 				if (rightStart < rightEnd)
// 					tmpIdxs.push_back(std::make_pair(rightStart, rightEnd));
// 			}
// 			sideIdxs.clear();
// 			sideIdxs = tmpIdxs;
// 		}
// 		answer[i] = curMaxRegion;
// 	}

	typedef struct
	{
		int height;
		int start;
		int end;
	} Node;
	for (int i = 0; i < numCase; i++)
	{
		int* pCurFence = arrFenceAll + i * maxBoard;
		Node* nodes = new Node[numBoard[i]];
		std::vector<Node*> myStack;
		for (int j = 0; j < numBoard[i]; j++)
		{
			nodes[j].height = pCurFence[j];
			while (!myStack.empty() && myStack.back()->height > pCurFence[j])
			{
				myStack.back()->end = j;
				myStack.pop_back();
			}
			myStack.push_back(&nodes[j]);
		}
		while (!myStack.empty())
		{
			myStack.back()->end = numBoard[i];
			myStack.pop_back();
		}
		for (int j = numBoard[i] - 1; j >= 0; j--)
		{
			while (!myStack.empty() && myStack.back()->height > pCurFence[j])
			{
				myStack.back()->start = j + 1;
				myStack.pop_back();
			}
			myStack.push_back(&nodes[j]);
		}
		while (!myStack.empty())
		{
			myStack.back()->start = 0;
			myStack.pop_back();
		}

		int maxRegion = 0;
		for (int j = 0; j < numBoard[i]; j++)
		{
			int newRegion = (nodes[j].end - nodes[j].start) * nodes[j].height;
			maxRegion = (newRegion > maxRegion) ? newRegion : maxRegion;
		}
		answer[i] = maxRegion;
		delete[] nodes;
	}

	/* output */
	for(int i = 0; i < numCase; i++)
	{
		//std::cout << answer[i] << "\n";
		printf("%d\n", answer[i]);
	}

	delete[] arrFenceAll;
}

// int main()
// {
// 	Fence();
// 	system("pause");
// 	return 0;
// }