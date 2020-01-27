# Thermostat

**A thermostat using the PIC16F1939 or a similar microcontroller.**

The thermostat can be programmed on a PC, using the accompanying application which can be found [here](https://github.com/HarisGusic/pic-thermostat-app). The thermostat can hold up to 25 programs, which define the minimum and maximum temperature to regulate. The user defines when each program is activated and deactivated.

For example, the thermostat can be programmed the following way:

|  Program #  |  Min temperature  | Max temperature |  Start time  |  Stop time   |
| :---------: | :---------------: | :-------------: | :----------: | :----------: |
|      1      |        21 °C      |      23 °C      |  Mon, 10:00  |  Mon, 14:35  |
|      2      |        22 °C      |     22.5 °C     |  Mon, 14:35  |  Mon, 19:00  |
|      3      |        18 °C      |      23 °C      |  Mon, 23:00  |  Tue, 10:45  |
|      4      |        19 °C      |      21 °C      | Daily, 20:00 | Daily, 22:00 |

## Documentation

All documentation, including technical specifications and implementation details, can be found in [/docs](https://github.com/HarisGusic/pic-thermostat/tree/master/docs).

<!-- Documentation about the PC application can be found [here](). -->

## Built With

* [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)

## Authors

* **Haris Gušić** - [@HarisGusic](https://github.com/HarisGusic)
* **Erol Terović** - [@ErolDude](https://github.com/ErolDude)
