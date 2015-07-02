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
template <typename T>
inline T GetSquare(T x) { return x * x; }
template <typename T>
inline T GetDistSQ(float t, int p1, int p2, int p3, int a1, int a2, int a3, int b1, int b2, int b3)
{
	return GetSquare<T>(a1 + t*(b1 - a1) - p1) + GetSquare<T>(a2 + t*(b2 - a2) - p2) + GetSquare<T>(a3 + t*(b3 - a3) - p3);
}

// inline std::pair<float, float> GetIntersection(int p1, int p2, int p3, int a1, int a2, int a3, int b1, int b2, int b3, int maxDist)
// {
// 	int A = GetSquare(b1 - a1) + GetSquare(b2 - a2) + GetSquare(b3 - a3);
// 	int B = 2 * ((a1 - p1)*(b1 - a1) + (a2 - p2)*(b2 - a2) + (a3 - p3)*(b3 - a3));
// 	int C = a1*a1 + a2*a2 + a3*a3 + p1*p1 + p2*p2 + p3*p3 - maxDist*maxDist - 2 * (a1*p1 + a2*p2 + a3*p3);
// 	float root = std::sqrt(B*B - 4 * A*C);
// 	return std::make_pair((float)(-B + root) / (2 * A), (float)(-B - root) / (2 * A));
// }

inline float GetIntersection(int p1, int p2, int p3, int pp1, int pp2, int pp3, int a1, int a2, int a3, int b1, int b2, int b3)
{
	int upper = (p1*p1 - pp1*pp1) + (p2*p2 - pp2*pp2) + (p3*p3 - pp3*pp3) - 2 * a1*(p1 - pp1) - 2 * a2*(p2 - pp2) - 2 * a3*(p3 - pp3);
	int lower = 2 * (p1 - pp1)*(b1 - a1) + 2 * (p2 - pp2)*(b2 - a2) + 2 * (p3 - pp3)*(b3 - a3);
	return (lower == 0) ? 0 : (float)upper / lower;
}
inline float GetExtvalCoord(int p1, int p2, int p3, int a1, int a2, int a3, int b1, int b2, int b3)
{
	return (float)((b1 - a1)*(p1 - a1) + (b2 - a2)*(p2 - a2) + (b3 - a3)*(p3 - a3)) / (GetSquare<int>(b1 - a1) + GetSquare<int>(b2 - a2) + GetSquare<int>(b3 - a3));
}



