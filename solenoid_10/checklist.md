# Pneumatic Solenoid 10ch

I think I need to rework some of PCB constraints to allow the build cost to be
lower, such as the silkscreen minimum sizes and the Vias diameters.

Also changing out the input protection might be a good idea, maybe using 
active ov and oc protection.

I think changing the text info to use the project variables on the silkscreen
layer is also another good change.


## Ideas

- Conformal coating for PCB protection?
- Per channel Polyfuses?
- Indicator LEDs?
- Manual actuation buttons?
- Optical isolation?


## TODO

- [X] Add M8 or M12 connector Symbols
- [X] Add M8 or M12 connector footprints.
- [X] Add spade connector Symbols.
- [X] Add spade connector footprints.
- [X] Add OV protection.
- [X] Add OC protection.
- [X] Source N-CH Mosfet.
- [X] Source Tactile switch.
- [X] Source smd led.
- [X] Source fuses.
- [X] Add test points.
- [X] Add M codes to silkscreen.
- [X] Take spade connector dimensions/locations.
- [X] Take overall PCB dimensions.
- [X] Setup Netclasses.
- [X] change sheet company name --> "Homewood Creations"
- [X] Add model for M12 conn.
- [X] Add model for LED.
- [X] Add model for button.
- [X] Change hole size to 3.5mm
- [X] Update C2C of holes to 23mm
- [X] Offset hole from edge by 12.859mm
- [X] Add mounting holes near M12 connecotr, C2C 32mm, diam: 4.5mm
- [X] Move the Mosfets 2mm right(aka X-axis +2mm)
- [ ] Import logo's onto boards.
- [X] Run DRC rulecheck.
- [X] Update pcb constraints for lower cost jlcPCB options.
- [X] Update silk-screen with variables


## Dimension Data(Original PCB)

Overall Length: 252.73mm

Solenoid C2C spade distance: 11.00074mm
Solenoid Hole Diameter: 3.2mm

