#include "Plugboard.h"
#include "common.h"

/* Your code to implement Plugboard here */
char plugboard_translate(char input, int num_pairs, const char *pairs)
{
    for (int i = 0; i < num_pairs; i++)
    {
        if (pairs[i * 2] == input)
        {
            return pairs[i * 2 + 1];
        }
        else if (pairs[i * 2 + 1] == input)
        {
            return pairs[i * 2];
        }
    }
    return input;
}