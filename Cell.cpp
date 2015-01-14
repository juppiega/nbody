#include "Cell.hpp"
#include <stdio.h>
#include <vector>
#include <cstddef>

using namespace std;
Cell::Cell(double comLocation[3], double cellWidth,
		vector<SimObject>& simObjectsXsort, vector<SimObject>& simObjectsYsort,
		vector<SimObject>& simObjectsZsort)
{
	mCellWidth = cellWidth;
	mComLocation = comLocation;
	//printf("%6.3f %6.3f %6.3f\n", mComLocation[0], mComLocation[1], mComLocation[2]);

	mExternalNode = true;
	mChildren.reserve(8);
	for (int i = 0; i < 8; i++)
	{
		mChildren[i] = NULL;
	}
	if (!mExternalNode)
	{
		CreateChildren(simObjectsXsort, simObjectsYsort, simObjectsZsort);
	}
}

vector<SimObject> Cell::FindObjThisCell(vector<SimObject>& simObjectsXsort,
		vector<SimObject>& simObjectsYsort,
		vector<SimObject>& simObjectsZsort) const
{
	vector<SimObject> objectsInCell;
	unsigned long westmostObj, eastmostObj;
	unsigned long nortmostObj, southmostObj;
	unsigned long uppermostObj, downmostObj;

	FindObjInCorrectInterval(westmostObj, eastmostObj, &SimObject::getX, simObjectsXsort);
}

void Cell::FindObjInCorrectInterval(unsigned long& minInd,
		unsigned long& maxInd, double (SimObject::*dimensionFunction)(),
		vector<SimObject>& simObjSorted) const
{
	unsigned long ind = simObjSorted.size() / 2;
	unsigned long indexChange = simObjSorted.size() / 4;
	double minDim = mComLocation[0] - mCellWidth / 2.0;
	do
	{
		if ((simObjSorted.at(ind).*dimensionFunction)() < minDim)
		{
			ind += indexChange;
		}
		else
		{
			ind -= indexChange;
		}
		indexChange /= 2;
	} while (indexChange > 0);
	minInd = ind;

	ind = simObjSorted.size() / 2;
	indexChange = simObjSorted.size() / 4;
	double maxDim = mComLocation[0] + mCellWidth / 2.0;
	do
	{
		if ((simObjSorted.at(ind).*dimensionFunction)() > maxDim)
		{
			ind -= indexChange;
		}
		else
		{
			ind += indexChange;
		}
		indexChange /= 2;
	} while (indexChange > 0);
	maxInd = ind;
}

double Cell::getX() const
{
	return mComLocation[0];
}

double Cell::getY() const
{
	return mComLocation[1];
}

double Cell::getZ() const
{
	return mComLocation[2];
}

void Cell::CreateChildren(vector<SimObject>& simObjectsXsort,
		vector<SimObject>& simObjectsYsort, vector<SimObject>& simObjectsZsort)
{
	double childCellWidth = mCellWidth / 2.0;
	for (int i = 0; i < 8; i++)
	{
		double x, y, z;

		if (i == 1 || i == 2 || i == 5 || i == 6)
		{
			x = mComLocation[0] - childCellWidth / 2.0;
		}
		else
		{
			x = mComLocation[0] + childCellWidth / 2.0;
		}

		if (i == 2 || i == 3 || i == 6 || i == 7)
		{
			y = mComLocation[1] - childCellWidth / 2.0;
		}
		else
		{
			y = mComLocation[1] + childCellWidth / 2.0;
		}

		if (i >= 4)
		{
			z = mComLocation[2] - childCellWidth / 2.0;
		}
		else
		{
			z = mComLocation[2] + childCellWidth / 2.0;
		}

		double childComLocation[3] =
		{ x, y, z };
		mChildren[i] = new Cell(childComLocation, childCellWidth,
				simObjectsXsort, simObjectsYsort, simObjectsZsort);
	}
}

Cell::~Cell()
{
	DeleteChildren(this);
}

void Cell::DeleteChildren(Cell* node)
{
	if (node != NULL)
	{
		for (int i = 0; i < 8; i++)
		{
			DeleteChildren(mChildren[i]);
		}
		delete node;
	}
}
