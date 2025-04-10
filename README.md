# Drill Controller

This repository contains the drill controller PCB design and schematic files
for both the pneumatic breakout and the shield pcb.

## Pneumatic

The pneumatic breakout is designed to connect via an industrial circular 
connector, allowing power switching directly next to the solenoid valves.

The connector used is the M12 12Pin connector. Compatible connectors I've found
assuming data sheet accuracy are:

- [T4140012121-000](https://www.mouser.com/ProductDetail/TE-Connectivity/T4140012121-000?qs=l7cgNqFNU1i1rwRV8IAvtw%3D%3D)
- [M12-P12A-GPBM12](https://jlcpcb.com/partdetail/Cazn-M12_P12AGPBM12/C7423418)


## Shield

Note: Most the protection circuitry should be on the shield itself, such as
optical isolation of signals and ESD protection. Larger fuses will be located
externally for the higher voltage components.


