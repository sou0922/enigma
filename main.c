#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Enigma.h"
#include "common.h"

int main() {
    // デフォルト設定（テストのget_default_Enigmaに基づく）
    const char *rotors[] = {ROTOR_I, ROTOR_II, ROTOR_III};
    size_t rings[] = {1, 5, 3};
    size_t inits[] = {1, 5, 3};
    Enigma *enigma = new_Enigma(3, rotors, rings, inits, I_UKW_A, 5, "ECSONFIVTH");

    if (!enigma) {
        printf("Failed to create Enigma\n");
        return 1;
    }

    char input[256];
    char output[256];

    printf("Enter message to encrypt (uppercase letters only): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        free_Enigma(enigma);
        return 1;
    }

    // 改行を削除
    input[strcspn(input, "\n")] = 0;

    encrypt_Enigma(enigma, output, input);
    printf("Encrypted: %s\n", output);

    free_Enigma(enigma);
    return 0;
}