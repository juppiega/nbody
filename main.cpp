#include "SimObject.hpp"
#include "Cell.hpp"
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

vector<SimObject> CreateSimObjects(int spaceWidth);
Cell* CreateSpaceGrid(vector<SimObject>& simObjects, int spaceWidth);
struct lessThanX;
struct lessThanY;
struct lessThanZ;

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
		double x = -1 * spaceWidth / 2.0 + i * d;
		double y = -1 * x;
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

struct lessThanX
{
	inline bool operator()(const SimObject& obj1, const SimObject& obj2)
	{
		return (obj1.getX() < obj2.getX());
	}
};

struct lessThanY
{
	inline bool operator()(const SimObject& obj1, const SimObject& obj2)
	{
		return (obj1.getY() < obj2.getY());
	}
};

struct lessThanZ
{
	inline bool operator()(const SimObject& obj1, const SimObject& obj2)
	{
		return (obj1.getZ() < obj2.getZ());
	}
};

Cell* CreateSpaceGrid(vector<SimObject>& simObjects, int spaceWidth)
{
	double origin[3] =
	{ 0.0, 0.0, 0.0 };
	vector<SimObject> simObjectsXsort = simObjects;
	vector<SimObject> simObjectsYsort = simObjects;
	vector<SimObject> simObjectsZsort = simObjects;

	sort(simObjectsXsort.begin(), simObjectsXsort.end(), lessThanX());
	sort(simObjectsYsort.begin(), simObjectsYsort.end(), lessThanY());
	sort(simObjectsZsort.begin(), simObjectsZsort.end(), lessThanZ());
	for (unsigned long i = 0; i < simObjects.size(); i++)
	{
		SimObject obj = simObjectsZsort.at(i);
		printf("%6.3f %6.3f %6.3f\n", obj.getX(), obj.getY(), obj.getZ());
	}
	Cell* spaceGridRoot = new Cell(origin, spaceWidth, simObjectsXsort,
			simObjectsYsort, simObjectsZsort);
	return spaceGridRoot;
}

