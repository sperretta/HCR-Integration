import sys
from naoqi import ALProxy

import random, time

Introduction = [[[   " This game is called Fanorona, it is for two players",
                    " Fanorona is a two player game",
                    " This game involves two players, it is called Fanorona"
                    ],
                
                [   " and there are two sets of coloured chips, one for each player",
                    " each player has a set of chips in one colour",
                    " we each get a number of chips of the same colour"
                    ]],
                [[
                    " The game is played on a 9 by 5 grid",
                    " The game board is 9 pieces by 5",
                    " The game board is 9 by 5 pieces"
                    ],
                [
                    " the aim is to capture all enemy pieces",
                    " your aim is to remove all enemy pieces",
                    " and you want to have no enemy pieces remaining"
                    ]],
                [[
                    " Pieces are taken by moving away or towards enemy pieces along one of the lines on the board",
                    " To take a piece, move away or towards an opponent's piece along a line on the board",
                    " Moving along the lines of the board, towards or away from an  opponent's piece will take it"
                   ]],
                [[
                    " all pieces in the chosen direction on the line of movement are captured",
                    " in the chosen direction all your oponnent's pieces get removed from the board"
                    ]],
                [[
                    " If you capture a piece then you can move again",
                    " You can move again, if you capture a piece",
                    " Capturing a piece means you can move again"
                    ],
                [
                    " and you can move up to one space in each direction in one turn, if you capture at least one piece per move",
                    " in one turn, you can move up to one space in each direction, provided you capture a piece per move",
                    " provided you capture a piece in each move, you can move up to one space in each direction in a turn"
                    ]],
                [[
                    " You must move at least once a turn",
                    " Each turn you must move at least once",
                    " In a turn you have to move at least once"
                    ],
                [
                    " and when moving, you must capture if its possible",
                    " if its possible to capture and you choose to move, you must move to capture",
                    " capturing moves always take priority over non capturing moves"
                    ]]]

CheckUnderstanding = [[[" Does that make sense",
                " Do you understand this",
                " Would you like me to repeat that"]]]

Vocalise = [[[" Umm",
                " Err",
                " Uhh",
                " Hmm"]]]

CheckHelpNeeded = [[[
                " Hmm, ",
                ]],
            [[
                " Would you like ",
                " Do you want ",
                " Are you in need of ",
                ],
            [
                " some help",
                " a bit of help",
                " some assistance",
                " a gameplay tip",
                " some advice",
                ]]]
            
Greeting = [[[  " Hello",
                " Greetings",
                " Hi"
                ]],
            [[
                " welcome to this learning experience",
                " and welcome"
                ]]]
            
MovePieces = [[[" Could you move that piece?",
                " Would you move that piece?",
                " Please move my piece from there to there",
                " Please move my piece darling human",
                " please could you move that piece",
                " please would you move that piece, it is too far for me to reach!",
                " would you move that piece, I can't reach",
                " Please move my piece across, I cant reach it!"]]]

AskToPlay = [[[" Would you like to play a game?",
                    " Do you want to play a game?",
                    " Would one kindly wish to partake in a game?"
                ]]]
                
RobotPlayInfo = [[[" I would like to use the orange pieces. Orange is the best colour as you can see from me"]]]

AskIfNeedTeaching = [[[" Do you need me to",
                    " Would you like me to",
                    " Should I"
                    ],
                [
                    " teach you",
                    " show you how",
                    " help you learn"
                    ],
                [
                " to play?"]]]
                
YourTurn = [[[" It's your turn to move.",
                    " Your turn.",
                    " Your go.",
                    " You can move now"]]]

MyTurn = [[[" My turn",
                    " Sit back and watch the master play",
                    " My turn to move",
                    " My go"]]]

IllegalMove = [[[" You can't make that move",
                    " Nice try, but that isn't allowed",
                    " That's an illegal move",
                    " You can't move there"]]]

YouWin = [[[" Congratulations",
                    " Well done",
                    " Hooray"
                ]],
                [[
                    " the student has become the master,",

                    ]],
                [[
                    " you win!",
                    " you've won!",
                    " you beat me."
                    ]],
                [[
                    " I will have my revenge."]]]

IWin = [[[" I win,"]],
        
                [[
                    " better luck next time",
                    " oh well, perhaps next time",
                    " sorry about that old chum",
                    ]]]

GameNameIs = [[[" This game is called Fanorama",
                    " Fanoarama is a two player game"]]]

GameAimIs = [[[" The aim of the game is to capture all enemy pieces",
                    " Your aim is to capture all the opponent's pieces",
                    " You want to have no enemy pieces remaining"]]]

HowCapturePieces = [[[" Pieces are taken by moving away or towards enemy pieces along one of the lines on the board",
                    " To take a piece, move away or towards an opponent's piece along a line on the board",
                    " Moving along the lines of the board, towards or away from an  opponent's piece will take it"
                    ]],
                    [[
                    " all pieces in the chosen direction on the line of movement are captured",
                    " in the chosen direction all your oponnent's pieces get removed from the board"]]]

