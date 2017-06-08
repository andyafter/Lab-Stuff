import os, sys, inspect, thread, time, socket
src_dir = os.path.dirname(inspect.getfile(inspect.currentframe()))
#arch_dir = './lib/x64' if sys.maxsize > 2**32 else './lib/x86'
arch_dir = '../lib'
sys.path.insert(0, os.path.abspath(os.path.join(src_dir, arch_dir)))

import Leap
from Leap import CircleGesture, KeyTapGesture, ScreenTapGesture, SwipeGesture


class LeapFlaskListener(Leap.Listener):

    def on_connect(self, controller):
        self.UDP_IP = '0.0.0.0'
        self.UDP_PORT = 5112
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print "Connected"

    def on_frame(self, controller):
        self.fingers = []
        
        frame = controller.frame()
        #print "Frame id: %d, timestamp: %d, hands: %d, fingers: %d" % (
        #frame.id, frame.timestamp, len(frame.hands), len(frame.fingers))
        pointable = frame.pointables.frontmost
        direction = pointable.direction
        length = pointable.length
        width = pointable.width
        stabilizedPosition = pointable.stabilized_tip_position
        position = pointable.tip_position
        speed = pointable.tip_velocity
        touchDistance = pointable.touch_distance
        zone = pointable.touch_zone
        for point in frame.pointables:
            # point here is a pointable
            self.fingers.append(point)
        MESSAGE = str(len(self.fingers))
        self.sock.sendto(MESSAGE, (self.UDP_IP, self.UDP_PORT))


def main():
    # Create a sample listener and controller
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

main()
