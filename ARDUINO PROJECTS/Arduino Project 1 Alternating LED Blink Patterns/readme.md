# Arduino Project 1: Alternating LED Blink Patterns
This sketch (Module 3 Peer Review.txt) demonstrates basic digital I/O control and timing by creating alternating fast and slow blinking patterns on the built-in Arduino LED (Pin 13).

# Functionality
Custom Function: Uses a helper function, blinkOnce(high_ms, low_ms), to encapsulate a single ON/OFF cycle.

Sequential Patterns: The main loop() function executes two distinct patterns consecutively:

Fast Blink: Five cycles with a short delay (e.g., 500ms ON / 500ms OFF).

Slow Blink: Five cycles with a long delay (e.g., 1000ms ON / 1000ms OFF).

Hardware Setup: Requires no external components; uses the onboard LED on Pin 13.
