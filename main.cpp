#include <BoardGraphics.hpp>

#include <iostream>
#include <limits>

int main()
{
    BoardGraphics bg;

    bg.start();

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    bg.end();

    return 0;
}
