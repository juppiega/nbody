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
	vector<SimObject> objectsInThisCell = FindObjThisCell(simObjectsXsort,
			simObjectsYsort, simObjectsZsort);
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
	unsigned long northmostObj, southmostObj;
	unsigned long uppermostObj, downmostObj;

	FindObjInCorrectInterval(westmostObj, eastmostObj, &SimObject::getX,
			simObjectsXsort);
	FindObjInCorrectInterval(southmostObj, northmostObj, &SimObject::getY,
			simObjectsYsort);
	FindObjInCorrectInterval(downmostObj, uppermostObj, &SimObject::getZ,
			simObjectsZsort);
}

void Cell::FindObjInCorrectInterval(unsigned long& minInd,
		unsigned long& maxInd, double (SimObject::*dimensionFunction)() const,
		vector<SimObject>& simObjSorted) const
{
	static int dim = 0; // x-dimension first.
	unsigned long count = simObjSorted.size();
	unsigned long ind;
	unsigned long indexChange, first = 0;
	double minDim = mComLocation[dim] - mCellWidth / 2.0;
	while (count > 0)
	{
		ind = first;
		indexChange = count / 2;
		ind += indexChange;
		if ((simObjSorted.at(ind).*dimensionFunction)() < minDim)
		{
			ind++;
			count -= indexChange + 1;
		}
		else
		{
			count = indexChange;
		}
	}
	minInd = ind;

	count = simObjSorted.size();
	ind = 0;
	double maxDim = mComLocation[dim] + mCellWidth / 2.0;
	while (count > 0)
	{
		ind = first;
		indexChange = count / 2;
		ind += indexChange;
		if ((simObjSorted.at(ind).*dimensionFunction)() >= maxDim)
		{
			ind++;
			count -= indexChange + 1;
		}
		else
		{
			count = indexChange;
		}
	}
	maxInd = ind;
	printf("%d\n", dim);
	dim++;
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
