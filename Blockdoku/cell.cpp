// cell.cpp

#include "cell.h"

Cell::Cell(const RGBAColor defaultColor)
	: Entity(),
	 isBusy(false), defaultColor{defaultColor}  // Initialize isBusy to false
{
	this->addSprite("assets/blockSprite.tga");
	this->sprite()->color = defaultColor;
}

Cell::~Cell()
{

}

void Cell::update(float deltaTime)
{

}
