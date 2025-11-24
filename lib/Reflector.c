#include "Reflector.h"
#include "common.h"
#include "stdlib.h"
#include "string.h"

/* Your code to implement Reflector here */
char reflector_translate(char input, const char *reflector)
{
    if (input >= 'A' && input <= 'Z')
    {
        int index = input - 'A';
        return reflector[index];
    }

    return input;
}