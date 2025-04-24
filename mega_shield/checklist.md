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
- [X] Duplicate sheet accross all motor driver connections.
- [X] Remove +36V protection circuit from servo interfaces.
- [X] Add test points to all sheets.
- [ ] Check/run simulation of servo interface fets.
- [X] Remove the I/O Interface sheet.
- [X] Remove the connectors for the maximum limit sensors.
- [X] Add Power supply sections.
- [X] Add 10V connection to spindle.
- [X] Run footprint assignment tool for all components.
- [ ] Run ERC on schematics.
- [ ] Bulk edit all components to ensure JLCPCB number assignment.
- [ ] 

## Power Protection

Anywhere the 5V/36V lines may iteract will be electrically isolated.

All digitals outputs need to be electricaly isolated and current limited.
All digital inputs need to be electrically isolated.



## servo interface

The servo interface takes in a +36v and +5v supply line.

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

The CS817x22HS in particular seem like a good potential canidate.


## solenoid interface

This section needs fuses as well as ESD protection given that it's dealing
with solenoids.

Rational behind the ESD chips is the potential for an solenoid's collapsing
magnetic field to produce a voltage spike if the snubber diodes failed.


## door interface

The door interface in the provided schematics is using a non-inverting 
schmitt trigger for debouncing I assume.

Issue is that component isn't availble or in stock on jlcpcb and the 
non-inverting type of schmitt trigger are a lot less common than inverting 
ones are.

I think I may design an op-amp circuit to act as a substitue using jellybean
components instead, this should make it easier to source parts in the
future as well.

After comparing the datasheets, it's possible the CS817x22HS could be used 
on the door sheet to replace both the opto-isolator and the schmitt triger IC,
this would bring down the cost and decrease latancy.