HowMove = [[[" If you capture a piece then you can move again",
                    " You can move again, if you capture a piece",
                    " Capturing a piece means you can move again",
                    ],

                [
                    " and you can move up to one space in each direction in one turn, if you capture at least one piece per move",
                    " in one turn you can move up to one space in each direction, provided you capture a piece per move",
                    " provided you capture a piece in each move, you can move up to one space in each direction in a turn"
                    ]],
                
                [[
                    " You must move at least once a turn",
                    " Each turn you must move at least once",
                    " In a turn you have to move at least once"
                    ],
                [
                    " and when moving you must capture if its possible",
                    " if its possible to capture and you choose to move, you must move to capture"
                    " capturing moves always take priority"]]]
                
YouCheat = [[[" You have clearly cheated",
                " No cheating please",
                " I can see the pieces on the board aren't in the right place",
                " The pieces on the board are not in the correct place"
                ]],
            [[
                " please move the pieces back.",
                " return them to their original positions"]]]
            
RemovePieces = [[[" Please remove these pieces", " Please remove the flashing pieces", " Please be a darling and remove these pieces"]]]

HaveYouFinished = [[[
                "", "", "", "", "Faster faster!", "mere human"],
                ["Have you finished your turn", "Is it my turn yet", "Chop chop, have you finished your turn"]]]

KeepMovingSame = [[["You can only move the same piece!"]]]


NotYourPiece = [[["That's not your piece"]]]

CantMoveSameDirection = [[["You cant move in the same direction twice"]]]

InvalidCapture = [[["That's an invalid capture"]]]

CantGoBackToSameSpot = [[["You cant move to a location you have already been in this turn"]]]

MustCapture = [[["You must capture a piece"]]]

TutorialAgain = [[["Would you like to hear my tutorial again", "Should I repeat that"]]]

HelloBasic = [[["Hello there", "Hello human", "Hello mere human", "Hello", "Good day", "Hi", "Greetings"]]]

AreYouSure = [[["Are you sure you want to restart?", "Do you want to restart the game?"]]]

PassTurnYN = [[["Would you like to pass your turn"]]]

DidntUnderstand = [[["I'm sorry i didnt understand that", "Please say that again", "Pardon"]]]

IntroduceRobot = [[["Hi, I am a robot and I am here to teach you a very fun game"],[" Please don't ask me about anything else but the game, because this is all I know about!"]]]

def speakWords(robotip = "192.168.0.100", input_d = 6):
    
    IP = robotip
    PORT = 9559
    try:
        tts = ALProxy("ALTextToSpeech", IP, PORT)
    except Exception,e:
        print "Could not create proxy to ALTextToSpeech"
        print "Error was: ",e
        sys.exit(1)
        
    #Says a test std::string
    
    
    if input_d == 1:
        token = Vocalise
    elif input_d == 2:
        token = CheckHelpNeeded
    elif input_d == 3:
        token = Greeting
    elif input_d == 4:
        token = CheckUnderstanding
    elif input_d == 5:
        token = MovePieces
    elif input_d == 6:
        token = Introduction
    elif input_d == 7:
        token = AskToPlay
    elif input_d == 8:
        token = AskIfNeedTeaching
    elif input_d == 9:
        token = YourTurn
    elif input_d == 10:
        token = MyTurn
    elif input_d == 11:
        token = IllegalMove
    elif input_d == 12:
        token = YouWin
    elif input_d == 13:
        token = IWin
    elif input_d == 14:
        token = GameNameIs
    elif input_d == 15:
        token = GameAimIs
    elif input_d == 16:
        token = HowCapturePieces
    elif input_d == 17:
        token = HowMove
    elif input_d == 18:
        token = YouCheat
    elif input_d == 19:
        token = RemovePieces
    elif input_d == 20:
        token = HaveYouFinished
    elif input_d == 21:
        token = KeepMovingSame
    elif input_d == 22:
        token = NotYourPiece
    elif input_d == 23:
        token = CantMoveSameDirection
    elif input_d == 24:
        token = InvalidCapture
    elif input_d == 25:
        token = CantGoBackToSameSpot
    elif input_d == 26:
        token = MustCapture
    elif input_d == 27:
        token = TutorialAgain
    elif input_d == 28:
        token = HelloBasic
    elif input_d == 29:
        token = AreYouSureGameRestart
    elif input_d == 30:
        token = PassTurnYN
    elif input_d == 31:
        token = DidntUnderstand
    elif input_d == 32:
        token = RobotPlayInfo
    elif input_d == 33:
        token = IntroduceRobot
        

    else:
        token = ["Error Error, Invalid Command"]
    
    #print "Token: ", token
    for i in range(0, len(token)):
        command = ""
        for j in token[i]:
            command = command + j[random.randint(0, len(j)-1)]
        time.sleep(0.3)
        print "Command: ",command
        tts.say(command)
    
    

#speakWords("192.168.0.100", 13)
