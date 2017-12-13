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
    return 0;
}
