
#ifndef SIMOBJECTHEADERDEF
#define SIMOBJECTHEADERDEF

#include "Cell.hpp"
class Cell;

class SimObject
{
private:
	double mMass;
	double* mLocation;
	double* mVelocity;
public:
	SimObject(double mass, double location[3], double velocity[3]);
	void move(Cell& spaceGridRoot);
};

#endif
