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
- [ ] Add Tripped fuse indicator leds.
- [ ] Create motor driver protection sheet/interface.
- [ ] Create Spin Interface Sheet.
- [ ] Create solenoid interface sheet.
- [ ] Create door interface sheet.
- [ ] Duplicate sheet accross all motor driver connections.

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


