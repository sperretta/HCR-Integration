#include <Interfacing.hpp>
#include <BoardGraphics.hpp>
#include <pyWrap.hpp>

#include <GameEngine/game_interface.hpp>

#include <ReadBoard.hpp>
#include <Interfacing.hpp>
#include <SpeechRecognition.hpp>

#include <limits>

// Final todos:
// Make the ai move only ask for the pieces to be moved once
// Call the flash pieces at the correct time? May already be ok
// Add in speech things
// Move head randomly when starting to speak (moveHeadRandom)

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

    // Initialise speech synthesis
    m_synthesis = std::make_shared<SpeechSynthesis>();
	transitionState( initialState );
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
        case HighState::Wait: // BLOCKING
		// TODO: Wait for "hello robot"
	    (*m_synthesis)("192.168.0.100", Greeting);
	    {
		std::string response("");

		do {
		    response = (*m_speechRecog)(10, 20); // TODO: Increase timeout based on testing
		    std::cout<<response<<std::endl; //JR EDIT
		} while(response != "what is the game called" && response != "hello robot");
		// TODO: Say hi back

		//if( response == "yes" )
		{
	    		//(*m_synthesis)("192.168.0.100", Introduction);
			transitionState( HighState::Info );
		}
	    }
            break;

        case HighState::Info: // BLOCKING
            // Explain information in transition, waiting for response
            // Transition to Tutorial or CheckHelp
	    {
		std::string response("");

		do {
		    response = (*m_speechRecog)(10, 20);
		    std::cout<<response<<std::endl; //JR EDIT
		} while(response != "yes" && response != "no");

		if( response == "yes" )
		{
			transitionState( HighState::Tutorial );
		}
		else // if( response == "no" )
		{
			// TODO: Implement
			transitionState( HighState::Play );
		}
	    }
            break;

        case HighState::Tutorial: // BLOCKING
            // TODO: Other states, etc.
	    //(*m_synthesis)("192.168.0.100", Tutorial); //Needs to be changed to tutorial
	    {
		std::string response("");

		do {
		    response = (*m_speechRecog)(10, 20);
		    std::cout<<response<<std::endl; //JR EDIT
		} while(response != "yes" && response != "no");

		if( response == "yes" )
		{
			transitionState( HighState::Play );
		}
		else // if( response == "no" )
		{
			// TODO: Say something 
			transitionState( HighState::Wait );
		}
	    }
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

        case HighState::Play: // BLOCKING
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
                    if( m_gameInterface->get_current_player() == p2 && gameInfo.displayMove.mov_dir != no_dir )
                    {
                        // TODO: Do this once and wait!!
	    		(*m_synthesis)("192.168.0.100", MyTurn);
                        std::cout << "Move the AI piece!" << std::endl;
			if( (int)gameInfo.displayMove.x >= 0 && (int)gameInfo.displayMove.x <= 2 ) // 0-2
			{
			    (*m_synthesis)("192.168.0.100", MovePieces);
	    			(*m_gesturing)("192.168.0.100", 1);
			}
			else if( (int)gameInfo.displayMove.x >= 3 && (int)gameInfo.displayMove.x <= 5 ) // 3-5
			{
			    (*m_synthesis)("192.168.0.100", MovePieces);
	    			(*m_gesturing)("192.168.0.100", 2);
			}
			if( (int)gameInfo.displayMove.x >= 6 && (int)gameInfo.displayMove.x <= 8 ) // 6-8
			{
				(*m_synthesis)("192.168.0.100", MovePieces);
	    			(*m_gesturing)("192.168.0.100", 0);
			}
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
	    		(*m_synthesis)("192.168.0.100", YourTurn);
                        std::cout << "Would you like to pass your turn?" << std::endl;

			std::string response("");

			do {
			    response = (*m_speechRecog)(10, 20);
			    std::cout<<response<<std::endl; //JR EDIT
			} while(response != "yes" && response != "no" && response != "restart");

			// Change this!
			if( response == "yes" )
			{
			    m_gameInterface->pass_turn();
			}
			else if( response == "no" )
			{
			    continue;
			}
			else if( response == "restart" )
			{
				transitionState(HighState::Play);
			}
                    }
                    else if( gameInfo.displayMove.mov_dir == no_dir )
                    {
                        m_boardGraphics.clearStates();
	    		(*m_gesturing)("192.168.0.100", 3);
                    }
		    // TODO: Put this in the right place
		    // TODO: Show board corections if starts invalid
		    // TODO: Ask to remove pieces as well as move
			for( auto& piece : gameInfo.captures )
			{
				unsigned x = piece % 9;
				unsigned y = piece / 9;
				m_boardGraphics.setPosState( x, y, PositionState::FlashGreen, Arrow::None );
			}
                    // TODO: Handle other input? Cancelling game etc?
                }
                else
                {
		    if(m_gameInterface->get_current_player() == p2)
		    {
			    (*m_synthesis)("192.168.0.100", YouWin);
		    }
		    else
		    {
	    		(*m_synthesis)("192.168.0.100", IWin);
		    }
                    //transitionState( HighState::End );
                    transitionState( HighState::Wait );
                    break;
                }
            }
            break;

        case HighState::End: // BLOCKING
	    // TODO: Wait for goodbye etc?
            break;
    }
}

void Interfacing::transitionState( HighState nextState )
{
    switch( m_currentHighState )
    {
        case HighState::Wait: // NON-BLOCKING
		break;

        case HighState::Play: // BLOCKING
		m_gameInterface.reset();
            m_boardGraphics.setActive( false );
            break;
        default:
            break;
    }

    switch( nextState )
    {
        case HighState::Wait:
            m_currentHighState = HighState::Wait;
            break;

        case HighState::Info:
            // TODO: Explain the information to the user
            // TODO: Setup speech recognition
	    (*m_synthesis)("192.168.0.100", AskIfNeedTeaching);
            m_currentHighState = HighState::Info;
            break;

        case HighState::Tutorial:
            // TODO: Other states, etc.
	    (*m_synthesis)("192.168.0.100", HowCapturePieces);
	    (*m_synthesis)("192.168.0.100", HowMove);
	    (*m_synthesis)("192.168.0.100", AskToPlay);
	    // TODO: AskToPlay state so that it can be transitioned to from both Tutorial and Info (if the user says no)
            m_currentHighState = HighState::Tutorial;
            break;

        case HighState::Play: // BLOCKING
            m_gameInterface = std::make_shared<GameInterface>(p2, DIFFICULTY);
            m_gameInterface->enable_debug();
            m_boardGraphics.setActive( true );
            m_currentHighState = HighState::Play;
            std::this_thread::sleep_for(1s);
            break;

        case HighState::End: // BLOCKING
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
