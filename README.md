# teensy36_ltc2348_datalogger
This project is intended to provide a high resolution, fully differential, +/- 10.24V datalogger for the Teensy. The existing Linduino library does not directly work as a port for Arduino-compatible systems (as it's intended to be used with the Linduino board, not surprisingly!). This project features:

- Arduino-compatible code for the Teensy 3.6 
- ~20kHz sampling frequency using all 8 channels
- SD card writing (although this will not guarantee fixed 20kHz operation due to allocation cluster lag)
- UART output @ 921600 baudrate, and a compatible MATLAB script for efficient logging. In the future, there will also be a Python executible.