#ifndef BLOCKDOKU_H
#define BLOCKDOKU_H

#include <rt2d/scene.h>
#include <rt2d/canvas.h>
#include "cell.h"
#include "block.h"
#include <rt2d/timer.h>

class Blockdoku : public Scene
{
    public:
        Blockdoku();
        virtual ~Blockdoku();

        virtual void update(float deltaTime);
        void checkVerticalLines();
        void checkHorizontalLines();

        std::vector<Cell*> grid;
    private:
    double solveDelay = 1.0;
    Timer* timer;
};

#endif