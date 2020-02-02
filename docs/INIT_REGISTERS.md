# Register Initializations

This documents shows the contents of various registers after initialization of various functionalities, i.e. after the `init_*` functions have been called.

This file should be regularly updated, especially if another microcontroller is used.

## Pin modes

#### Port A

|              | Bit  7 | Bit  6 | Bit  5 | Bit  4 | Bit  3 | Bit  2 | Bit  1 |      Bit 0     |
| :----------: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :------------: |
| **Function** | Unused | Unused | Unused | Unused | Unused | Unused | Unused | TEMPERATURE_IN |
|   **TRISA**  |   *    |   *    |   *    |   *    |   *    |   *    |   *    |        1       |
|  **ANSELA**  |   0    |   0    |   0    |   0    |   0    |   0    |   0    |        1       |

_<span>* Any value can be assigned</span>_

#### Port B

This port is currently unused.

#### Port C

|              | Bit  7 | Bit  6 | Bit  5 | Bit  4 | Bit  3 | Bit  2 | Bit  1 |    Bit 0   |
| :----------: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :--------: |
| **Function** | RX_IN  | TX_OUT | Unused | Unused | Unused | Unused | Unused | HEATER_OUT |
|   **TRISC**  |   1    |   0    |   *    |   *    |   *    |   *    |   *    |      0     |

_<span>* Any value can be assigned</span>_

#### Port D

|              | Bit  7 | Bit  6 | Bit  5 | Bit  4 | Bit  3 | Bit  2 | Bit  1 |         Bit 0        |
| :----------: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :------------------: |
| **Function** | Unused | Unused | Unused | Unused | Unused | Unused | Unused | HEATER_INDICATOR_OUT |
|   **TRISD**  |   *    |   *    |   *    |   *    |   *    |   *    |   *    |           0          |
|  **ANSELD**  |   0    |   0    |   0    |   0    |   0    |   0    |   0    |           0          |

_<span>* Any value can be assigned</span>_

## Interrupts

#### OPTION_REG

|  WPUEN  |  INTEDG  | TMR0CS | TMR0SE | PSA | PS2 | PS1 | PS0 |
| :-----: | :------: | :----: | :----: | :-: | :-: | :-: | :-: |
|  Unused |  Unused  |    0   |    *   |  0  |  1  |  1  |  1  |

_<span>* Any value can be assigned</span>_

#### INTCON

|  GIE  |  PEIE  |  TMR0IE  |  INTE  |  IOCIE  |  TMR0IF  |  INTF  |  IOCIF  |
| :---: | :----: | :------: | :----: | :-----: | :------: | :----: | :-----: |
|   1   |   1    |    1     | Unused | Unused  |     0    | Unused |  Unused |

## EEPROM

#### EECON1

| EEPGD |  CFGS  |   LWLO   |  FREE  |  WRERR  |   WREN   |    WR    |    RD    |
| :---: | :----: | :------: | :----: | :-----: | :------: | :------: | :------: |
|   1   |   1    |  Unused  | Unused | Unused  |     0    | 0 (Auto) | 0 (Auto) |
