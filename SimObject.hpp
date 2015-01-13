
#ifndef SIMOBJECTHEADERDEF
#define SIMOBJECTHEADERDEF

class Cell;

#include "Cell.hpp"

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
