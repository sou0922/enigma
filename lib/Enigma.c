#include "Enigma.h"
#include "EnigmaImpl.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

/* Your code to implement Enigma here */
Enigma *new_Enigma(size_t num_rotors, const char **rotors, size_t *rings, size_t *inits, const char *reflector, size_t num_pairs, const char *pairs)
{
    struct Enigma *enigma = malloc(sizeof(struct Enigma));
    if (enigma == NULL)
    {
        return NULL;
    }
    enigma->num_rotors = num_rotors;

    enigma->rotors = malloc(num_rotors * sizeof(char *));
    for (size_t i = 0; i < num_rotors; i++)
    {
        enigma->rotors[i] = strdup(rotors[i]);
    }

    enigma->rings = malloc(num_rotors * sizeof(size_t));
    memcpy(enigma->rings, rings, num_rotors * sizeof(size_t));

    enigma->inits = malloc(num_rotors * sizeof(size_t));
    memcpy(enigma->inits, inits, num_rotors * sizeof(size_t));

    enigma->reflector = reflector;
    enigma->num_pairs = num_pairs;
    enigma->pairs = pairs;
    return enigma;
}

char *encrypt_Enigma(Enigma *self, char *dst, const char *src)
{
    int len = 0;
    if (self->pairs != NULL)
    {
        len = strlen(self->pairs);
    }
    if ((int)self->num_pairs != (len / 2))
    {
        return NULL;
    }

    char *start = dst;
    for (char *p = (char *)src; *p != '\0'; p++, dst++)
    {
        if (*p == ' ')
        {
            *dst = ' ';
            continue;
        }

        tick_Enigma(self);                                                                               // 1tick
        *dst = plugboard_translate(*p, self->num_pairs, self->pairs);                                    // plugboard
        *dst = rotor_translate_forward(*dst, self->num_rotors, self->rotors, self->rings, self->inits);  // forward
        *dst = reflector_translate(*dst, self->reflector);                                               // reflector
        *dst = rotor_translate_backward(*dst, self->num_rotors, self->rotors, self->rings, self->inits); // backward
        *dst = plugboard_translate(*dst, self->num_pairs, self->pairs);                                  // plugboard
    }

    *dst = '\0';
    return start;
}

void reset_rotor_Enigma(Enigma *self, size_t *new_setting)
{
    memcpy(self->inits, new_setting, self->num_rotors * sizeof(size_t));
}

void free_Enigma(Enigma *self)
{
    free(self->inits); // free inits
    free(self->rings); // free rings

    for (size_t i = 0; i < self->num_rotors; i++)
    {
        free((char *)self->rotors[i]); // free rotors[i]
    }
    free(self->rotors); // free rotors

    free(self); // free enigma
}

void get_setting_Enigma(Enigma *self, char *ret)
{
    for (int i = 0; i < (int)self->num_rotors; i++)
    {
        ret[i] = 'A' + self->inits[i];
    }
    ret[self->num_rotors] = '\0';
}

void tick_Enigma(Enigma *self)
{
    if (self->num_rotors == 0)
    {
        return;
    }
    char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *notches[self->num_rotors];
    int flag[self->num_rotors + 1];
    char *comma = ",";

    // build notch
    for (int i = 0; i < (int)self->num_rotors; i++)
    {
        char *delimiter = strchr(self->rotors[i], comma[0]);
        char *substring = delimiter + 1;
        notches[i] = substring;
        flag[i] = 0;
    }

    // rotor1
    if (self->num_rotors > 0)
    {
        if (str_index(notches[0], alpha[self->inits[0]]) != -1)
        {
            flag[0] = 1;
        }
        self->inits[0] = (self->inits[0] + 1) % 26;
    }

    // rotor2,3,4...
    int limit = (int)self->num_rotors - 1;
    if (limit == 3)
    {
        limit--;
    }
    for (int i = 0; i < limit; i++)
    {
        if ((flag[i] == 1) || (i + 1 != limit && str_index(notches[i + 1], alpha[self->inits[i + 1]]) != -1))
        {
            if (str_index(notches[i + 1], alpha[self->inits[i + 1]]) != -1)
            {
                flag[i + 1] = 1;
            }
            self->inits[i + 1] = (self->inits[i + 1] + 1) % 26;
        }
    }
}

void tick_n_Enigma(Enigma *self, size_t n)
{
    for (int i = 0; i < (int)n; i++)
    {
        tick_Enigma(self);
    }
}