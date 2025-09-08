#include "log.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#define SCREEN_ROW(cycle) ((cycle - 1) / 40)
#define SCREEN_INDEX(cycle) ((cycle) - 1 + (SCREEN_ROW(cycle)))
#define PIXEL_COLUMN(cycle) (((cycle) - 1) % 40)

// Solve day ten problem
int main(void) {
    FILE *file = fopen("./data/aoc/twytwo/ten.txt", "r");
    if (file == nullptr) {
        LOG_ERROR("Unable to find the file\n");

        exit(EXIT_FAILURE);
    }

    constexpr int instmaxlen = 256;
    char inst[instmaxlen];
    size_t cycle = 1;
    int x = 1, v = 0;
    unsigned strengths = 0;
    // 240 pixels + One new line character per row + end of string
    char screen[247] = {[SCREEN_INDEX(40) + 1] = '\n',
                        [SCREEN_INDEX(80) + 1] = '\n',
                        [SCREEN_INDEX(120) + 1] = '\n',
                        [SCREEN_INDEX(160) + 1] = '\n',
                        [SCREEN_INDEX(200) + 1] = '\n',
                        [SCREEN_INDEX(240) + 1] = '\n',
                        [246] = '\0'};

    while (true) {
        LOG_DEBUG("Starts Cycle=%llu, x=%d, v=%d, inst=%s\n", cycle, x, v, inst);

        // Update strengths
        if (cycle % 40 == 20) {
            strengths += x * cycle;
            LOG_TRACE("Strength: %u\n", strengths);
        }

        if (cycle <= 240) {
            // Do not compare signed ints with unsigned ones. x was not negative but it got to 0 so x-1 was converted to a large unsigned.
            if ((x - 1) <= (int)PIXEL_COLUMN(cycle) && (int)PIXEL_COLUMN(cycle) <= (x + 1)) {
                // The pixel should be drawn
                screen[SCREEN_INDEX(cycle)] = '#';
            } else {
                screen[SCREEN_INDEX(cycle)] = '.';
            }

            LOG_DEBUG("During Cycle=%llu, x=%d, PixelCol=%lld, ScreenInd=%lld, PixelPaintedWith=%c\n", cycle, x, PIXEL_COLUMN(cycle), SCREEN_INDEX(cycle), screen[SCREEN_INDEX(cycle)]);
        }

        // Check if there is a pending instruction
        if (v != 0) {
            // Process instruction
            x += v;
            v = 0;
            inst[0] = '\0';
        } else if (fgets(inst, instmaxlen, file) != NULL) {
            // Read the instruction
            size_t instlen = strlen(inst);
            if (instlen == 0 || inst[instlen - 1] != '\n') {
                LOG_FATAL("The instruction read is not valid: %s", inst);

                exit(EXIT_FAILURE);
            }
            inst[instlen - 1] = '\0'; // Remove trailing new line

            LOG_TRACE("inst=%s\n", inst);

            // Process the instruction
            if (inst[3] == 'x') {
                v = atoi(inst + 5); // Process addx: inst is a pointer :)
            } else {
                inst[0] = '\0';
            }
        } else {
            break;
        }

        LOG_DEBUG("Ends Cycle=%llu, x=%d, v=%d, inst=%s\n", cycle, x, v, inst);

        cycle++;
    }

    LOG_TRACE("End of prog: cycle=%llu, x=%d, v=%d, s=%u\n", cycle, x, v, strengths);

    fclose(file);

    LOG_INFO("\n%s", screen);

    return EXIT_SUCCESS;
}
