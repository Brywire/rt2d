// cell.cpp

#include "cell.h"

Cell::Cell()
	: Entity(),
	 isBusy(false)  // Initialize isBusy to false
{
	this->addSprite("assets/blockSprite.tga");
	this->sprite()->color = WHITE;
}

Cell::~Cell()
{

}

void Cell::update(float deltaTime)
{

}
