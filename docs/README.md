## EEPROM Memory Structure <a name="ref_eeprom"></a>

<table>
    <thead>
        <tr>
            <th align="center">Address</th>
            <th align="center">Content</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td align="center"> 00 </td>
            <td> VERSION_CODE </td>
        </tr>
        <tr>
            <td align="center" rowspan=2>
                01 <br>
                ⋮
            </td>
            <td align="left" rowspan=2>
                Reserved for configuration data. <br>
                <b>Current version does not use this space.</b>
            </td>
        </tr>
        <tr></tr> <!-- Skip -->
        <tr>
            <td align="center">
                <code>eepromStartAddress</code>
            </td>
            <td>Number of programs stored in the EEPROM</td>
        </tr>
        <tr>
            <td align="center" rowspan=3>
                <code>eepromStartAddress</code> + 1 <br>
                ⋮ <br>
                EEPROM_SIZE - 1
            </td>
            <td align="left" rowspan=3>
                <br>
                Program data
                <br><br>
            </td>
        </tr>
    </tbody>
</table>

Programs are stored in contiguous memory blocks, each of which is `sizeof (struct Program)`
bytes wide. Thus, the maximum number of programs that can be stored in EEPROM can be
calculated as:

<center> (EEPROM_SIZE - 1 - <code>eepromStartAddress</code>) / <code>sizeof(struct Program)</code> </center>
<br><br>

With the current configuration, using PIC16F1939, we can store a maximum of 25 programs.

## `struct Program` <a name="ref_program"></a>

The current data structure for storing a program is defined as follows:
```c
struct PROGRAM_LIMIT
{
    char startDay, endDay;   // Start and end day
    unsigned short on, off;  // Activation and deactivation time
    unsigned short min, max; // Min and max regulated temperature
}
```
_Note that another bit of information must be included: whether the program is active. This information is coded in the sign of_ `startDay` _- a positive sign indicates that the program is active._

The data structure requires 10 bytes of storage as it is currently defined.

---

However, should limited data storage become a problem,
the definition can be changed based on the following considerations:

* Information about whether the program is active should be coded somewhere in the data structure. One bit of storage is required for this.

* `startDay` and `endDay` must store values 0 - 6, which requires 3 bits of storage for each.

* With the current programming resolution of one minute, `on` and `off` need only store values from 0 - 1439 (the number of minutes in a day). Therefore, these attributes require only 11 bits of storage each.

The total amount of storage for the structure with the above optimizations in mind would be 1+6+22+32 = 61 bits, i.e. 8 bytes.

## Communication <a name="ref_comm"></a>

The thermostat uses serial communication to communicate with the PC, via the built-in UART module of the microcontroller. The general flow of communication is the following:

1. The PC sends a `REQUEST_CONNECTION` byte, to which the thermostat responds by returning the same byte. <br>
_The connection has been established._

1. The PC periodically sends `REQUEST` characters, which are classified as RX and TX. If the request is RX, the microcontroller is expected to send data to the PC. Conversely, if the request is TX, the PC is expected to send data to the microcontroller.

1. The appropriate device sends the requested raw data in a continuous transmission. There is no data verification. <br>
_If data fails to be delivered within a specified timeout period, the connection has been lost and has to be re-established if data is to be transferred._

#### Communication Requests

Communication request codes are defined in the header file ["/src/communication.h"](https://github.com/HarisGusic/pic-thermostat/blob/master/src/communication.h).

_Note: RX and TX requests can be made if and only if the connection has been established. Otherwise, they will be ignored._

##### `REQUEST_RX_TEMP`

Request the current measured temperature. Upon reception, the microcontroller sends raw temperature data as a sequence of bytes.

##### `REQUEST_RX_TIME`

Request the current time on the thermostat. Upon reception, the microcontroller then sends raw time data as a sequence of bytes.

##### `REQUEST_RX_CURRENT_PROGRAM`

Request the currently active program on the thermostat. Upon reception, the microcontroller sends the data of the currently active program as a sequence of bytes defined by [`struct Program`](#ref_program).

##### `REQUEST_RX_PROGRAMS`

Request all stored programs on the thermostat to be sent to the PC. Upon reception, the microcontroller sends the entire `programs` array as a sequence of bytes, to the PC.

---

##### `REQUEST_TX_TIME`

Request the current time to be sent to the thermostat. This is used to synchronise the thermostat's clock with the PC's clock. The sent data is a sequence of bytes.

##### `REQUEST_TX_PROGRAM`

Request program data to be sent to the thermostat. This overrides the data stored on the thermostat for the program with the specified index. The sent data is a sequence of bytes defined by [`struct Program`](#ref_program).

##### `REQUEST_TX_PROGRAMS`

Request all programs on the thermostat to be overriden by the sent data. If the thermostat contained more programs than have been sent, the excess programs are rendered inaccessible.

#### Software implementation

//TODO
