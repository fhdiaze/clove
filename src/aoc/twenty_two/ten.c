#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file = NULL;
    errno_t err = fopen_s(&file, "./src/aoc/twenty_two/ten.txt", "r");
    if (err != 0 || file == NULL) {
        printf("Unable to find the file\n");

        return EXIT_FAILURE;
    }

    constexpr int instmaxlen = 256;
    char inst[instmaxlen];
    uint64_t cycle = 0;
    int64_t x = 1, v = 0;
    int64_t strengths = 0;

    while (true) {
        cycle++;

        printf("During cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

        // Update strengths
        if (cycle % 40 == 20) {
            strengths += x * cycle;
            printf("Strength: %lld\n", strengths);
        }

        // Check if there is a pending instruction
        if (v != 0) {
            // Process instruction
            x += v;
            v = 0;

            printf("End cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

            continue;
        }

        // Read the instruction
        if (fgets(inst, instmaxlen, file) != NULL) {
            size_t instlen = strlen(inst);
            if (instlen == 0 || inst[instlen - 1] != '\n') {
                printf("The instruction read is not valid: %s", inst);

                return EXIT_FAILURE;
            }
            inst[instlen - 1] = '\0'; // Remove trailing new line

            // Process the instruction
            if (inst[3] == 'x') {
                v = strtoll(inst + 5, NULL, 10); // Process addx: inst is a pointer :)
            }

            printf("End cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

            continue;
        }

        break;
    }

    printf("cycle=%llu, x=%lld, v=%lld, s=%lld\n", cycle, x, v, strengths);

    fclose(file);

    return EXIT_SUCCESS;
}
