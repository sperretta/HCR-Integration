from enum import Enum

class SpeechToken(Enum):
    Vocalise=1 #(hmm uhh etc.)
    CheckHelpNeeded=2 #Asks the user if they need help.
    Greeting=3 #Greets the user.
    #ExplainN #Explains a specified rule/concept/technique of the game.
    CheckUnderstanding=4 #Asks the user if they understand what has been explained.
    MovePieces=5 #Asks the user to move pieces on the game board.
    Introduction=6 #Explain the game
    AskToPlay=7 #Ask if user wants to play the game
    AskIfNeedTeaching=8 #Ask if the user needs teaching the game
    YourTurn=9 #Tell user that it is their turn
    MyTurn=10 #Tell user that it is robot's turn
    IllegalMove=11 #Tell user that they cannot move to that position
    YouWin=12 #Congratulate/Insult user for win
    IWin=13 #Mock user for losing, bring on robot uprising
    GameNameIs=14 #Tell user name of the game
    GameAimIs=15 #Tell user the aim of the game
    HowCapturePieces=16 #Tell user how to capture pieces
    HowMove=17 #Tell user how to move
    YouCheat=18 #Tell user they are cheating
