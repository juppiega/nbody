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
	void CreateChildren(std::vector<SimObject>& simObjectsXsort,
			  	  	    std::vector<SimObject>& simObjectsYsort,
						std::vector<SimObject>& simObjectsZsort);
	void DeleteChildren(Cell* node);
	double ComputeMass(std::vector<SimObject>& objectsInCell) const;
	bool IsExternal(std::vector<SimObject>& objectsInCell) const;

	void FindObjInCorrectInterval(unsigned long& minInd,
			unsigned long& maxInd, double (SimObject::*dimensionFunction)(void),
			std::vector<SimObject>& simObjSorted) const;
	std::vector<SimObject> FindObjThisCell(std::vector<SimObject>& simObjectsXsort,
											std::vector<SimObject>& simObjectsYsort,
											std::vector<SimObject>& simObjectsZsort) const;
public:
	double GetMass() const;
	double getWidth() const;
	double IsExternal() const;
	double getX() const;
	double getY() const;
	double getZ() const;
	Cell(double comLocation[3], double cellWidth, std::vector<SimObject>& simObjectsXsort,
		 std::vector<SimObject>& simObjectsYsort, std::vector<SimObject>& simObjectsZsort);
	~Cell();
};

#endif
