#pragma once
#include "WProgram.h"

/*
 * Braille Numbering
 * -------
 * | 1 4 |
 * | 2 5 |
 * | 3 6 |
 * -------
 */

// Pins for Output (PWM pins!)
//byte pin[6] = {3,5,6,9,10,11};

// Pins for Output (Non-WiShield pins!)
byte pin[6] = {3,4,5,6,7,2};

void setPinsTo(byte a, byte b, byte c, byte d, byte e, byte f) {
  digitalWrite(pin[0], a);
  digitalWrite(pin[1], b);
  digitalWrite(pin[2], c);
  digitalWrite(pin[3], d);
  digitalWrite(pin[4], e);
  digitalWrite(pin[5], f);
}

void initializeOutputPins() {
  byte i;
  for (i=0; i < 6; i++) {
    pinMode(pin[i], OUTPUT);
  }
  
  setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW); // Set all pins to LOW
}

void outputChar(char x) {
  switch (x) {
    case '\n': case '\r': case ' ': case '_':
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(1000);
      break;
    case 'A': case 'a': case '1':
      setPinsTo(HIGH,LOW,LOW,LOW,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'B': case 'b': case '2':
      setPinsTo(HIGH,HIGH,LOW,LOW,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'C': case 'c': case '3':
      setPinsTo(HIGH,LOW,LOW,HIGH,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'D': case 'd': case '4':
      setPinsTo(HIGH,LOW,LOW,HIGH,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'E': case 'e': case '5':
      setPinsTo(HIGH,LOW,LOW,LOW,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'F': case 'f': case '6':
      setPinsTo(HIGH,HIGH,LOW,HIGH,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'G': case 'g': case '7':
      setPinsTo(HIGH,HIGH,LOW,HIGH,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'H': case 'h': case '8':
      setPinsTo(HIGH,HIGH,LOW,LOW,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'I': case 'i': case '9':
      setPinsTo(LOW,HIGH,LOW,HIGH,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'J': case 'j': case '0':
      setPinsTo(LOW,HIGH,LOW,HIGH,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'K': case 'k':
      setPinsTo(HIGH,LOW,HIGH,LOW,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'L': case 'l':
      setPinsTo(HIGH,HIGH,HIGH,LOW,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'M': case 'm':
      setPinsTo(HIGH,LOW,HIGH,HIGH,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'N': case 'n':
      setPinsTo(HIGH,LOW,HIGH,HIGH,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'O': case 'o':
      setPinsTo(HIGH,LOW,HIGH,LOW,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'P': case 'p':
      setPinsTo(HIGH,HIGH,HIGH,HIGH,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'Q': case 'q':
      setPinsTo(HIGH,HIGH,HIGH,HIGH,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'R': case 'r':
      setPinsTo(HIGH,HIGH,HIGH,LOW,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'S': case 's':
      setPinsTo(LOW,HIGH,HIGH,HIGH,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'T': case 't':
      setPinsTo(LOW,HIGH,HIGH,HIGH,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'U': case 'u':
      setPinsTo(HIGH,LOW,HIGH,LOW,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'V': case 'v':
      setPinsTo(HIGH,HIGH,HIGH,LOW,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'W': case 'w':
      setPinsTo(LOW,HIGH,LOW,HIGH,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'X': case 'x':
      setPinsTo(HIGH,LOW,HIGH,HIGH,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'Y': case 'y':
      setPinsTo(HIGH,LOW,HIGH,HIGH,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case 'Z': case 'z':
      setPinsTo(HIGH,LOW,HIGH,LOW,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '&':  // The word 'And'
      setPinsTo(HIGH,HIGH,HIGH,HIGH,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '<':  // CH
      setPinsTo(HIGH,LOW,LOW,LOW,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '=': // SH
      setPinsTo(HIGH,LOW,LOW,HIGH,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '>':  // ST
      setPinsTo(LOW,LOW,HIGH,HIGH,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '~':  // TH
      setPinsTo(HIGH,LOW,LOW,HIGH,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '^':  // Capital letter follows
      setPinsTo(LOW,LOW,LOW,LOW,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '#':  // Number follows
      setPinsTo(LOW,LOW,HIGH,HIGH,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '\'':  // Apostrophe
      setPinsTo(LOW,LOW,HIGH,LOW,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '.':  // Full stop (Period)
      setPinsTo(LOW,HIGH,LOW,LOW,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case ',':  // Comma
      setPinsTo(LOW,HIGH,LOW,LOW,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case ':': case ';':  // Semicolon, or colon
      setPinsTo(LOW,HIGH,HIGH,LOW,LOW,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '!': // Exclamation point
      setPinsTo(LOW,HIGH,HIGH,LOW,HIGH,LOW);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '"':  // Quotation Mark
      setPinsTo(LOW,HIGH,HIGH,LOW,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '?':  // Question Mark
      setPinsTo(LOW,LOW,HIGH,LOW,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '(': case ')':  // Bracket (Parentheses)
      setPinsTo(LOW,HIGH,HIGH,LOW,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    case '-':  // Hyphen
      setPinsTo(LOW,LOW,HIGH,LOW,LOW,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
    default:  // Unknown Character
      #if USE_SERIAL
        Serial.print("Unknown character: ");
        Serial.println(x);
      #endif
      setPinsTo(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH);
      delay(800);
      setPinsTo(LOW,LOW,LOW,LOW,LOW,LOW);
      delay(200);
      break;
  }
}

void outputString(char *str) {
  byte i = 0;
  
  while (str[i] != '\0') {
    outputChar(str[i]);
    i++;
  }
}

