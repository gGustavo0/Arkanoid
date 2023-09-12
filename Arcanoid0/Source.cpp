#include "Arkanoid.h"

int main()
{
    Arkanoid &arkanoid = *new Arkanoid();
    arkanoid.start();
    delete(&arkanoid);
    return 0;
}