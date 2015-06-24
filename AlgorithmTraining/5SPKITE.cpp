#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

inline int getInt()
{
	//#define getchar getchar_unlocked
	register int s = 0, ch;
	for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	for (s = ch - '0', ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar())
		s = s * 10 + ch - '0';
	return s;
}

int PlanetCoord[100 * 3];
void SPKITE()
{
	int numCase, numPlanet, numPlace, radius, refDistance, minDist, minIdx;
	numCase = getInt();
	
	for (int i = 0; i < numCase; i++)
	{
		std::vector<int> contractIdx;
		numPlanet = getInt();
		numPlace = getInt();
		radius = getInt();
		refDistance = getInt();
		for (int j = 0; j < numPlanet; j++)
		{
			PlanetCoord[j * 3] = getInt();
			PlanetCoord[j * 3 + 1] = getInt();
			PlanetCoord[j * 3 + 2] = getInt();
		}

		int oldX, oldY, oldZ, curX, curY, curZ;
		oldX = getInt();
		oldY = getInt();
		oldZ = getInt();
		for (int j = 0; j < numPlace; j++)
		{
			int curX = getInt();
			int curY = getInt();
			int curZ = getInt();

			//from this

// 			int curDistSQ;
// 			//find nearest planet
// 			minDist = std::numeric_limits<int>::max();
// 			for (int k = 0; k < numPlanet; k++)
// 			{
// 				int compX = PlanetCoord[k * 3];
// 				int compY = PlanetCoord[k * 3 + 1];
// 				int compZ = PlanetCoord[k * 3 + 2];
// 				curDistSQ = (curX - compX) * (curX - compX) +
// 							(curY - compY) * (curY - compY) +
// 							(curZ - compZ) * (curZ - compZ);
// 				if (curDistSQ < minDist)
// 				{
// 					minDist = curDistSQ;
// 					minIdx = k + 1;
// 				}
// 			}
// 			minDist = std::sqrt(minDist);
// 
// 			//condition for contact
// 			if (minDist <= refDistance + radius)
// 			{
// 				contractIdx.push_back(minIdx);
// 			}

		}

		std::sort(contractIdx.begin(), contractIdx.end());
		printf("%d ", contractIdx.size());
		for (int j = 0; j < contractIdx.size(); j++)
		{
			printf("%d ", contractIdx[j]);
		}
		printf("\n");
	}
}

void main()
{
	SPKITE();
	system("pause");
}