'''
    Flask server
'''
from flask import Flask
app = Flask(__name__)

import sys, time
from controller import LeapFlaskListener, Leap


listener = LeapFlaskListener()
controller = Leap.Controller()

# Have the sample listener receive events from the controller
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


@app.route('/')
def hello_world():
    return 'Success!'

if __name__ == "__main__":
    app.run()
