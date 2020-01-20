# Register Initializations

This documents shows the contents of various registers after initialization of various functionalities, i.e. after the `init_` functions have been called.

This file should be regularly updated, especially if another microcontroller is used.

## Interrupts

#### OPTION_REG

|  WPUEN  |  INTEDG  | TMR0CS | TMR0SE | PSA | PS2 | PS1 | PS0 |
| :-----: | :------: | ------ | ------ | --- | --- | --- | --- |
|  Unused |    TBD   |    0   |    0   | TBD | TBD | TBD | TBD |

#### INTCON

|  GIE  |  PEIE  |  TMR0IE  |  INTE  |  IOCIE  |  TMR0IF  |  INTF  |  IOCIF  |
| :---: | :----: | :------: | :----: | :-----: | :------: | :----: | :-----: |
|   1   |  TBD   |    1     |  TBD   |   TBD   |     0    |  TBD   |   TBD   |
