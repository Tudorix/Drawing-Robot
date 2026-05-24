# Drawing Robot

![Drawing Robot](Media/Final.jpeg)

A simple 2D drawing robot built using an ESP8266, servo motors and inverse kinematics.

The robot controls a pen using two servo-driven arms and a SG90 servo for lowering the pen and computes the required angles to reach points in a 2D plane. An IR remote is used to control movements and drawing actions wirelessly.

Watch demo: https://youtu.be/7PwpwJKB_Jg

## What I learned

- Basic inverse kinematics for 2D robotic arms
- Controlling multiple servo motors with an ESP8266
- Reading commands from an IR remote
- Converting coordinates into servo angles
- Mechanical design and CAD modeling for robotic linkages

## Challenges

- Calibrating the servos for accurate positioning
- Reducing wobble and mechanical play in the arms
- Making the movement smooth and repeatable
- Finding arm lengths that balance precision and drawing area
- Synchronizing both servos for coordinated motion

## Limitations

- The servos are not very precise and introduce small positioning errors
- The drawing area is relatively small because of the arm length
- Servo backlash affects line accuracy and repeatability
- Drawing speed is limited by the servo motors

## Possible Improvements

- Using higher quality or metal gear servos
- Replacing the servos with stepper motors for better precision
- Increasing the arm length for a larger drawing area
