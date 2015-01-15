#include "SimObject.hpp"
#include "Cell.hpp"
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

vector<SimObject> CreateSimObjects(int spaceWidth);
Cell* CreateSpaceGrid(vector<SimObject>& simObjects, int spaceWidth);
struct lessThanPair;

int main()
{
	int spaceWidth = 4;
	vector<SimObject> simObjects = CreateSimObjects(spaceWidth);
	Cell* spaceGridRoot = CreateSpaceGrid(simObjects, spaceWidth);
	delete spaceGridRoot;
	return 0;
}

vector<SimObject> CreateSimObjects(int spaceWidth)
{
	int numObjects = 5;
	vector<SimObject> simObjects;
	simObjects.reserve(numObjects);
	double d = spaceWidth / (double) numObjects;
	for (int i = 0; i < numObjects; i++)
	{
		double x = (-1 * spaceWidth / 2.0 + i * d) * 0.5;
		double y = -1 * x * 0.5;
		double z = -1 * i * d * 0.5;
		double location[3] =
		{ x, y, z };
		double velocity[3] =
		{ 1, 1, 1 };
		SimObject obj(1.0, location, velocity);
		simObjects.push_back(obj);
	}
	return simObjects;
}

struct lessThanPair
{
	inline bool operator()(const pair<double, unsigned long>& l, const pair<double, unsigned long>& r)
	{
		return (l.first < r.first);
	}
};

Cell* CreateSpaceGrid(vector<SimObject>& simObjects, int spaceWidth)
{
	double origin[3] =
	{ 0.0, 0.0, 0.0 };
	vector<pair<double, unsigned long> > sortX, sortY, sortZ;
	unsigned long length = simObjects.size();
	sortX.reserve(length);
	sortY.reserve(length);
	sortZ.reserve(length);
	for (unsigned long i = 0; i < simObjects.size(); i++)
	{
		SimObject obj = simObjects.at(i);
		sortX.push_back(make_pair(obj.getX(), i));
		sortY.push_back(make_pair(obj.getY(), i));
		sortZ.push_back(make_pair(obj.getZ(), i));
	}
	sort(sortX.begin(), sortX.end(), lessThanPair());
	sort(sortY.begin(), sortY.end(), lessThanPair());
	sort(sortZ.begin(), sortZ.end(), lessThanPair());
	for (unsigned long i = 0; i < simObjects.size(); i++)
	{
		printf("%6.3f\n", sortY.at(i).first);
	}
	Cell* spaceGridRoot = new Cell(origin, spaceWidth, sortX, sortY, sortZ, simObjects);
	return spaceGridRoot;
}

