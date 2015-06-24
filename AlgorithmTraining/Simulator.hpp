#include <random>
#include <iostream>
#include <sstream>
#include <string>

#include "Clock.hpp"

template <class InputType, class OutputType>
class Simulator
{
public:
	Simulator(InputType* pData, int numCase, int arrHeight, int arrWidth, int lenOutput)
	{
		m_pData = pData;
		m_numCase = numCase;
		m_arrHeight = arrHeight;
		m_arrWidth = arrWidth;
		m_lenOutput = lenOutput;
	}

	~Simulator()
	{
	}

	void Generator(InputType minVal, InputType maxVal)
	{
		std::random_device randDev;
		std::mt19937 generator(randDev());
		std::uniform_real_distribution<float> distVal(0, 1);
		InputType interval = maxVal - minVal;

		for (int i = 0; i < m_numCase * m_arrWidth * m_arrHeight; i++)
		{
			m_pData[i] = (InputType)(distVal(generator) * interval + minVal);
		}
	}

	void CompareResult(void(*pFunc1)(void), void(*pFunc2)(void))
	{
		Clock myClock;
		myClock.MeasureBegin();
		std::stringstream ss1, ss2;
		auto oldCoutBuf = std::cout.rdbuf(ss1.rdbuf());		//redirect to ss1
		pFunc1();
		myClock.MeasureEnd();
		
		double t1 = myClock.GetSectionTime();

		std::cout.rdbuf(ss2.rdbuf());	//redirect to ss2
		pFunc2();
		
		std::cout.rdbuf(oldCoutBuf);	//restore original cout

		std::cout << "time : " << t1 << "\n";

// 		for (int c = 0; c < m_numCase; c++)
// 		{
// 			for (int l = 0; l < m_lenOutput; l++)
// 			{
// 				OutputType tmp1, tmp2;
// 				ss1 >> tmp1;
// 				ss2 >> tmp2;
// 				if (tmp1 != tmp2)
// 				{
// 					std::cout << "different case occurs\n";
// 					InputType* curData = pData + c * m_arrWidth * m_arrHeight;
// 					for (int row = 0; row < m_arrHeight; row++)
// 					{
// 						for (int col = 0; col < m_arrWidth; col++)
// 						{
// 							std::cout << curData[m_arrWidth * row + col] << " ";
// 						}
// 						std::cout << "\n";
// 					}
// 
// 					c = m_numCase;	//exit double loop
// 					break;
// 				}
// 			}
// 		}
// 
// 		std::cout << "all results are the same\n";
	}

private:
	int m_numCase;
	int m_arrWidth;
	int m_arrHeight;
	int m_lenOutput;

	InputType* m_pData;
};