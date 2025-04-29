# Arduino Mega Shield

- Screw terminals > non-screw terminals.

## Protection

- ESD
- OVP
- OCP
- Opto-isolation

## TODO

- [X] Setup main sheet info.
- [X] Add mega connectors
- [X] Add M12 connectors(sym, fp, step).
- [X] Add sheets for uC
- [X] Add X-Axis uc-Labels
- [X] Add Y-Axis uc-Labels
- [X] Add Z-Axis uc-Labels
- [X] Add A-Axis uc-Labels
- [X] Add B-Axis uc-Labels
- [X] Add C-Axis uc-Labels
- [X] Add remaining uc-Labels
- [X] Add Tripped fuse indicator leds.
- [X] Create motor driver protection sheet/interface.
- [X] Create Spin Interface Sheet.
- [X] Create solenoid interface sheet.
- [X] Create door interface sheet.
- [X] Create homing interface sheet.
- [X] Duplicate sheet across all motor driver connections.
- [X] Remove +36V protection circuit from servo interfaces.
- [X] Add test points to all sheets.
- [X] Remove the I/O Interface sheet.
- [X] Remove the connectors for the maximum limit sensors.
- [X] Add Power supply sections.
- [X] Add 10V connection to spindle.
- [X] Run footprint assignment tool for all components.
- [X] Run ERC on schematics.
- [X] Bulk edit all components to ensure JLCPCB number assignment.
- [X] Find substitute Connectors that are in stock.
- [X] Create Net classes.
- [X] Assign Net classes.
- [X] Setup PCB constraints for JLCPCB manufacturing.
- [X] Figure out probe connection.
- [X] Create a couple of solenoid drivers onto the board.
- [X] Add local solenoid driver sheet.
- [X] Move all proxy sensors to one side.
- [X] Move all screw terminals to the other side.
- [X] Add mounting holes, basic square pattern.
- [X] Change the +5V power connector to different size than the +24V connection.
- [ ] Add some filter capacitors to the power interface.
- [ ] Double check all bypass capacitors for ideal resonance frequencies.
- [ ] Re-update the JLCPCB numbers.
- [X] Add symbols/footprints for XT30 connectors.
- [X] Add symbols/footprints for JST-XH connectors.
- [X] Change the 5V power connector to the JST 2pos connector.
- [X] Change the 24V power connector to the XT30 connector.
- [X] Isolate the +5V of the Arduino from external +5V power.
- [ ] Add the solenoid driver connections inside the mega interface.


## PCB design requirements



## Power Protection

All digitals outputs need to be electrically isolated and current limited.
All digital inputs need to be electrically isolated.



## servo interface

All the interfaces need to have opto-isolators and be fused or protected
against short circuit conditions as well as over-voltage/current.

**Opto-isolators:**

The original chip used is a DIP package and totally out of stock, it also
costs a good amount.

Replacement could be done using the 6N137 which is a jellybean component so
highly availble from various manufactures.

**NOTE:** Digital isolator's offer higher speed and don't suffer from the slow
off state that photo-transistors do.

Photodiode based opto-isolators can provide higher speed but still are slower
than newer digital isolators.

The CS817x22HS in particular seem like a good potential candidate.


## solenoid interface

This section needs fuses as well as ESD protection given that it's dealing
with solenoids.

Rational behind the ESD chips is the potential for an solenoid's collapsing
magnetic field to produce a voltage spike if the snubber diodes failed.

