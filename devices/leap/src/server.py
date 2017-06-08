'''
    Flask server
'''
from flask import Flask
app = Flask(__name__)

import sys, time
import threading
import json

from controller import LeapFlaskListener, Leap

pointables = []


def listen():
    # Have the sample listener receive events from the controller
    
    listener = LeapFlaskListener()
    controller = Leap.Controller()

    controller.add_listener(listener)

    # Keep this process running until Enter is pressed
    print "Press Enter to quit..."
    try:
        sys.stdin.readline()
    except KeyboardInterrupt:
        pass
    finally:
        # Remove the sample listener when done
        controller.remove_listener(listener)

#t = threading.Thread(target=listen)
#t.start()


@app.route('/')
def hello_world():
    return 'Success!'


@app.route('/fingers')
def get_fingers():
    return str(len(pointables))


if __name__ == "__main__":
    app.run()