int PlanetCoord[100 * 3];
void SPKITE()
{
	int numCase, numPlanet, numPlace, radius, refDistance, minDist, minIdx;
	numCase = getInt();
	
	for (int i = 0; i < numCase; i++)
	{
		std::vector<int> contactIdx;
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

			// from oldXYZ to curXYZ, possible range of t is, 0 <= t <= 1
			// find minDist planet when t = 0
			int curDistSQ, minIdx;
			float minDist = std::numeric_limits<float>::max();
			for (int k = 0; k < numPlanet; k++)
			{
				int p1 = PlanetCoord[k * 3];
				int p2 = PlanetCoord[k * 3 + 1];
				int p3 = PlanetCoord[k * 3 + 2];

				curDistSQ = GetDistSQ<float>(0, p1, p2, p3, oldX, oldY, oldZ, curX, curY, curZ);
				if (curDistSQ < minDist)
				{
					minDist = curDistSQ;
					minIdx = k + 1;
				}
			}
			minDist = std::sqrt(minDist);

			//condition for contact
			if (minDist <= refDistance + radius)
			{
				contactIdx.push_back(minIdx);
			}

			// find intersection points

			float divRate = 0.01;
			float err = divRate / 10;
			for (float t = 0; t <= 1; t += divRate)
			{
				std::vector<int> minIdxs;
				float minDist = std::numeric_limits<float>::max();
				for (int k = 0; k < numPlanet; k++)
				{
					int p1 = PlanetCoord[k * 3];
					int p2 = PlanetCoord[k * 3 + 1];
					int p3 = PlanetCoord[k * 3 + 2];
					float curDistSQ = GetDistSQ<float>(t, p1, p2, p3, oldX, oldY, oldZ, curX, curY, curZ);
					if (curDistSQ < minDist)
					{
						minDist = curDistSQ;
						minIdxs.clear();
						minIdxs.push_back(k + 1);
					}
					else if (curDistSQ == minDist)
					{
						minIdxs.push_back(k + 1);
					}
				}
				minDist = std::sqrt(minDist);

				if (minDist <= refDistance + radius + err)
				{
					contactIdx.insert(contactIdx.begin(), minIdxs.begin(), minIdxs.end());
				}
			}

// 			float prev_t, cur_t;
// 			prev_t = 0;
// 			std::vector<int> prevIdxs;
// 			std::vector<int> curIdxs;
// 			int prevIdx;
// 			prevIdx = minIdx;
// 			prevIdxs.push_back(minIdx);
// 			while (1)
// 			{
// 				int p1 = PlanetCoord[(prevIdx - 1) * 3];
// 				int p2 = PlanetCoord[(prevIdx - 1) * 3 + 1];
// 				int p3 = PlanetCoord[(prevIdx - 1) * 3 + 2];
// 
// 				//find next t (nearest intersection point)
// 				cur_t = 1;
// 				for (int k = 0; k < numPlanet; k++)
// 				{
// 					int pp1 = PlanetCoord[k * 3];
// 					int pp2 = PlanetCoord[k * 3 + 1];
// 					int pp3 = PlanetCoord[k * 3 + 2];
// 
// 					float tmp_t = GetIntersection(p1, p2, p3, pp1, pp2, pp3, oldX, oldY, oldZ, curX, curY, curZ);
// 					if (tmp_t > prev_t && tmp_t < 1 && tmp_t <= cur_t)
// 					{
// 						if (tmp_t < cur_t)
// 						{
// 							curIdxs.clear();
// 						}
// 						cur_t = tmp_t;
// 						curIdxs.push_back(k + 1);
// 					}
// 				}
// 
// 				//find entire contact of prevMin
// 				for (auto v : prevIdxs)
// 				{
// 					int pp1 = PlanetCoord[(v - 1) * 3];
// 					int pp2 = PlanetCoord[(v - 1) * 3 + 1];
// 					int pp3 = PlanetCoord[(v - 1) * 3 + 2];
// 					float ext_t = GetExtvalCoord(p1, p2, p3, oldX, oldY, oldZ, curX, curY, curZ);
// 					float ext_dist = std::sqrt(GetDistSQ<float>(ext_t, p1, p2, p3, oldX, oldY, oldZ, curX, curY, curZ));
// 					if (ext_t < cur_t && ext_t >= 0 && ext_dist <= refDistance + radius)
// 					{
// 						contactIdx.push_back(v);
// 					}
// 				}
// 				prevIdxs.clear();
// 
// 				if (curIdxs.empty())
// 				{
// 					break;
// 				}
// 
// 				int newIdx;
// 				std::vector<float> vDists;
// 				float minVal = std::numeric_limits<float>::max();
// 				for (auto v : curIdxs)
// 				{
// 					int pp1 = PlanetCoord[(v - 1) * 3];
// 					int pp2 = PlanetCoord[(v - 1) * 3 + 1];
// 					int pp3 = PlanetCoord[(v - 1) * 3 + 2];
// 					float distVal = GetDistSQ<float>(cur_t + 0.01, pp1, pp2, pp3, oldX, oldY, oldZ, curX, curY, curZ);
// 					vDists.push_back(distVal);
// 					if (distVal < minVal)
// 					{
// 						newIdx = v;
// 						minVal = distVal;
// 					}
// 				}
// 				for (int k = 0; k < vDists.size(); k++)
// 				{
// 					if (vDists[k] == minVal)
// 						prevIdxs.push_back(curIdxs[k]);
// 				}
// 
// 				
// 				int pp1 = PlanetCoord[(curIdxs[0] - 1) * 3];
// 				int pp2 = PlanetCoord[(curIdxs[0] - 1) * 3 + 1];
// 				int pp3 = PlanetCoord[(curIdxs[0] - 1) * 3 + 2];
// 
// 				float intersectDist = std::sqrt(GetDistSQ<float>(cur_t, pp1, pp2, pp3, oldX, oldY, oldZ, curX, curY, curZ));
// 				if (intersectDist <= refDistance + radius)
// 				{
// 					contactIdx.insert(contactIdx.begin(), curIdxs.begin(), curIdxs.end());
// 				}
// 				prev_t = cur_t;
// 				prevIdx = newIdx;
// 				curIdxs.clear();
// 			}

			oldX = curX;
			oldY = curY;
			oldZ = curZ;
		}

		std::sort(contactIdx.begin(), contactIdx.end());
		contactIdx.erase(std::unique(contactIdx.begin(), contactIdx.end()), contactIdx.end());
		printf("%d ", contactIdx.size());
		for (int j = 0; j < contactIdx.size(); j++)
		{
			printf("%d ", contactIdx[j]);
		}
		printf("\n");
	}
}

void main()
{
	SPKITE();
	system("pause");
}