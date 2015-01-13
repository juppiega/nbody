#include "SimObject.hpp"
#include <vector>

SimObject::SimObject(double mass, double location[3], double velocity[3])
{
	mMass = mass;
	mLocation = location;
	mVelocity = velocity;
}
