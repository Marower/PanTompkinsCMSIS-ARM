# Pan-Tompkins algorithm CMSIS DSP library
 Implementation of Pan-Tompkins algorithm with CMSIS DSP library for ARM

## Communication over serial terminal
### Data opperation
Each sample must be send in one line (ended with \r\n) with chosed format of data: <BR/>
- as string - as human redable text
- as bytes - two bytes integer, little endian coded.

After each sample device will send actual values of valiable, as line with comma separated of values of Pan-Tompkins algorithm:
Output,filter_value,deriverative,squared,moving_windows,THL1,THF\r\n
- delay - 0 if peak wasn't detected or numer of sample delay for peek detected
- filter_value - current filter value
- deriverative - current value of derivative
- squared - current value in squared values buffer 
- moving_windows - current value in moving window
- ThI1 - Threshold I1 (Integrated signal)
- ThF1 - Threshold F1 (Band-passed signal)

### Commands
Example:
+++B1\r\n
- First three +++ indicate command
- 4 byte - select comand
- next bytes are comand parameter
- line end with \r\n

#### changeDataFormat
Command change data code method<BR/>
Byte[4] == 'A' (0x41)<BR/>
Command take 1 byte parameter<BR/>
Byte[5] == '1' (0x31)<BR/>
indicate that data will be coded as string<BR/>
<BR/>
Byte[5] == '2' (0x32)<BR/>
indicate that data will be coded as two byte, little endian<BR/>

#### changeSelectedAlgorithm
Command chose implementation of Pan-TOmpkins Algorithm<BR/>
Byte[4] == 'B' (0x42)<BR/>
Command take 1 byte parameter<BR/>
Byte[5] == '1' (0x31)<BR/>
use Hooman650's implementation<BR/>
https://github.com/hooman650/Pan-Tompkins-FixedPoint#1<BR/>

Byte[5] == '2' (0x32)<BR/>
use modifiy Rafael de Moura Moreira's implementationn<BR/>
https://github.com/rafaelmmoreira/PanTompkinsQRS<BR/>