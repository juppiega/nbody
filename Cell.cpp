#include "Cell.hpp"
#include <stdio.h>
#include <vector>
#include <cstddef>

using namespace std;
Cell::Cell(double comLocation[3], double cellWidth, vector<SimObject>& simObjectsXsort,
		   vector<SimObject>& simObjectsYsort, vector<SimObject>& simObjectsZsort)
{
	mCellWidth = cellWidth;
	mComLocation = comLocation;
	printf("%s %4.1f %4.1f %4.1f\n", "x y z: ", mComLocation[0], mComLocation[1], mComLocation[2]);
	mExternalNode = false;
	if(cellWidth < 1.0) mExternalNode = true;
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

void Cell::CreateChildren(vector<SimObject>& simObjectsXsort,
						  vector<SimObject>& simObjectsYsort,
						  vector<SimObject>& simObjectsZsort)
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

		double childComLocation[3] = {x, y, z};
		mChildren[i] = new Cell(childComLocation, childCellWidth, simObjectsXsort, simObjectsYsort, simObjectsZsort);
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
