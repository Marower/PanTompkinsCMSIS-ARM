# Pan-Tompkins algorithm CMSIS DSP library
 Implementation of Pan-Tompkins algorithm with CMSIS DSP library for ARM

## Communication over serial terminal

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