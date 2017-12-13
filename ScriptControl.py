from random import randint

class ChoiceScriptComponent:
    LOCK_LENGTH = 5
    def __init__(self,options):
        self._options = options
        self._locks = [0] * len(options)
        if len(self._locks) < ChoiceScriptComponent.LOCK_LENGTH:
            self.LOCK_LENGTH = len(self._locks)-2

    def _reduceLock(self):
        self._locks[:] = [(lockLength-1) if lockLength > 0 else 0 for lockLength in self._locks]

    def _lockChoice(self,index):
        self._locks[index] = self.LOCK_LENGTH

    def getRandomSegment(self):
        options = [(option,index) for index,option in enumerate(self._options) if self._locks[index] == 0]
        if len(options) == 1:
            segmentChoice = 0
        else:
            segmentChoice = randint(0,len(options)-1)
        self._reduceLock()
        self._lockChoice(options[segmentChoice][1])
        return options[segmentChoice][0]

class ScriptItem:
    def __init__(self,script):
        self._script = []
        for item in script:
            if isinstance(item,str):
                self._script.append(item)
            elif isinstance(item,tuple):
                self._script.append(ChoiceScriptComponent(item))
            else:
                raise Exception("Invalid type in script datastructure")

    def generateScriptLine(self):
        line = ""
        for segment in self._script:
            if isinstance(segment,str):
                line += segment
            elif isinstance(segment,ChoiceScriptComponent):
                line += segment.getRandomSegment()
        return line
