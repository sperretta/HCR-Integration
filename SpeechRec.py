#!/usr/bin/env python


from sys import byteorder
from array import array
from struct import pack
from os import environ, path
import pyaudio
import wave

import requests
import httplib
import uuid
import json

import edit_distance_lib

import time

THRESHOLD = 8000
CHUNK_SIZE = 1024
FORMAT = pyaudio.paInt16
RATE = 44100

class Microsoft_ASR():
    def __init__(self):
        self.sub_key = 'eb2947d43fde465e89ba3b0b517286c3'
        self.token = None
        pass

    def get_speech_token(self):
        FetchTokenURI = "/sts/v1.0/issueToken"
        header = {'Ocp-Apim-Subscription-Key': self.sub_key}
        conn = httplib.HTTPSConnection('api.cognitive.microsoft.com')
        body = ""
        conn.request("POST", FetchTokenURI, body, header)
        response = conn.getresponse()
        str_data = response.read()
        conn.close()
        self.token = str_data
        #print "Got Token: ", self.token
        return True

    def transcribe(self,speech_file):

        # Grab the token if we need it
        if self.token is None:
            print "No Token... Getting one"
            self.get_speech_token()

        endpoint = 'https://speech.platform.bing.com/recognize'
        request_id = uuid.uuid4()
        # Params form Microsoft Example 
        params = {'scenarios': 'ulm',
                  'appid': 'D4D52672-91D7-4C74-8AD8-42B1D98141A5',
                  'locale': 'en-GB',
                  'version': '3.0',
                  'format': 'json',
                  'instanceid': '565D69FF-E928-4B7E-87DA-9A750B96D9E3',
                  'requestid': uuid.uuid4(),
                  'device.os': 'linux'}
        content_type = "audio/wav; codec=""audio/pcm""; samplerate=44100"

        def stream_audio_file(speech_file, chunk_size=1024):
            with open(speech_file, 'rb') as f:
                while 1:
                    data = f.read(1024)
                    if not data:
                        break
                    yield data

        headers = {'Authorization': 'Bearer ' + self.token, 
                   'Content-Type': content_type}
        resp = requests.post(endpoint, 
                            params=params, 
                            data=stream_audio_file(speech_file), 
                            headers=headers)
        val = json.loads(resp.text)
        return val["results"][0]["name"], val["results"][0]["confidence"]



def is_silent(snd_data):
    "Returns 'True' if below the 'silent' threshold"
    #print(THRESHOLD + sum(snd_data)/len(snd_data))
    return max(snd_data) - (sum(snd_data)/len(snd_data)) < THRESHOLD 

def normalize(snd_data):
    "Average the volume out"
    MAXIMUM = 16384
    times = float(MAXIMUM)/max(abs(i) for i in snd_data)

    r = array('h')
    for i in snd_data:
        r.append(int(i*times))
    return r

def trim(snd_data):
    "Trim the blank spots at the start and end"
    def _trim(snd_data):
        snd_started = False
        r = array('h')

        for i in snd_data:
            if not snd_started and abs(i)>THRESHOLD:
                snd_started = True
                r.append(i)

            elif snd_started:
                r.append(i)
        return r

    # Trim to the left
    snd_data = _trim(snd_data)

    # Trim to the right
    snd_data.reverse()
    snd_data = _trim(snd_data)
    snd_data.reverse()
    return snd_data

def add_silence(snd_data, seconds):
    "Add silence to the start and end of 'snd_data' of length 'seconds' (float)"
    r = array('h', [0 for i in xrange(int(seconds*RATE))])
    r.extend(snd_data)
    r.extend([0 for i in xrange(int(seconds*RATE))])
    return r

