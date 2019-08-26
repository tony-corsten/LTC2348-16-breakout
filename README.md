# teensy36_ltc2348_datalogger
This project is intended to provide a high resolution datalogger for the Teensy 3.6. The Analog Devices LTC2348-16/-18 supports fully-differential, pseudo-differential and single-ended bipolar signaling at either 16 or 18-bit resolution (1LSB INL). The existing Linduino library does not directly work as a port for Arduino-compatible systems (as it's intended to be used with the Linduino board, not surprisingly!). This project features:

- Arduino-compatible code for the Teensy 3.6 
- up to 50kHz sampling frequency using all 8 channels
- SD card writing in real-time
- UART output @ 921600 baudrate, and a compatible MATLAB script for efficient logging. In the future, there will also be a Python executible.
