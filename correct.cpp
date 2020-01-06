#include <iostream>

#include "correct.h"

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

/* converts a binary string representation into a character */
char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(const char *text, char *binary) {
  if (text[0] == '\0')
    return;

  ascii_to_binary(text[0], binary);
  text_to_binary(text+1, binary+8);
}

void binary_to_text(const char *binary, char *text) {
  if (binary[0] == '\0') {
    text[0] = '\0';
    return;
  }

  text[0] = binary_to_ascii(binary);
  binary_to_text(binary+8, text+1);
}

void add_error_correction(const char *data, char *corrected) {
  if (data[0] == '\0') {
    corrected[0] = '\0';
    return;
  }

  char bits1[4] = {data[0], data[1], data[3]};
  char bits2[4] = {data[0], data[2], data[3]};
  char bits3[4] = {data[1], data[2], data[3]};

  char c1 = parity(bits1, 3);
  char c2 = parity(bits2, 3);
  char c3 = parity(bits3, 3);

  corrected[0] = c1;
  corrected[1] = c2;
  corrected[2] = data[0];
  corrected[3] = c3;
  corrected[4] = data[1];
  corrected[5] = data[2];
  corrected[6] = data[3];

  add_error_correction(data+4, corrected+7);
}

int decode(char *received, char *decoded, int errors) {
  if (received[0] == '\0') {
    decoded[0] = '\0';
    return errors;
  }

  char bits1[5] = {received[3], received[4], received[5], received[6]};
  char bits2[5] = {received[1], received[2], received[5], received[6]};
  char bits3[5] = {received[0], received[2], received[4], received[6]};

  char p1 = parity(bits1, 4);
  char p2 = parity(bits2, 4);
  char p3 = parity(bits3, 4);

  int err_i = -1;
  if (p1 == '1')
    err_i += 4;
  
  if (p2 == '1')
    err_i += 2;

  if (p3 == '1')
    err_i += 1;

  if (err_i >= 0) {
    ++errors;
    received[err_i] = (received[err_i] == '0' ? '1' : '0');
  }

  decoded[0] = received[2];
  decoded[1] = received[4];
  decoded[2] = received[5];
  decoded[3] = received[6];

  return decode(received+7, decoded+4, errors);
}

char parity(char *bits, const int num_bits) {
  int total = 0;
  for (int i = 0; i < num_bits; ++i)
    total += (int) (bits[i] - '0');
  
  return (char) (total % 2) + '0';
}