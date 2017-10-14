import speech_recognition as sr
import time

r = sr.Recognizer()
m = sr.Microphone()

try:
    print("A moment of silence, please...")
    with m as source: r.adjust_for_ambient_noise(source)
    print("Set minimum energy threshold to {}".format(r.energy_threshold))
    x = 0;
    while True:
        fantasma = 0;
        print("Say something!")
        with m as source: audio = r.listen(source)
        print("Got it! Now to recognize it...")
        try:
            # recognize speech using Google Speech Recognition
            value = r.recognize_google(audio)
            fi = open('input.txt','w')
            # we need some special handling here to correctly print unicode characters to standard output
            if str is bytes:  # this version of Python uses bytes for strings (Python 2)
                fi.write("{}".format(value).encode("utf-8"))
            else:  # this version of Python uses unicode for strings (Python 3+)
                fi.write("{}".format(value))
            fi.close()

            fo = open('output.txt','r')
            text = fo.read()
            fo.close()
            while text == "":
                fo = open('output.txt','r')
                text = fo.read()
                fo.close()
                print("txt vacio")
                time.sleep(5)
            fi = open('output.txt','w')
            fi.write('')
            fi.close()
        except sr.UnknownValueError:
            fantasma = 0
        except sr.RequestError as e:
            fantasma = 0

except KeyboardInterrupt:
    pass
