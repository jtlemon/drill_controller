# Arduino Mega Shield

## Protection

- ESD
- OVP
- OCP
- Opto-isolation




## TODO

- [X] Setup main sheet info.
- [X] Add mega connectors
- [ ] Add M12 connections(sym, fp, step).
- [X] Add sheets for uC
- [X] Add X-Axis uc-Labels
- [X] Add Y-Axis uc-Labels
- [X] Add Z-Axis uc-Labels
- [X] Add A-Axis uc-Labels
- [X] Add B-Axis uc-Labels
- [X] Add C-Axis uc-Labels
- [X] Add remaining uc-Labels
- [ ] Create motor driver protection sheet/interface.
- [ ] Create Spin Interface Sheet.
- [ ] Create solenoid interface sheet.
- [ ] Create door interface sheet.
- [ ] Duplicate sheet accross all motor driver connections.

## servo interface

The servo interface takes in a +36v and +5v supply line.

All the interfaces need to have opto-isolators and be fused or protected
against short circuit conditions as well as over-voltage/current.

**Opto-isolators:**

The original chip used is a DIP package and totally out of stock, it also
costs a good amount.

Replacement will be done using the 6N137 which is a jellybean component so
highly availble from various manufactures.


