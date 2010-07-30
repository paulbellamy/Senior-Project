#pragma once
#include "WProgram.h"
#include <avr/pgmspace.h>
#include "queue.h"

/*
 * Morse Code -> Binary Representation
 *
 * 1. short mark, dot or 'dit' (·) — 1
 * 2. longer mark, dash or 'dah' (–) — 111
 * 3. intra-character gap (between the dots and dashes within a character) — 0
 * 4. short gap (between letters) — 000
 * 5. medium gap (between words) — 0000000
 *
 * For training, the length of 4 and 5 are exaggerated by some common factor (Farnsworth Method).
 *
 * Reference: http://en.wikipedia.org/wiki/Morse_code
 */

int pin[6] = {3,4,5,6,7,2}; //  Only outputting on pin3 for now

int cpm = 40; // Characters per minute to output
int inter_letter_training_factor = 3; // Amount of zeros to add to each inter-letter gap
int inter_word_training_factor   = 5; // Amount of zeros to add to each inter-word gap

// Define our queues
queue* outputQ;
queue* morseQ;

void setPinsTo(byte a) {
  digitalWrite(pin[0], a); // Only using one pin for now
  digitalWrite(pin[1], a);
  digitalWrite(pin[2], a);
  digitalWrite(pin[3], a);
  digitalWrite(pin[4], a);
  digitalWrite(pin[5], a);
}

void initializeOutput() {
  pinMode(pin[0], OUTPUT); // only one pin for now
  pinMode(pin[1], OUTPUT);
  pinMode(pin[2], OUTPUT);
  pinMode(pin[3], OUTPUT);
  pinMode(pin[4], OUTPUT);
  pinMode(pin[5], OUTPUT);
  
  setPinsTo(LOW); // Set all pins to LOW

  // Initialize our queues
  outputQ = newQueue(256);
  morseQ  = newQueue(24);
}

boolean outputChar(char c) {
  return Qpush(outputQ, c);
}

void outputString(char *str) {
  // Put this string into the outputQ
  for (int i=0; i < strlen(str); i++) {
    outputChar(str[i]);
  }
}


unsigned long outputInterval = 6000 / cpm; // unit of time for each bit (in milliseconds)
unsigned long previousOutputMillis = 0; // next millisecond value to stop at

char async_output_buffer[24];
prog_char morseStringSpace[] PROGMEM = "0000000";
prog_char morseStringA[] PROGMEM = "10111";
prog_char morseStringB[] PROGMEM = "111010101";
prog_char morseStringC[] PROGMEM = "11101011101";
prog_char morseStringD[] PROGMEM = "1110101";
prog_char morseStringE[] PROGMEM = "1";
prog_char morseStringF[] PROGMEM = "101011101";
prog_char morseStringG[] PROGMEM = "111011101";
prog_char morseStringH[] PROGMEM = "1010101";
prog_char morseStringI[] PROGMEM = "101";
prog_char morseStringJ[] PROGMEM = "1011101110111";
prog_char morseStringK[] PROGMEM = "111010111";
prog_char morseStringL[] PROGMEM = "101110101";
prog_char morseStringM[] PROGMEM = "1110111";
prog_char morseStringN[] PROGMEM = "11101";
prog_char morseStringO[] PROGMEM = "11101110111";
prog_char morseStringP[] PROGMEM = "10111011101";
prog_char morseStringQ[] PROGMEM = "1110111010111";
prog_char morseStringR[] PROGMEM = "1011101";
prog_char morseStringS[] PROGMEM = "10101";
prog_char morseStringT[] PROGMEM = "111";
prog_char morseStringU[] PROGMEM = "1010111";
prog_char morseStringV[] PROGMEM = "101010111";
prog_char morseStringW[] PROGMEM = "101110111";
prog_char morseStringX[] PROGMEM = "11101010111";
prog_char morseStringY[] PROGMEM = "1110101110111";
prog_char morseStringZ[] PROGMEM = "11101110101";
prog_char morseString0[] PROGMEM = "1110111011101110111";
prog_char morseString1[] PROGMEM = "10111011101110111";
prog_char morseString2[] PROGMEM = "101011101110111";
prog_char morseString3[] PROGMEM = "1010101110111";
prog_char morseString4[] PROGMEM = "10101010111";
prog_char morseString5[] PROGMEM = "101010101";
prog_char morseString6[] PROGMEM = "11101010101";
prog_char morseString7[] PROGMEM = "1110111010101";
prog_char morseString8[] PROGMEM = "111011101110101";
prog_char morseString9[] PROGMEM = "11101110111011101";
prog_char morseStringPeriod[] PROGMEM = "10111010111010111";
prog_char morseStringComma[] PROGMEM = "1110111010101110111";
prog_char morseStringQuestion[] PROGMEM = "101011101110101";
prog_char morseStringSingleQuote[] PROGMEM = "1011101110111011101";
prog_char morseStringExclamation[] PROGMEM = "1110101110101110111";
prog_char morseStringForwardSlash[] PROGMEM = "1110101011101";
prog_char morseStringLeftParen[] PROGMEM = "111010111011101";
prog_char morseStringRightParen[] PROGMEM = "1110101110111010111";
prog_char morseStringAmper[] PROGMEM = "10111010101";
prog_char morseStringColon[] PROGMEM = "11101110111010101";
prog_char morseStringSemicolon[] PROGMEM = "11101011101011101";
prog_char morseStringEquals[] PROGMEM = "1110101010111";
prog_char morseStringPlus[] PROGMEM = "1011101011101";
prog_char morseStringMinus[] PROGMEM = "111010101010111";
prog_char morseStringUnderscore[] PROGMEM = "10101110111010111";
prog_char morseStringDoubleQuote[] PROGMEM = "101110101011101";
prog_char morseStringDollar[] PROGMEM = "10101011101010111";
prog_char morseStringAt[] PROGMEM = "10111011101011101";
prog_char morseStringInterLetterGap[] PROGMEM = "000";
PROGMEM const char *morse_strings[] = 	   // change "string_table" name to suit
{   
  morseStringSpace,
  morseStringA, morseStringB, morseStringC, morseStringD, morseStringE, morseStringF,
  morseStringG, morseStringH, morseStringI, morseStringJ, morseStringK, morseStringL,
  morseStringM, morseStringN, morseStringO, morseStringP, morseStringQ, morseStringR,
  morseStringS, morseStringT, morseStringU, morseStringV, morseStringW, morseStringX,
  morseStringY, morseStringZ,
  morseString0, morseString1, morseString2, morseString3, morseString4,
  morseString5, morseString6, morseString7, morseString8, morseString9,
  morseStringPeriod,
  morseStringComma,
  morseStringQuestion,
  morseStringSingleQuote,
  morseStringExclamation,
  morseStringForwardSlash,
  morseStringLeftParen,
  morseStringRightParen,
  morseStringAmper,
  morseStringColon,
  morseStringSemicolon,
  morseStringEquals,
  morseStringPlus,
  morseStringMinus,
  morseStringUnderscore,
  morseStringDoubleQuote,
  morseStringDollar,
  morseStringAt,
  morseStringInterLetterGap
};


