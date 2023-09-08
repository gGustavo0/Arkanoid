#include "Arkanoid.h"

int main()
{
    Arkanoid &arkanoid = *new Arkanoid();
    arkanoid.start();

    return 0;
}