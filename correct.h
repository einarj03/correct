#ifndef CORRECT_H
#define CORRECT_H

#include <cstring>
using namespace std;

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);

void text_to_binary(const char *text, char *binary);
void binary_to_text(const char *binary, char *text);

void add_error_correction(const char *data, char *corrected);

int decode(char *received, char *decoded, int errors = 0);

char parity(char *bits, const int num_bits);

#endif
