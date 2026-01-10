# Servo Adapter Checklist

*Note:* Step file is the correct or accurate file to base it off of. 


## Schematic
- [X] Add the servo motor to adapter power connector.
- [X] Add the servo motor to adapter signal connector:
- [X] Add the servo motor to shield power connector.
- [X] Add the servo motor to shield signal connector.
- [X] Add mounting holes.
- [X] Add all needed JLCPCB numbers.
- [ ] Pass electrical rules check.

## PCB

- [X] Extract the needed dimensions from the step file.
- [X] Setup PCB as 4-layer for extra EMI resistance.
- [X] Add ground plane.
- [ ] Add power plane.
- [ ] Add connector info to front and back silkscreen layer.
- [ ] Add version number to silkscreen layer.
- [X] Import Components into PCB editor
- [ ] Fix issue with rotated 3D model. 


## Components

The design's given from the 2022 REV.B show what looks like du-pont 2.54mm
pin sockets for both the connectors that go into the servo motors.

I think the actual connector's used are the 3.81mm Phoenix Contact connectors
specifically the IMCV series.

The signal connector doesn't seem to be the 2.54mm connector indicated in the
given schematics from the datasheet and 3D model of the stepper motors I have
found.

My thoughts are that the connector needs to be changed, but it may be that
it's been checked and found compatible with the 2.54mm spacing?


