#include "Cell.hpp"
#include <stdio.h>
#include <vector>
#include <cstddef>
#include <climits>

using namespace std;
Cell::Cell(double comLocation[3], double cellWidth,
		std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsYsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
		std::vector<SimObject>& simObjects)
{
	mCellWidth = cellWidth;
	mComLocation = comLocation;
	//printf("%6.3f %6.3f %6.3f\n", mComLocation[0], mComLocation[1], mComLocation[2]);
	vector<SimObject> objectsInThisCell = FindObjThisCell(simObjectsXsort,
			simObjectsYsort, simObjectsZsort, simObjects);
	mExternalNode = true;
	mChildren.reserve(8);
	for (int i = 0; i < 8; i++)
	{
		mChildren[i] = NULL;
	}
	if (!mExternalNode)
	{
		CreateChildren(simObjectsXsort, simObjectsYsort, simObjectsZsort,
				simObjects);
	}
}

vector<SimObject> Cell::FindObjThisCell(
		std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsYsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
		std::vector<SimObject>& simObjects) const
{
	// Taman funktion nopeus on kyseenalainen; vertaa brute-forceen.
	vector<SimObject> objectsInCell;
	unsigned long westmostObj, eastmostObj;
	unsigned long northmostObj, southmostObj;
	unsigned long uppermostObj, downmostObj;

	FindObjInCorrectInterval(westmostObj, eastmostObj, simObjectsXsort);
	FindObjInCorrectInterval(southmostObj, northmostObj, simObjectsYsort);
	FindObjInCorrectInterval(downmostObj, uppermostObj, simObjectsZsort);

}

vector<unsigned long> Cell::FindObjInCorrectInterval(vector<pair<double, unsigned long> >& simObjSorted) const
{
	static int dim = 0; // x-dimension first.
	unsigned long minInd, maxInd;
	unsigned long length = simObjSorted.size();
	double minDim = mComLocation[dim] - mCellWidth / 2.0;
	double maxDim = mComLocation[dim] + mCellWidth / 2.0;

	if (simObjSorted.at(0).first > maxDim
			|| simObjSorted.at(length - 1).first < minDim)
	{
		minInd = ULONG_MAX;
		maxInd = ULONG_MAX;
		return;
	}

	unsigned long ind = length / 2;
	unsigned long step = ind;
	if (simObjSorted.at(0).first >= minDim)
	{
		minInd = 0;
	}
	else
	{
		while (step > 1)
		{
			step = (step + 1) / 2;
			if (simObjSorted.at(ind).first < minDim)
			{
				ind += step;
				minInd = ind + 1;
			}
			else
			{
				ind -= step;
				minInd = ind;
			}
		}
	}

	ind = length / 2;
	step = ind;
	if (simObjSorted.at(length - 1).first < maxDim)
	{
		maxInd = length - 1;
	}
	else
	{
		while (step > 1)
		{
			step = (step + 1) / 2;
			if (simObjSorted.at(ind).first < maxDim)
			{
				ind += step;
				maxInd = ind;
			}
			else
			{
				ind -= step;
				maxInd = ind - 1;
			}
		}
	}

	vector<unsigned long> inRange;
	inRange.reserve(maxInd - minInd + 1);
	for (unsigned long i = minInd; i <= maxInd; i++)
	{
		inRange.at(i - minInd) = simObjSorted.at(i).second;
	}

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

void Cell::CreateChildren(
		std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsYsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
		std::vector<SimObject>& simObjects)
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
				simObjectsXsort, simObjectsYsort, simObjectsZsort, simObjects);
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
