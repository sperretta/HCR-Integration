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
