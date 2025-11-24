#ifndef ENIGMA_IMPL_H
#define ENIGMA_IMPL_H

#include "Enigma.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

struct Enigma
{
  /* Your implementation of Enigma */
  size_t num_rotors;
  const char **rotors;
  size_t *rings;
  size_t *inits;
  const char *reflector;
  size_t num_pairs;
  const char *pairs;
};

#endif