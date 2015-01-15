#ifndef CELLHEADERDEF
#define CELLHEADERDEF

class SimObject;

#include <vector>
#include "SimObject.hpp"

class Cell
{
private:
	double mTotalMass, mCellWidth;
	double* mComLocation;
	bool mExternalNode;
	std::vector<Cell*> mChildren;
	void CreateChildren(
			std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsYsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
			std::vector<SimObject>& simObjects);
	void DeleteChildren(Cell* node);
	double ComputeMass(std::vector<SimObject>& objectsInCell) const;
	bool IsExternal(std::vector<SimObject>& objectsInCell) const;

	void FindObjInCorrectInterval(unsigned long& minInd, unsigned long& maxInd,
			std::vector<std::pair<double, unsigned long> >& simObjectsSort) const;
	std::vector<SimObject> FindObjThisCell(
			std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsYsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
			std::vector<SimObject>& simObjects) const;
public:
	double GetMass() const;
	double getWidth() const;
	double IsExternal() const;
	double getX() const;
	double getY() const;
	double getZ() const;
	Cell(double comLocation[3], double cellWidth,
			std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsYsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsZsort,
			std::vector<SimObject>& simObjects);
	~Cell();
};

#endif
