from enum import Enum

class SpeechToken(Enum):
    Vocalise=1 #(hmm uhh etc.)
    CheckHelpNeeded=2 #Asks the user if they need help.
    Greeting=3 #Greets the user.
    #ExplainN #Explains a specified rule/concept/technique of the game.
    CheckUnderstanding=4 #Asks the user if they understand what has been explained.
    MovePieces=5 #Asks the user to move pieces on the game board.
