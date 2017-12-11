#include <BoardGraphics.hpp>
#include <pyWrap.hpp>

#include <iostream>
#include <limits>

int main( int argc, char **argv )
{
	Py_Initialize();
    PySys_SetArgv( argc, argv );

    BoardGraphics bg;

    bg.start();

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    bg.end();

	Py_Finalize();
    return 0;
}
