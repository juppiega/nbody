#include "Cell.hpp"
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <climits>

using namespace std;
Cell::Cell(double comLocation[3], double cellWidth, std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsYsort, std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
		std::vector<SimObject>& simObjects)
{
	mCellWidth = cellWidth;
	mComLocation = comLocation;
	printf("%6.3f %6.3f %6.3f\n", mComLocation[0], mComLocation[1], mComLocation[2]);
	vector<unsigned long> objectsInThisCell = FindObjThisCell(simObjectsXsort, simObjectsYsort, simObjectsZsort);
	mExternalNode = IsExternal(objectsInThisCell);
	mTotalMass = ComputeMass(objectsInThisCell, simObjects);

	mChildren.reserve(8);
	for (int i = 0; i < 8; i++)
	{
		mChildren[i] = NULL;
	}
	if (!mExternalNode)
	{
		CreateChildren(simObjectsXsort, simObjectsYsort, simObjectsZsort, simObjects);
	}
}

vector<unsigned long> Cell::FindObjThisCell(std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsYsort, std::vector<std::pair<double, unsigned long> >& simObjectsZsort) const
{
	// Taman funktion nopeus on kyseenalainen; vertaa brute-forceen.
	// Ei myöskaan tarvitse etsia koko avaruuden kappaleiden joukosta;
	// ainoastaan parentin sisältä!
	vector<SimObject> objectsInCell;

	vector<unsigned long> objWithCorrectX = FindObjInCorrectInterval(simObjectsXsort, 0);
	vector<unsigned long> objWithCorrectY = FindObjInCorrectInterval(simObjectsYsort, 1);
	vector<unsigned long> objWithCorrectZ = FindObjInCorrectInterval(simObjectsZsort, 2);
	vector<unsigned long> intersectXY;
	vector<unsigned long> intersectXYZ;

	intersectXYZ.reserve(0);

	if (objWithCorrectX.size() == 0 || objWithCorrectY.size() == 0 || objWithCorrectZ.size() == 0)
	{
		return intersectXYZ;
	}

	intersectXY = Intersection(objWithCorrectX, objWithCorrectY);
	intersectXYZ = Intersection(intersectXY, objWithCorrectZ);

	for (unsigned long i = 0; i < intersectXYZ.size(); i++)
	{
		printf("%d\n", (int) intersectXYZ.at(i));
	}

	return intersectXYZ;
}

vector<unsigned long> Cell::Intersection(const vector<unsigned long>& vec1, const vector<unsigned long>& vec2) const
{
	vector<unsigned long> result;
	result.reserve(min(vec1.size(), vec2.size()));
	unsigned long first1 = 0, first2 = 0, last1 = vec1.size(), last2 = vec2.size();

	while (first1 < last1 && first2 < last2)
	{
		unsigned long val1 = vec1.at(first1);
		unsigned long val2 = vec2.at(first2);

		if (val1 == val2)
		{
			result.push_back(val1);
		}
		if (val1 < val2)
		{
			first1++;
		}
		else
		{
			first2++;
		}
	}

	vector<unsigned long> tmp(result);
	result.swap(tmp);
	return result;
}

vector<unsigned long> Cell::FindObjInCorrectInterval(vector<pair<double, unsigned long> >& simObjSorted, int dim) const
{
	unsigned long minInd, maxInd;
	unsigned long length = simObjSorted.size();
	double minDim = mComLocation[dim] - mCellWidth / 2.0;
	double maxDim = mComLocation[dim] + mCellWidth / 2.0;
	vector<unsigned long> inRange;
	inRange.reserve(0);

	if (simObjSorted.at(0).first > maxDim || simObjSorted.at(length - 1).first < minDim)
	{
		minInd = ULONG_MAX;
		maxInd = ULONG_MAX;
		return inRange;
	}

	unsigned long ind = (length - 1) / 2;
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
			if (ind > length - 1)
			{
				int a = 1;
			}
			if (simObjSorted.at(ind).first < minDim)
			{
				ind += step;
			}
			else
			{
				ind -= step;
			}
		}
		if (simObjSorted.at(ind).first < minDim)
		{
			minInd = ind + 1;
		}
		else
		{
			minInd = ind;
		}
	}

	ind = (length - 1) / 2;
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
			}
			else
			{
				ind -= step;
			}
		}
		if (simObjSorted.at(ind).first < maxDim)
		{
			maxInd = ind;
		}
		else
		{
			maxInd = ind - 1;
		}
	}

	inRange.reserve(maxInd - minInd + 1);
	for (unsigned long i = minInd; i <= maxInd; i++)
	{
		inRange.push_back(simObjSorted.at(i).second);
	}

	sort(inRange.begin(), inRange.end());
	return inRange;
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

inline bool Cell::IsExternal(vector<unsigned long>& objectsInCell) const
{
	return objectsInCell.size() <= 1;
}

double Cell::ComputeMass(vector<unsigned long>& objectsInCell, vector<SimObject>& simObjects) const
{
	// Olisiko rekursio nopeampi? Miten objectsInCell.size():n kutsuminen joka loopilla vaikuttaa?

	double mass = 0.0;
	for (unsigned long i = 0; i < objectsInCell.size(); i++)
	{
		mass += simObjects.at(objectsInCell.at(i)).getMass();
	}
	return mass;
}

void Cell::CreateChildren(std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
		std::vector<std::pair<double, unsigned long> >& simObjectsYsort, std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
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

		double childComLocation[3] = { x, y, z };
		mChildren[i] = new Cell(childComLocation, childCellWidth, simObjectsXsort, simObjectsYsort, simObjectsZsort, simObjects);
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
