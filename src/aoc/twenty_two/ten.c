#include "../../lib/log.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG

int main(void) {
    FILE *file = NULL;
    errno_t err = fopen_s(&file, "./src/aoc/twenty_two/ten.txt", "r");
    if (err != 0 || file == NULL) {
        loge("Unable to find the file\n");

        return EXIT_FAILURE;
    }

    constexpr int instmaxlen = 256;
    char inst[instmaxlen];
    uint64_t cycle = 0;
    int64_t x = 1, v = 0;
    int64_t strengths = 0;

    while (true) {
        cycle++;

        logd("During cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

        // Update strengths
        if (cycle % 40 == 20) {
            strengths += x * cycle;
            logi("Strength: %lld\n", strengths);
        }

        // Check if there is a pending instruction
        if (v != 0) {
            // Process instruction
            x += v;
            v = 0;

            logd("End cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

            continue;
        }

        // Read the instruction
        if (fgets(inst, instmaxlen, file) != NULL) {
            size_t instlen = strlen(inst);
            if (instlen == 0 || inst[instlen - 1] != '\n') {
                loge("The instruction read is not valid: %s", inst);

                return EXIT_FAILURE;
            }
            inst[instlen - 1] = '\0'; // Remove trailing new line

            // Process the instruction
            if (inst[3] == 'x') {
                v = strtoll(inst + 5, NULL, 10); // Process addx: inst is a pointer :)
            }

            logd("End cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

            continue;
        }

        break;
    }

    logi("cycle=%llu, x=%lld, v=%lld, s=%lld\n", cycle, x, v, strengths);

    fclose(file);

    return EXIT_SUCCESS;
}
