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
            ", ",
            (
                "would you like to ",
                "are you ready to "
                ),
            "play a game?"
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
            ]
        }
