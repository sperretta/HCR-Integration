#include <Interfacing.hpp>

#include <iostream>
#include <limits>

int main( int argc, char **argv )
{
    Interfacing iface( argc, argv, HighState::Wait );

    iface.transitionState( HighState::PlayNoHelp );

    while( iface.shouldContinue() )
    {
        iface.update();
    }
    /*
	Py_Initialize();
    PySys_SetArgv( argc, argv );

    ReadBoard readBoard;

    GameInterface gameInterface(p2, 3);
    gameInterface.enable_debug();
    while(1)
    {
        std::vector<Piece> gameBoard = readBoard( "/dev/video0" );
        gameInterface.print_board( gameBoard );
        for( auto e : gameBoard )
        {
            std::cout << e << ",";
        }

        std::cout << std::endl;

        GameInfo gameInfo;
        if(!gameInterface.finished())
        {
            int inVal;

            std::cin >> inVal;

            if( inVal == 0 )
            {
                gameInterface.pass_turn();
            }
            else
            {
                gameInfo = gameInterface.run_game(gameBoard);
                std::cout << "MOVE TO MAKE: " << gameInfo.displayMove.x << std::endl;
                std::cout << "MOVE TO MAKE: " << gameInfo.displayMove.y << std::endl;
                std::cout << "MOVE TO MAKE: " << gameInfo.displayMove.mov_dir << std::endl;
                std::cout << "MOVE TO MAKE: " << gameInfo.displayMove.cap_dir << std::endl;
            }
        }
        else
        {
            std::cerr<< "Game Over!" << std::endl;
            std::cerr<< "Player " << gameInterface.get_current_player() << " wins!" << std::endl;
            break;
        }
    }

    BoardGraphics bg;
    bg.start();

    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

    bg.end();

	Py_Finalize();
    */
    return 0;
}
