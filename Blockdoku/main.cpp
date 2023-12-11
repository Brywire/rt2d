#include <rt2d/core.h>
#include "blockdoku.h"


int main(void)
{
    Core core;

    Blockdoku* blockdoku = new Blockdoku();
    while(blockdoku->isRunning()) {
        core.run(blockdoku);
        core.showFrameRate(5);
    }
    delete blockdoku;
    return 0;
}