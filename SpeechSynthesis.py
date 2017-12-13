import naoqi
import ScriptControl 

from SpeechTokens import SpeechToken
import Script

class SpeechSynthesis:
    NAO_PORT = 9559

    def __init__(self,ip):
        """Construct speech synthesis class

        Arguments:
        -ip: IP address of NAO robot (string)
        """
        self._tts = naoqi.ALProxy("ALTextToSpeech",ip,SpeechSynthesis.NAO_PORT)
        self._script = {
                token:ScriptControl.ScriptItem(scriptRaw)
                for token,scriptRaw in Script.data.iteritems()
                }

    def sayToUser(self,speechToken):
        if not isinstance(speechToken,SpeechToken):
            raise Exception(
                    "Invalid input to function, expected type SpeechToken, got {0}".format(
                        type(speechToken)
                        )
                    )
        self._tts.say(self._script[speechToken].generateScriptLine())

def speakWords(robotip, input_d):
    if input_d == 1:
        token = SpeechToken.Vocalise
    elif input_d == 2:
        token = SpeechToken.CheckHelpNeeded
    elif input_d == 3:
        token = SpeechToken.Greeting
    elif input_d == 4:
        token = SpeechToken.CheckUnderstanding
    elif input_d == 5:
        token = SpeechToken.MovePieces
    elif input_d == 6:
        token = SpeechToken.Introduction
    elif input_d == 7:
        token = SpeechToken.AskToPlay
    elif input_d == 8:
        token = SpeechToken.AskIfNeedTeaching
    elif input_d == 9:
        token = SpeechToken.YourTurn
    elif input_d == 10:
        token = SpeechToken.MyTurn
    elif input_d == 11:
        token = SpeechToken.IllegalMove
    elif input_d == 12:
        token = SpeechToken.YouWin
    elif input_d == 13:
        token = SpeechToken.IWin
    elif input_d == 14:
        token = SpeechToken.GameNameIs
    elif input_d == 15:
        token = SpeechToken.GameAimIs
    elif input_d == 16:
        token = SpeechToken.HowCapturePieces
    elif input_d == 17:
        token = SpeechToken.HowMove
    elif input_d == 18:
        token = SpeechToken.YouCheat
    
    speech_engine = SpeechSynthesis(robotip)
    
    speech_engine.sayToUser(token)
    
   
