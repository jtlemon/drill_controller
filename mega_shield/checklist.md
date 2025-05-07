# Arduino Mega Shield

- Screw terminals > non-screw terminals.

## Protection

- ESD
- OVP
- OCP
- Opto-isolation

## TODO

- [X] Add test points to all sheets.
- [X] Run ERC on schematics.
- [X] Bulk edit all components to ensure JLCPCB number assignment.
- [ ] Add some filter capacitors to the power interface.
- [ ] Double check all bypass capacitors for ideal resonance frequencies.
- [X] Re-update the JLCPCB numbers.
- [ ] Add GPIO for 24V control, setup for low-side digital switching.
- [X] Add pull-down resistors to all fets, mega pins could be in input on reset causing fets to pulse trigger during resets.
- [X] Duplicate/re-factor solenoids as general purpose outputs(More flexibility.).
- [ ] Ensure digital outputs in low-side mode.
- [ ] Check V_gs is setup for correct Vmax
- [X] Add both models of the digital isolator IC.
- [X] Add alternate digital isolators.
- [X] Change isolator in spindle interface.
- [X] Change isolator in digital inputs/outputs.
- [X] Add voltage dividers for the new isolators.
- [X] Swap all proximity sensors to using opto isolation(cheaper for low speed.)
- [ ] Create layout for digital inputs.
- [ ] Create layout for solenoid interface.
- [ ] Re-Route all traces.
- [ ] Run checks/tests.


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
highly available from various manufactures.

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

