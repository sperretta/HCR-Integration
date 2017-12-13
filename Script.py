from SpeechTokens import SpeechToken

data = {
        SpeechToken.Vocalise    : [
            (
                "Umm",
                "Err",
                "Uhh",
                "Hmm",
                )
            ],
        SpeechToken.CheckHelpNeeded : [
            (
                "",
                "Hmm, ",
                ),
            (
                "Would you like",
                "Do you want",
                "Are you in need of",
                ),
            " ",
            (
                "some help",
                "a bit of help",
                "some assistance",
                "a gameplay tip",
                "some advice",
                ),
            "?"
            ],
        SpeechToken.Greeting : [
            (
                "Hello",
                "Greetings",
                "Hi"
                ),
            ", ",
            (
                "welcome to this learning experience",
                "and welcome"
                ),
            "."
            ],
        SpeechToken.CheckUnderstanding : [
            (
                "Does that make sense",
                "Do you understand this",
                "Would you like me to repeat that"
                ),
            "?"
            ],
        SpeechToken.MovePieces : [
            (
                "Could you move that piece?",
                "Would you move that piece?",
                "Please move my piece from there to there"
                )
            ],
        SpeechToken.Introduction : [
                (
                    "This game is called Fanorama, it is for two players",
                    "Fanorama is a two player game",
                    "This game involves two players, it is called Fanorama"
                    ),
                ", ",
                (
                    "there are two sets of coloured chips, one for each player",
                    "each player has a set of chips in one colour",
                    "we each get a number of chips of the same colour"
                    ),
                ". ",
                (
                    "The game is played on a 9 by 5 grid",
                    "The game board is 9 pieces by 5",
                    "The game board is 9 by 5 pieces",
                    ),
                ", ",
                (
                    "the aim is to capture all enemy pieces",
                    "your aim is to remove all enemy pieces",
                    "and you want to have no enemy pieces remaining"
                    ),
                ".",
                (
                    "Pieces are taken by moving away or towards enemy pieces along one of the lines on the board",
                    "To take a piece, move away or towards an opponent's piece along a line on the board",
                    "Moving along the lines of the board, towards or away from an  opponent's piece will take it"
                    ),
                ", ",
                (
                    "all pieces in the chosen direction on the line of movement are captured",
                    "in the chosen direction all your oponnent's pieces get removed from the board"
                    ),
                ". ",
                (
                    "If you capture a piece then you can move again",
                    "You can move again, if you capture a piece",
                    "Capturing a piece means you can move again",
                    ),
                ", ",
                (
                    "and you can move up to one space in each direction in one turn, if you capture at least one piece per move",
                    "in one turn you can move up to one space in each direction, provided you capture a piece per move",
                    "provided you capture a piece in each move, you can move up to one space in each direction in a turn"
                    ),
                ". ",
                (
                    "You must move at least once a turn",
                    "Each turn you must move at least once",
                    "In a turn you have to move at least once"
                    ),
                ", ",
                (
                    "and when moving you must capture if its possible",
                    "if its possible to capture and you choose to move, you must move to capture"
                    "capturing moves always take priority"
                    ),
                "."
                ],
        SpeechToken.AskToPlay : [
                (
                    "Would you like to play a game?",
                    "Do you want to play a game?",
                    "Would one kindly wish to partake in a game?"
                    )
                ],
        SpeechToken.AskIfNeedTeaching : [
                (
                    "Do you need me to",
                    "Would you like me to",
                    "Should I"
                    ),
                (
                    "teach you",
                    "show you how",
                    "help you learn"
                    ),
                "to play?"
                ],
        SpeechToken.YourTurn : [
                (
                    "It's your turn to move.",
                    "Your turn.",
                    "Your go.",
                    "You can move now",
                    ),
                ],
        SpeechToken.MyTurn : [
                (
                    "My turn",
                    "Sit back and watch the master play",
                    "My turn to move",
                    "My go"
                    ),
                ],
        SpeechToken.IllegalMove : [
                (
                    "You can't make that move",
                    "Nice try, but that isn't allowed",
                    "That's an illegal move",
                    "You can't move there",
                    )
                ],
        SpeechToken.YouWin : [
                (
                    "Congratulations",
                    "Well done",
                    "Hooray"
                    ),
                ", ",
                (
                    "the student has become the master,",
                    "",
                    ""
                    ),
                (
                    "you win!",
                    "you've won!",
                    "you beat me."
                    ),
                (
                    " I will have my revenge.",
                    "",
                    "",
                    "",
                    "",
                    ),
                ],
        SpeechToken.IWin : [
                "I win,",
                (
                    "better luck next time",
                    "oh well, perhaps next time",
                    "sorry about that old chum",
                    ),
                ],
        SpeechToken.GameNameIs : [
                (
                    "This game is called Fanorama",
                    "Fanoarama is a two player game",
                    ),
                ],
        SpeechToken.GameAimIs : [
                (
                    "The aim of the game is to capture all enemy pieces",
                    "Your aim is to capture all the opponent's pieces",
                    "You want to have no enemy pieces remaining",
                    ),
                ],
        SpeechToken.HowCapturePieces : [
                (
                    "Pieces are taken by moving away or towards enemy pieces along one of the lines on the board",
                    "To take a piece, move away or towards an opponent's piece along a line on the board",
                    "Moving along the lines of the board, towards or away from an  opponent's piece will take it"
                    ),
                ", ",
                (
                    "all pieces in the chosen direction on the line of movement are captured",
                    "in the chosen direction all your oponnent's pieces get removed from the board"
                    ),
                ". ",
                ],
        SpeechToken.HowMove : [
                (
                    "If you capture a piece then you can move again",
                    "You can move again, if you capture a piece",
                    "Capturing a piece means you can move again",
                    ),
                ", ",
                (
                    "and you can move up to one space in each direction in one turn, if you capture at least one piece per move",
                    "in one turn you can move up to one space in each direction, provided you capture a piece per move",
                    "provided you capture a piece in each move, you can move up to one space in each direction in a turn"
                    ),
                ". ",
                (
                    "You must move at least once a turn",
                    "Each turn you must move at least once",
                    "In a turn you have to move at least once"
                    ),
                ", ",
                (
                    "and when moving you must capture if its possible",
                    "if its possible to capture and you choose to move, you must move to capture"
                    "capturing moves always take priority"
                    ),
                "."
                ],
        SpeechToken.YouCheat : [
            (
                "You have clearly cheated",
                "No cheating please",
                "I can see the pieces on the board aren't in the right place",
                "The pieces on the board are not in the correct place"
                ),
            ", ",
            (
                "please move the pieces back.",
                "return them to their original positions",
                )
            ]
        }
