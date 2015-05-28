#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NODE_NUM	26	//number of alphabet possibility
void Dictionary()
{
	/* data input */
	int maxWords = 1000;
	int maxLength = 21;	// 20 + 1(for end_of_string)
	int caseStep = maxWords * maxLength;
	int numCase;
	scanf("%d", &numCase);

	int inputSize = numCase * caseStep * sizeof(char);
	char* inputData = (char*)malloc(inputSize);
	memset(inputData, 0, inputSize);
	int* inputNumWords = (int*)malloc(numCase * sizeof(int));

	for (int i = 0; i < numCase; i++)
	{
		int numWords;
		scanf("%d", &numWords);
		inputNumWords[i] = numWords;

		int curCase = i * caseStep;
		for (int j = 0; j < numWords; j++)
		{
			std::string tmpStr;
			std::cin >> tmpStr;
			strcpy(inputData + curCase + j*maxLength, tmpStr.c_str());
		}
	}

	/* algorithm */
	typedef struct _Node
	{
		std::vector<_Node*> inEdges;
		std::vector<_Node*> outEdges;
		int nodeVal;
		bool isChecked;

		_Node()
		{
			nodeVal = 0;
			isChecked = false;
		}
	} Node;

	for (int i = 0; i < numCase; i++)
	{
		/* build the graph */
		char* curData = inputData + i * caseStep;
		Node nodes[NODE_NUM];	//26 : lower case alphabet a to z
		for (int j = 0; j < NODE_NUM; j++)
		{
			nodes[j].nodeVal = j;
		}

		// extract order condition info from the data to the graph data structure
		std::vector<std::pair<int, int> > curProcess;
		curProcess.push_back(std::make_pair(0, inputNumWords[i]));	// (startIdx, size)
		for (int j = 0; j < maxLength; j++)
		{
			if (curProcess.empty())	//termination condition
			{
				break;
			}

			std::vector<std::pair<int, int> > nextProcess;
			for (int k = 0; k < curProcess.size(); k++)
			{
				int dupStart = -1;
				char prevChar = 0;
				char curChar = 0;
				for (int idx = curProcess[k].first; idx < curProcess[k].first + curProcess[k].second; idx++)
				{
					curChar = curData[idx * maxLength + j];

					if (dupStart == -1)
					{
						if (curChar == '\0')
						{
							continue;
						}
						
						if (prevChar == curChar)
						{
							dupStart = idx - 1;
						}
						else
						{
							if (prevChar == 0)
							{
								prevChar = curChar;
								continue;
							}
							nodes[prevChar - 'a'].outEdges.push_back(&nodes[curChar - 'a']);
							nodes[curChar - 'a'].inEdges.push_back(&nodes[prevChar - 'a']);
						}
					}
					else
					{
						if (prevChar != curChar)
						{
							int dupSize = idx - dupStart;
							nextProcess.push_back(std::make_pair(dupStart, dupSize));
							dupStart = -1;

							if (curChar == '\0')
							{
								continue;
							}

							nodes[prevChar - 'a'].outEdges.push_back(&nodes[curChar - 'a']);
							nodes[curChar - 'a'].inEdges.push_back(&nodes[prevChar - 'a']);
						}
					}
					prevChar = curChar;
				}

				if (dupStart != -1)
				{
					int dupSize = (curProcess[k].first + curProcess[k].second) - dupStart;
					nextProcess.push_back(std::make_pair(dupStart, dupSize));
				}
			}
			curProcess.clear();
			curProcess = nextProcess;
		}

		/* decode the graph, and get the entire order */
		std::string answerStr;
		std::vector<int> notCheckedIdx(26);
		for (int j = 0; j < 26; j++)
			notCheckedIdx[j] = j;
		while (!notCheckedIdx.empty())
		{
			int prevNodeNum = notCheckedIdx.size();
			for (int j = 0; j < notCheckedIdx.size(); j++)
			{
				int curIdx = notCheckedIdx[j];
				int numPrev = 0;
				for (int k = 0; k < nodes[curIdx].inEdges.size(); k++)
				{
					if (!nodes[curIdx].inEdges[k]->isChecked)
						numPrev++;
				}
				if (!numPrev)
				{
					answerStr.push_back(nodes[curIdx].nodeVal + 'a');
					nodes[curIdx].isChecked = true;
					notCheckedIdx.erase(notCheckedIdx.begin() + j);
				}
			}

			if (prevNodeNum == notCheckedIdx.size())	//if there is cyclic component, then no reduction occurs
			{
				answerStr.clear();
				answerStr = "INVALID HYPOTHESIS";
				break;
			}
		}
		std::cout << answerStr << std::endl;
	}

	free(inputData);
	free(inputNumWords);
}

//int main()
//{
//	Dictionary();
//	system("pause");
//
//	return 0;
//}