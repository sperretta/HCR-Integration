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
// Call the flash pieces at the correct time? May already be ok (cases 10 and 12)
// Put IP in one place, put distance, timeout, etc. in one place

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

    // Initialise head movement
    m_moveHead = std::make_shared<MoveHead>();
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
	    {
		std::string response("");

	    	(*m_synthesis)("192.168.0.100", Greeting);
		/*
		do {
			(*m_moveHead)("192.168.0.100", 20);
		    response = (*m_speechRecog)(15, 20);
		    std::cout<<response<<std::endl; //JR EDIT
		    if( response == "Nothing" || response == "Command Not Recognised" ) {(*m_moveHead)("192.168.0.100", 20); (*m_synthesis)("192.168.0.100", DidntUnderstand);}
		} while(response != "hello robot");
		*/

		std::cin >> response;
		std::cout << "\"" << response << "\"" << std::endl;

		if( response == "hello" )
		{
			(*m_moveHead)("192.168.0.100", 20);
	    		(*m_synthesis)("192.168.0.100", HelloBasic);
			transitionState( HighState::Info );
		}
	    }
            break;

        case HighState::Info: // BLOCKING
            // Explain information in transition, waiting for response
            // Transition to Tutorial or CheckHelp
	    {
		std::string response("");

		/*
		do {
		    response = (*m_speechRecog)(10, 20);
		    std::cout<<response<<std::endl; //JR EDIT
		    if( response == "Nothing" || response == "Command Not Recognised" ) {(*m_moveHead)("192.168.0.100", 20); (*m_synthesis)("192.168.0.100", DidntUnderstand);}
		} while(response != "yes" && response != "no");
		*/

		std::cin >> response;

		if( response == "yes" )
		{
			transitionState( HighState::Tutorial );
		}
		else // if( response == "no" )
		{
			transitionState( HighState::AskPlay );
		}
	    }
            break;

        case HighState::AskPlay: // BLOCKING
	    // Ask if they want to play a game
	    {
		std::string response("");

		/*
		do {
		    response = (*m_speechRecog)(10, 20);
		    std::cout<<response<<std::endl; //JR EDIT
		    if( response == "Nothing" || response == "Command Not Recognised" ) {(*m_moveHead)("192.168.0.100", 20); (*m_synthesis)("192.168.0.100", DidntUnderstand);}
		} while(response != "yes" && response != "no");
		*/
		std::cin >> response;

		if( response == "yes" )
		{
			transitionState( HighState::Play );
		}
		else // if( response == "no" )
		{
			transitionState( HighState::Wait );
		}
	    }
            break;
        case HighState::Tutorial: // BLOCKING
	    //(*m_synthesis)("192.168.0.100", Tutorial); //Needs to be changed to tutorial
	    {
		std::string response("");

		// Do you want to hear the tutorial again?
		/*
		do {
		    response = (*m_speechRecog)(10, 20);
		    std::cout<<response<<std::endl; //JR EDIT
		    if( response == "Nothing" || response == "Command Not Recognised" ) {(*m_moveHead)("192.168.0.100", 20); (*m_synthesis)("192.168.0.100", DidntUnderstand);}
		} while(response != "yes" && response != "no");
		*/
		std::cin >> response;

		if( response == "yes" )
		{
			transitionState( HighState::Tutorial );
		}
		else // if( response == "no" )
		{
			// TODO: Say something 
			transitionState( HighState::AskPlay );
		}
	    }
            break;

        case HighState::Play: // BLOCKING
            while(1)
            {
//reRead:
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
                        // TODO: Repeat only so often
			//auto timeNow = std::chrono::high_resolution_clock::now();
			    {
			(*m_moveHead)("192.168.0.100", 20);
	    		(*m_synthesis)("192.168.0.100", MyTurn);
                        std::cout << "Move the AI piece!" << std::endl;
			if( (int)gameInfo.displayMove.x >= 0 && (int)gameInfo.displayMove.x <= 2 ) // 0-2
			{
			(*m_moveHead)("192.168.0.100", 20);
	    			(*m_gesturing)("192.168.0.100", 1);
			    (*m_synthesis)("192.168.0.100", MovePieces);
			}
			else if( (int)gameInfo.displayMove.x >= 3 && (int)gameInfo.displayMove.x <= 5 ) // 3-5
			{
			(*m_moveHead)("192.168.0.100", 20);
	    			(*m_gesturing)("192.168.0.100", 2);
			    (*m_synthesis)("192.168.0.100", MovePieces);
			}
			if( (int)gameInfo.displayMove.x >= 6 && (int)gameInfo.displayMove.x <= 8 ) // 6-8
			{
			(*m_moveHead)("192.168.0.100", 20);
	    			(*m_gesturing)("192.168.0.100", 0);
				(*m_synthesis)("192.168.0.100", MovePieces);
			}
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
			(*m_moveHead)("192.168.0.100", 20);
	    		(*m_synthesis)("192.168.0.100", YourTurn); // Only accept pass, prompt after x seconds like AI
			(*m_synthesis)("192.168.0.100", HaveYouFinished);

			std::string response("");

			/*
			do {
			    response = (*m_speechRecog)(20, 20);
			    std::cout<<response<<std::endl; //JR EDIT
			if(response == "Nothing" || response == "Timeout!") {goto reRead;}
		    if( response == "Command Not Recognised"  ) {(*m_moveHead)("192.168.0.100", 20); (*m_synthesis)("192.168.0.100", DidntUnderstand);}
			} while(response != "yes" && response != "no" && response != "pass" && response != "restart"); // ADd confirmation for restart
			*/
		std::cin >> response;

			// Change this!
			if( response == "yes" || response == "pass" )
			{
			    m_gameInterface->pass_turn();
			}
			else if( response == "no" )
			{
			    continue;
			}
			else if( response == "restart" )
			{
			(*m_moveHead)("192.168.0.100", 20);
				(*m_synthesis)("192.168.0.100", AreYouSureGameRestart);
				/*
				do {
				    response = (*m_speechRecog)(10, 20);
				    std::cout<<response<<std::endl; //JR EDIT
		    if( response == "Nothing" || response == "Command Not Recognised" ) {(*m_moveHead)("192.168.0.100", 20); (*m_synthesis)("192.168.0.100", DidntUnderstand);}
				} while(response != "yes" && response != "no"); // ADd confirmation for restart
				*/
				if( response == "yes" )
				{
					transitionState(HighState::Play);
				}
				else
				{
					continue;
				}
			}
                    }
                    else if( gameInfo.displayMove.mov_dir == no_dir )
                    {
                        m_boardGraphics.clearStates();
	    		(*m_gesturing)("192.168.0.100", 3);
                    }
		    // TODO: Show board corections if starts invalid
		    // TODO: Board correction: flash while camera not being used for reading. (targetBoard)
		    // TODO: DO this for state 10 and 12
		    if(gameInfo.captures.size() != 0)
		    {
				(*m_synthesis)("192.168.0.100", RemovePieces);
			}
			for( auto& piece : gameInfo.captures )
			{
				unsigned x = piece % 9;
				unsigned y = piece / 9;
				m_boardGraphics.setPosState( x, y, PositionState::FlashGreen, Arrow::None );
			}
		    //std::this_thread::sleep_for(2s);
		    if( gameInfo.moveStatus == 14)
		    {
			    // TODO: Add counter
			    std::cout << "Invalid move" << std::endl;
			(*m_synthesis)("192.168.0.100", IllegalMove);
		    std::this_thread::sleep_for(1s);
		    }
                }
                else
                {
		    if(m_gameInterface->get_current_player() == p1)
		    {
			(*m_moveHead)("192.168.0.100", 20);
			    (*m_synthesis)("192.168.0.100", YouWin);
		    }
		    else
		    {
			(*m_moveHead)("192.168.0.100", 20);
	    		(*m_synthesis)("192.168.0.100", IWin);
		    }
		    m_gameInterface->save_log_to_file();
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
	    		(*m_gesturing)("192.168.0.100", 3);
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
			(*m_moveHead)("192.168.0.100", 20);
	    (*m_synthesis)("192.168.0.100", AskIfNeedTeaching);
            m_currentHighState = HighState::Info;
            break;

        case HighState::Tutorial:
            // TODO: Other states, etc.
			(*m_moveHead)("192.168.0.100", 20);
	    (*m_synthesis)("192.168.0.100", Introduction);
			//(*m_moveHead)("192.168.0.100", 20);
	    //(*m_synthesis)("192.168.0.100", HowCapturePieces);
		//	(*m_moveHead)("192.168.0.100", 20);
	   // (*m_synthesis)("192.168.0.100", HowMove);
			(*m_moveHead)("192.168.0.100", 20);
	    (*m_synthesis)("192.168.0.100", TutorialAgain);
	    // TODO: AskToPlay state so that it can be transitioned to from both Tutorial and Info (if the user says no)
            m_currentHighState = HighState::Tutorial;
            break;

	case HighState::AskPlay:
			(*m_moveHead)("192.168.0.100", 20);
	    (*m_synthesis)("192.168.0.100", AskToPlay);
            m_currentHighState = HighState::AskPlay;
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