void pushMorseString(char* string) {
  char *ptr = string;
  while (*ptr != '\0') {
    if (*ptr == '1') {
      Qpush(morseQ, HIGH);
    } else {
      Qpush(morseQ, LOW);
    }
    ptr++;
  }
}

void pushMorseTrainingFactor(int t) {
  for (int i=0; i < t; i++) {
    pushMorseString("0");
  }
}

void outputRunAsync() {
  // Only run this once per time unit
  if (millis() - previousOutputMillis > outputInterval) {
    previousOutputMillis = millis(); // stop again in 1 more time unit
    
    if (Qempty(morseQ)) {
      if (!Qempty(outputQ)) {
        if (Qfront(outputQ) == ' ') {
          strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[0])));
          pushMorseString(async_output_buffer);  // push inter-word gap  
          pushMorseTrainingFactor(inter_word_training_factor);  // Push training factor
        } else {
          switch(Qfront(outputQ)) {
            case 'A': case 'a':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[1])));
              break;
            case 'B': case 'b':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[2])));
              break;
            case 'C': case 'c':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[3])));
              break;
            case 'D': case 'd':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[4])));
              break;
            case 'E': case 'e':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[5])));
              break;
            case 'F': case 'f':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[6])));
              break;
            case 'G': case 'g':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[7])));
              break;
            case 'H': case 'h':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[8])));
              break;
            case 'I': case 'i':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[9])));
              break;
            case 'J': case 'j':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[10])));
              break;
            case 'K': case 'k':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[11])));
              break;
            case 'L': case 'l':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[12])));
              break;
            case 'M': case 'm':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[13])));
              break;
            case 'N': case 'n':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[14])));
              break;
            case 'O': case 'o':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[15])));
              break;
            case 'P': case 'p':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[16])));
              break;
            case 'Q': case 'q':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[17])));
              break;
            case 'R': case 'r':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[18])));
              break;
            case 'S': case 's':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[19])));
              break;
            case 'T': case 't':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[20])));
              break;
            case 'U': case 'u':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[21])));
              break;
            case 'V': case 'v':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[22])));
              break;
            case 'W': case 'w':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[23])));
              break;
            case 'X': case 'x':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[24])));
              break;
            case 'Y': case 'y':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[25])));
              break;
            case 'Z': case 'z':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[26])));
              break;
            case '0':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[27])));
              break;
            case '1':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[28])));
              break;
            case '2':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[29])));
              break;
            case '3':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[30])));
              break;
            case '4':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[31])));
              break;
            case '5':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[32])));
              break;
            case '6':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[33])));
              break;
            case '7':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[34])));
              break;
            case '8':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[35])));
              break;
            case '9':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[36])));
              break;
            case '.':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[37])));
              break;
            case ',':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[38])));
              break;
            case '?':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[39])));
              break;
            case '\'':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[40])));
              break;
            case '!':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[41])));
              break;
            case '/':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[42])));
              break;
            case '(':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[43])));
              break;
            case ')':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[44])));
              break;
            case '&':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[45])));
              break;
            case ':':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[46])));
              break;
            case ';':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[47])));
              break;
            case '=':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[48])));
              break;
            case '+':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[49])));
              break;
            case '-':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[50])));
              break;
            case '_':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[51])));
              break;
            case '"':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[52])));
              break;
            case '$':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[53])));
              break;
            case '@':
              strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[54])));
              break;
          }

          // Push the string onto the morse output buffer
          pushMorseString(async_output_buffer);

          // Push the inter-letter space
          strcpy_P(async_output_buffer,  (char*)pgm_read_word(&(morse_strings[55])));
          pushMorseString(async_output_buffer);
          
          // Push training factor
          pushMorseTrainingFactor(inter_letter_training_factor);
        }
        Qpop(outputQ);
      }
    }
    // 2 if-statements so that if we pushed something above, we will begin output immediately
    if (!Qempty(morseQ)) {
      // Have something in morseQ
      setPinsTo(Qfront(morseQ));
      Qpop(morseQ);
    }
  }
}

