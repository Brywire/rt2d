// cell.h

#ifndef CELL_H
#define CELL_H

#include <rt2d/entity.h>

class Cell: public Entity
{
public:
	Cell();
	virtual ~Cell();

	bool isBusy;  //Adding a bool to the cell
private:
	virtual void update(float deltaTime);
};

#endif /* CELL_H */
