// block.h

#ifndef BLOCK_H
#define BLOCK_H

#include <rt2d/entity.h>
#include <rt2d/color.h>
#include <rt2d/scene.h>
#include <rt2d/canvas.h>
#include "cell.h"

class Block: public Entity
{
public:
	Block();
	virtual ~Block();

	void spawnBlock();
private:
	std::vector<Cell*> grid;
	virtual void update(float deltaTime);
};

#endif /* BLOCK_H */
