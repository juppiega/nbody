#include "Cell.hpp"
#include <vector>
#include <cstddef>

using namespace std;
Cell::Cell(double comLocation[3], double cellWidth, vector<SimObject>* simObjectsXsort,
		   vector<SimObject>* simObjectsYsort, vector<SimObject>* simObjectsZsort)
{
	mCellWidth = cellWidth;
	mComLocation = comLocation;
	for (int i = 0; i < 8; i++)
	{
		mChildren[i] = NULL;
	}

}

void Cell::CreateChildren(vector<SimObject>* simObjectsXsort,
						  vector<SimObject>* simObjectsYsort,
						  vector<SimObject>* simObjectsZsort)
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
		mChildren[i] = Cell(childComLocation, childCellWidth, simObjectsXsort, simObjectsYsort, simObjectsZsort);
	}
}
