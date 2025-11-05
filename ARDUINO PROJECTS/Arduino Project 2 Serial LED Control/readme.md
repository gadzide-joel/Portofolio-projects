# Arduino Project 2: Serial LED Control
This sketch (Module 4 Peer Review.txt) implements serial communication to control the onboard LED (Pin 13) using commands sent from the computer's Serial Monitor.

# Functionality
Serial Communication: The setup() function initializes serial communication at a standard 9600 baud rate.

Input Handling: The loop() function continuously checks for incoming data using Serial.available().

Command Logic: The LED state is controlled by reading a single character from the serial port:

Sending '1' turns the LED ON (digitalWrite(ledPin, HIGH)).

Sending '0' turns the LED OFF (digitalWrite(ledPin, LOW)).

Usage: The user must open the Arduino IDE Serial Monitor and send the characters '1' or '0' to interact with the sketch.