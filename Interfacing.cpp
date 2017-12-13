#include <Interfacing.hpp>
#include <BoardGraphics.hpp>
#include <pyWrap.hpp>

#include <GameEngine/game_interface.hpp>

#include <ReadBoard.hpp>
#include <Interfacing.hpp>
#include <SpeechRecognition.hpp>

#include <limits>

// TODO: Move this elsewhere?
Arrow movDirToArrow( Direction dir )
{
    switch( dir )
    {
        case u:
            return Arrow::Up;
            break;
        case d:
            return Arrow::Down;
            break;
        case l:
            return Arrow::Left;
            break;
        case r:
            return Arrow::Right;
            break;
        case ul:
            return Arrow::UpLeft;
            break;
        case ur:
            return Arrow::UpRight;
            break;
        case dl:
            return Arrow::DownLeft;
            break;
        case dr:
            return Arrow::DownRight;
            break;
        default:
            return Arrow::None;
    }
}

Interfacing::Interfacing( int argc, char **argv, HighState initialState ) : m_currentHighState{ initialState }
{
    // Initialise python
	Py_Initialize();
    PySys_SetArgv( argc, argv );

    // Initialise readboard
    m_readBoard = std::make_shared<ReadBoard>();

    // Initialise board graphics
    m_boardGraphics.start();

    // Initialise speech recognition
    m_speechRecog = std::make_shared<SpeechRecog>();

    // Initialise gesturing
    m_gesturing = std::make_shared<Gesturing>();
}

Interfacing::~Interfacing()
{
    // Shut down board graphics
    m_boardGraphics.end();

    // Shut down python
	Py_Finalize();
}

void Interfacing::update()
{
    switch( m_currentHighState )
    {
        case HighState::Wait: // NON-BLOCKING
            // Wait for face to appear
            // Transition to Info
            //if( faceRecognition.checkForFace() )
            //{
                //transitionState( HighState::Info );
            //}
            break;

        case HighState::Info: // BLOCKING
            // Explain information in transition, waiting for response
            // Transition to Tutorial or CheckHelp
            //{
                //auto response = invalid;
                //while( response == invalid )
                //{
                    //response = speechRecognition.getResponse();
                    //switch( response )
                    //{
                        //case yes:
                            //// TODO: Change state to tutorial
                        //case no:
                            //// TODO: Change state to check help
                    //}
                //}
            //}
            break;

        case HighState::Tutorial: // BLOCKING
            // TODO: Other states, etc.
            break;

        case HighState::CheckHelp: // BLOCKING
            //{
                //auto response = invalid;
                //while( response == invalid )
                //{
                    //response = speechRecognition.getResponse();
                    //switch( response )
                    //{
                        //case yes:
                            //// TODO: Change state to play help
                        //case no:
                            //// TODO: Change state to play no help
                    //}
                //}
            //}
            break;

        case HighState::PlayHelp: // BLOCKING
            break;

        case HighState::PlayNoHelp: // BLOCKING
            while(1)
            {
                std::vector<Piece> gameBoard = ( *m_readBoard )( "/dev/video0" );
                if ( gameBoard.size() != 45 )
                {
                    continue;
                }

                m_gameInterface->print_board( gameBoard );

                GameInfo gameInfo;
                if(!m_gameInterface->finished())
                {
                    gameInfo = m_gameInterface->run_game(gameBoard);
                    std::cout << gameInfo.moveStatus << std::endl;
                    // TODO: Notify user to move pieces with graphics things (flash board)
                    // TODO: Tell user where to move pieces on AI turn
                    if( m_gameInterface->get_current_player() == p2 && gameInfo.displayMove.mov_dir != no_dir )
                    {
                        // TODO: Do this once and wait!!
                        std::cout << "Move the AI piece!" << std::endl;
                        m_boardGraphics.setPosState( gameInfo.displayMove.x, gameInfo.displayMove.y, PositionState::FlashGreen, movDirToArrow(gameInfo.displayMove.mov_dir) );
                        std::cout << "(" << gameInfo.displayMove.x << ", " << gameInfo.displayMove.y << ")";
                        switch( gameInfo.displayMove.mov_dir )
                        {
                            case u:
                                std::cout << " up." << std::endl;
                                break;
                            case d:
                                std::cout << " down." << std::endl;
                                break;
                            case l:
                                std::cout << " left." << std::endl;
                                break;
                            case r:
                                std::cout << " right." << std::endl;
                                break;
                            case ul:
                                std::cout << " up-left." << std::endl;
                                break;
                            case ur:
                                std::cout << " up-right." << std::endl;
                                break;
                            case dl:
                                std::cout << " down-left." << std::endl;
                                break;
                            case dr:
                                std::cout << " down-right." << std::endl;
                                break;
                            default:
                                break;
                        }
                    }
                    else if( m_gameInterface->get_current_player() == p1 && gameInfo.moveStatus == noMove) // If gameInfo is in a state where there are no more possible moves...
                    {
                        // TODO: Listen for user saying their turn is over
                        std::cout << "Would you like to pass your turn?" << std::endl;
                        //char c;
                        //std::cin >> c;
                        //if( c == 'y' )
                        //{
                        //    m_gameInterface->pass_turn();
                        //}
                        //else
                        //{
                        //    continue;
                        //}
			std::string response("");

			response = (*m_speechRecog)(10, 600);
			std::cout << response << std::endl;
                    }
                    else if( gameInfo.displayMove.mov_dir == no_dir )
                    {
                        m_boardGraphics.clearStates();
                    }
                    // TODO: Handle other input? Cancelling game etc?
                }
                else
                {
                    // TODO: Finish this, move into next state
                    // TODO: Robot says player has won
                    std::cerr<< "Player " << m_gameInterface->get_current_player() << " wins!" << std::endl;
                    transitionState( HighState::End );
                    break;
                }
            }
            break;

        case HighState::End: // NON-BLOCKING
            // TODO: Wait for face to no longer be in frame
            break;
    }
}

void Interfacing::transitionState( HighState nextState )
{
    // TODO: Also do things based on current state
    switch( m_currentHighState )
    {
        case HighState::PlayNoHelp: // BLOCKING
            m_boardGraphics.setActive( false );
            break;
        default:
            break;
    }

    switch( nextState )
    {
        case HighState::Wait:
            // TODO: Setup face recognition
            m_currentHighState = HighState::Wait;
            break;

        case HighState::Info:
            // TODO: Explain the information to the user
            // TODO: Setup speech recognition
            m_currentHighState = HighState::Info;
            break;

        case HighState::Tutorial:
            // TODO: Other states, etc.
            break;

        case HighState::PlayHelp: // BLOCKING
            m_boardGraphics.setActive( true );
            break;

        case HighState::PlayNoHelp: // BLOCKING
	    (*m_gesturing)("192.168.0.100", 1);
            m_gameInterface = std::make_shared<GameInterface>(p2, DIFFICULTY);
            m_gameInterface->enable_debug();
            m_boardGraphics.setActive( true );
            m_currentHighState = HighState::PlayNoHelp;
            std::this_thread::sleep_for(1s);
            break;

        default:
            return;
    }
}

bool Interfacing::shouldContinue()
{
    // TODO: End condition
    return true;
}