def record(timeout = 10.0):
    """
    Record a word or words from the microphone and 
    return the data as an array of signed shorts.

    Normalizes the audio, trims silence from the 
    start and end, and pads with 0.5 seconds of 
    blank sound to make sure VLC et al can play 
    it without getting chopped off.
    """
    p = pyaudio.PyAudio()
    stream = p.open(format=FORMAT, channels=1, rate=RATE,
        input=True, output=True,
        frames_per_buffer=CHUNK_SIZE)

    num_silent = 0
    snd_started = False
    
    time_started = time.time()

    r = array('h')

    while 1:
        # little endian, signed short
        snd_data = array('h', stream.read(CHUNK_SIZE))
        if byteorder == 'big':
            snd_data.byteswap()
        r.extend(snd_data)

        silent = is_silent(snd_data)
        #print(silent) 
        if silent and snd_started:
            num_silent += 1
        elif not silent and not snd_started:
            snd_started = True

        if snd_started and num_silent > 20:
            break
        
        if (time.time()-time_started)>timeout:
            return 0, 0, False

    sample_width = p.get_sample_size(FORMAT)
    stream.stop_stream()
    stream.close()
    p.terminate()

    r = normalize(r)
    r = trim(r)
    r = add_silence(r, 0.5)
    return sample_width, r, True

def record_to_file(path, timeout):
    "Records from the microphone and outputs the resulting data to 'path'"
    sample_width, data, timeout_flag = record(timeout)
    
    if not timeout_flag:
        return False
    
    data = pack('<' + ('h'*len(data)), *data)

    wf = wave.open(path, 'wb')
    wf.setnchannels(1)
    wf.setsampwidth(sample_width)
    wf.setframerate(RATE)
    wf.writeframes(data)
    wf.close()
    return True

illegal_list = ['please', 'could']
    
yes_list = ['yes', 'yeah', 'affirmative', 'yea', 'fine', 'good', 'okay', 'ok', 'true', 'sure', 'roger', 'yep']
no_list = ['no', 'nay', 'never', 'nope', 'not', 'negative']
reset_list = ['restart', 'reset', 'reboot']
pass_list = ['pass', 'skip']
help_list = ['help', 'assistance', 'assistant', 'please help', 'I dont understand what to do', "I'm confused", 'what am I supposed to do', 'give me a hand' ]
game_info = ['what is the game called', 'information', ' info', 'robot please tell me about this game']
robot_hello = ['hello robot', 'hi robot']

dictionary_list = [yes_list, no_list, reset_list, pass_list, help_list, game_info, robot_hello]

def search_dict(input_str):
    tmp_val = 1000000
    tmp_idx = 0
    for i in range(0, len(dictionary_list)):
        for j in range(0, len(dictionary_list[i])):
            edit_dist = edit_distance_lib.SequenceMatcher(a=dictionary_list[i][j], b=input_str)
            #print input_str, dictionary_list[i][j], i,j,edit_dist.distance()
            if edit_dist.distance()<tmp_val:
                tmp_val = edit_dist.distance()
                tmp_idx = i
                #print "New min value!"
    return str(dictionary_list[tmp_idx][0]), tmp_val

#if __name__ == '__main__':
    #while True:
        #print("please speak a word into the microphone")
        #record_to_file('demo.wav')
        ##print("done - result written to demo.raw")
        #ms_asr = Microsoft_ASR()
        #ms_asr.get_speech_token()
        #try:
            #text, confidence = ms_asr.transcribe('demo.wav')
            #text_data = text.split(' ')
            #print "Text: ", text.split(' ')
            #print "Confidence: ", confidence
            #print "Command: ", search_dict(str(" ".join(text_data)))
                
                
        #except KeyError:
            #print "Nothing heard"
    
def get_command(timeout = 10.0, edit_dist_JR_val = 20):
    #print("please speak a word into the microphone")
    
    timeout_flag = record_to_file('demo.wav', timeout)
    #print timeout_flag
    if not timeout_flag:
        return "Timeout!"
    #print("done - result written to demo.raw")
    ms_asr = Microsoft_ASR()
    ms_asr.get_speech_token()
    try:
        text, confidence = ms_asr.transcribe('demo.wav')
        text_data = text.split(' ')
        #print "Text: ", text.split(' ')
        
        
        command, edit_dist_JR = search_dict(str(" ".join(text_data)))
        
        if edit_dist_JR > edit_dist_JR_val:
            return "Command Not Recognised"
        
        #print "Command: ", command
        return command
        
        
    except KeyError:
        #print "Nothing heard"
        return "Nothing"
        
#print get_command()
