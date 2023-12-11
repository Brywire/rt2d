#ifndef BLOCKDOKU_H
#define BLOCKDOKU_H

#include <rt2d/scene.h>
#include <rt2d/canvas.h>
#include "cell.h"
#include "block.h"

class Blockdoku : public Scene
{
    public:
        Blockdoku();
        virtual ~Blockdoku();

        virtual void update(float deltaTime);

        std::vector<Cell*> grid;
};

#endif