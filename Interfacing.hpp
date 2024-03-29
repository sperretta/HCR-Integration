#ifndef INTERFACING_HPP
#define INTERFACING_HPP

#include <BoardGraphics.hpp>
#include <pyWrap.hpp>

#include <GameEngine/game_interface.hpp>

#include <ReadBoard.hpp>
#include <Interfacing.hpp>
#include <SpeechRecog.hpp>
#include <Gesturing.hpp>
#include <SpeechSynthesis.hpp>
#include <MoveHead.hpp>

#define DIFFICULTY 3

enum class HighState
{
    Wait,
    Info,
    Tutorial,
    AskPlay,
    Play,
    End,
};

class Interfacing
{
    public:
        Interfacing( int argc, char **argv, HighState initialState = HighState::Wait );
        ~Interfacing();

        void update();

        void transitionState( HighState nextState );
        bool shouldContinue();
    private:

        HighState m_currentHighState;
        BoardGraphics m_boardGraphics;
        //SpeechRecognition speechRecognition;
        //FaceRecognition faceRecognition;
        std::shared_ptr<GameInterface> m_gameInterface;
        std::shared_ptr<ReadBoard> m_readBoard;
	std::shared_ptr<SpeechRecog> m_speechRecog;
	std::shared_ptr<Gesturing> m_gesturing;
	std::shared_ptr<SpeechSynthesis> m_synthesis;
	std::shared_ptr<MoveHead> m_moveHead;
};

#endif // INTERFACING_HPP
