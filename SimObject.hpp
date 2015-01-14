
#ifndef SIMOBJECTHEADERDEF
#define SIMOBJECTHEADERDEF

class Cell;

#include "Cell.hpp"

class SimObject
{
private:
	double mMass;
	double mLocation[3];
	double mVelocity[3];
public:
	SimObject(double mass, double location[3], double velocity[3]);
	void move(Cell& spaceGridRoot);
	double getX() const;
	double getY() const;
	double getZ() const;
};

#endif
