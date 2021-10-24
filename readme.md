# Load Firmware from XMC ASC Bootstrap

This script allows to load a firmware to Infineon XMC SRAM with an UART adapter (Ex: FT232RL).
Firmware needs to be converted from .hex to .bin before hand.

More information about ASC BSL can be found [here](https://www.infineon.com/dgdl/Infineon-TOO_XMC1000_Boot_Modes-ApplicationNotes-v01_04-EN.pdf?fileId=db3a30433ea3aef6013eb2429b8c1bdb).

Baud rate may need to be adjusted based on MCU clock frequency, check below:
![Baudrate Information](docs/baudrate.png?raw=true)

One important aspect of ASC is that the firmware is loaded to SRAM instead of flash. Because of that, the linker script of your program may need to be adjusted.

### Enabling SWD
If you just want to enable SWD and don't have a programmer capable of SPD (Ex: J-Link EDU Mini), you can use the DAVE project available in this repo. It's based on the XMC1x_ASCLoader and was tested on an XMC1302-T038x200.

After flashing it, the code will set the BMI register to 0xF8C3, which enables SWD. Also, for verification purposes, the code will keep sending bytes through UART until a new firmware is flashed.