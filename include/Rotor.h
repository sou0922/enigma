#ifndef ROTOR_H
#define ROTOR_H

#include "common.h"
#include <string.h>
#include <stdlib.h>

/* Your definition of Rotor */
char rotor_translate_forward(char input, size_t num_rotors, const char **rotors, size_t *rings, size_t *inits);
char rotor_translate_backward(char input, size_t num_rotors, const char **rotors, size_t *rings, size_t *inits);
int str_index(const char *str, int character);

#endif