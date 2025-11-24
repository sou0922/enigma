#include "Rotor.h"
#include "common.h"

/* Your code to implement Rotor here */
char rotor_translate_forward(char input, size_t num_rotors, const char **rotors, size_t *rings, size_t *inits)
{
    int index = input - 'A';

    for (int i = 0; i < (int)num_rotors; i++)
    {
        index = (index + inits[i] - rings[i] + 26) % 26;
        index = rotors[i][index] - 65;
        index = (index - inits[i] + rings[i] + 26) % 26;
    }

    input = 'A' + index;

    return input;
}

char rotor_translate_backward(char input, size_t num_rotors, const char **rotors, size_t *rings, size_t *inits)
{
    int index = input - 'A';
    char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = (int)num_rotors - 1; i > -1; i--)
    {
        index = (index + inits[i] - rings[i] + 26) % 26;
        index = str_index(rotors[i], alpha[index]);
        index = (index - inits[i] + rings[i] + 26) % 26;
    }
    input = 'A' + index;

    return input;
}

int str_index(const char *str, int character)
{
    char *pos = strchr(str, character);
    if (pos)
    {
        return (int)(pos - str);
    }
    else
    {
        return -1;
    }
}