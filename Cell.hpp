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
	double ComputeMass(std::vector<unsigned long>& objectsInCell, std::vector<SimObject>& simObjects) const;
	bool IsExternal(std::vector<unsigned long>& objectsInCell) const;

	std::vector<unsigned long> FindObjInCorrectInterval(std::vector<std::pair<double, unsigned long> >& simObjSorted) const;
	std::vector<unsigned long> FindObjThisCell(
			std::vector<std::pair<double, unsigned long> >& simObjectsXsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsYsort,
			std::vector<std::pair<double, unsigned long> >& simObjectsZsort) const;
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
