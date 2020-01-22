## `struct Program`

The current data structure for storing a program is defined as follows:
```c
struct PROGRAM_LIMIT
{
    char startDay, endDay;   // Start and end day
    unsigned short on, off;  // Activation and deactivation time
    unsigned short min, max; // Min and max regulated temperature
}
```
_Note that another bit of information must be included: whether the program is active. This information is coded in the sign of `startDay` - a positive sign indicates that the program is active._

The data structure requires 10 bytes of storage as it is currently defined.

---

However, should limited data storage become a problem,
the definition can be changed based on the following considerations:

* Information about whether the program is active should be coded somewhere in the data structure. One bit of storage is required for this.

* `startDay` and `endDay` must store values 0 - 6, which requires 3 bits of storage for each.

* With the current programming resolution of one minute, `on` and `off` need only store values from 0 - 1439 (the number of minutes in a day). Therefore, these attributes require only 11 bits of storage each.

The total amount of storage for the structure with the above optimizations in mind would be 1+6+22+32 = 61 bits, i.e. 8 bytes.
