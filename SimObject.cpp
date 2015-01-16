#include "SimObject.hpp"
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

SimObject::SimObject(double mass, double location[3], double velocity[3])
{
	mMass = mass;
	memmove(mLocation, location, sizeof(mLocation));
	memmove(mVelocity, velocity, sizeof(mVelocity));
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

double SimObject::getMass() const
{
	return mMass;
}
