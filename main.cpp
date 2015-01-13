#include "Cell.hpp"
#include "SimObject.hpp"
#include <vector>

using namespace std;
int main()
{
	vector<SimObject> simObjects = createSimObjects();
	Cell spaceGridRoot = createSpaceGrid();
	return 0;
}

vector<SimObject> createSimObjects()
{
	int numObjects = 1;
	vector<SimObject> simObjects;
	simObjects.reserve(numObjects);
	int location[3] = {1,1,1};
	int velocity[3] = {1,1,1};
	simObjects[1] = SimObject(1, location, velocity);
	return simObjects;
}

Cell createSpaceGrid()
{

}
