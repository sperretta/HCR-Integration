#ifndef SPEECHSYNTHESIS_HPP
#define SPEECHSYNTHESIS_HPP

#include <pyWrap.hpp>
#include <string>

#define Vocalise 1
#define CheckHelpNeeded 2
#define Greeting 3
#define CheckUnderstanding 4
#define MovePieces 5
#define Introduction 6
#define AskToPlay 7
#define AskIfNeedTeaching 8
#define YourTurn 9
#define MyTurn 10
#define IllegalMove 11
#define YouWin 12
#define IWin 13
#define GameNameIs 14
#define GameAimIs 15
#define HowCapturePieces 16
#define HowMove 17
#define YouCheat 18
#define RemovePieces 19
#define HaveYouFinished 20
#define KeepMovingSame 21
#define NotYourPiece 22
#define CantMoveSameDirection 23
#define InvalidCapture 24
#define CantGoBackToSameSpot 25
#define MustCapture 26
#define TutorialAgain 27
#define HelloBasic 28
#define AreYouSureGameRestart 29
#define PassTurnYN 30

class SpeechSynthesis :
    public pyWrap
{
    public:
        SpeechSynthesis() : pyWrap( "SpeechSynthesis", "speakWords", 2 ) { }
        ~SpeechSynthesis() = default;
	void operator()( std::string IP, int token)
        {
            PyObject *pValue1;
	    PyObject *pValue2;

            pValue1 = PyString_FromString(IP.c_str());
	    pValue2 = PyLong_FromLong(token);

            PyTuple_SetItem( m_pArgs, 0, pValue1 );
	    PyTuple_SetItem( m_pArgs, 1, pValue2 );

            PyObject_CallObject( m_pFunc, m_pArgs );
        }
};

#endif
