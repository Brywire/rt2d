// cell.h

#ifndef CELL_H
#define CELL_H

#include <rt2d/entity.h>
#include <rt2d/color.h>

class Cell: public Entity
{
public:
	Cell(const RGBAColor defaultColor);
	virtual ~Cell();

	const RGBAColor defaultColor;
	bool isBusy;  //Adding a bool to the cell
private:
	virtual void update(float deltaTime);
};

#endif /* CELL_H */
