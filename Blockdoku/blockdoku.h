#ifndef BLOCKDOKU_H
#define BLOCKDOKU_H

#include <rt2d/scene.h>
#include <rt2d/canvas.h>
#include <rt2d/text.h>
#include "cell.h"
#include "block.h"
#include <rt2d/timer.h>

class Blockdoku : public Scene
{
public:
    Blockdoku();
    virtual ~Blockdoku();

    virtual void update(float deltaTime);
    

    std::vector<Cell*> grid;
private:
    double solveDelay = 1.0;
    Timer* timer;
    bool isAnimPlaying{false};
    Text* text;

    std::vector<std::vector<size_t>> checkVerticalLines();
    std::vector<std::vector<size_t>> checkHorizontalLines();
    std::vector<std::vector<size_t>> checkThrees();
    void solveLines(std::vector<std::vector<size_t>> busyCells, const bool endTransition = false);
    void solveThrees(std::vector<std::vector<size_t>> busyCells, const bool endTransition = false);
};

#endif