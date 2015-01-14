#include "SimObject.hpp"
#include <vector>
#include <stdio.h>

SimObject::SimObject(double mass, double location[3], double velocity[3])
{
	mMass = mass;
	mLocation = location;
	printf("%6.3f %6.3f %6.3f\n", mLocation[0], mLocation[1], mLocation[2]);
	mVelocity = velocity;
}

double SimObject::getX() const
{
	return mLocation[0];
}

double SimObject::getY() const
{
	return mLocation[1];
}

double SimObject::getZ() const
{
	return mLocation[2];
}
