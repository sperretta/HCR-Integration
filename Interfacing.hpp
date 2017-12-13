#ifndef INTERFACING_HPP
#define INTERFACING_HPP

#include <BoardGraphics.hpp>
#include <pyWrap.hpp>

#include <GameEngine/game_interface.hpp>

#include <ReadBoard.hpp>
#include <Interfacing.hpp>

#define DIFFICULTY 3

enum class HighState
{
    Wait,
    Info,
    Tutorial,
    CheckHelp,
    PlayHelp,
    PlayNoHelp,
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
};

#endif // INTERFACING_HPP