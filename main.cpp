#include "SimObject.hpp"
#include "Cell.hpp"
#include <vector>

using namespace std;

vector<SimObject> CreateSimObjects();
Cell CreateSpaceGrid(vector<SimObject>& simObjects);

int main()
{
	vector<SimObject> simObjects = CreateSimObjects();
	Cell spaceGrid = CreateSpaceGrid(simObjects);
	return 0;
}

vector<SimObject> CreateSimObjects()
{
	int numObjects = 1;
	vector<SimObject> simObjects;
	simObjects.reserve(numObjects);
	double location[3] = {1,1,1};
	double velocity[3] = {1,1,1};
	simObjects[0] = SimObject(1, location, velocity);
	return simObjects;
}

Cell CreateSpaceGrid(vector<SimObject>& simObjects)
{
	double origin[3] = {0.0, 0.0, 0.0};
	double spaceWidth = 4;
	Cell spaceGridRoot(origin, spaceWidth, simObjects, simObjects, simObjects);
	return spaceGridRoot;
}
