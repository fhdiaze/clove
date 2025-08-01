#include "../../lib/log.h"
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

int main(void) {
    FILE *file = NULL;
    errno_t err = fopen_s(&file, "./src/aoc/twenty_two/ten.txt", "r");
    if (err != 0 || file == NULL) {
        loge("Unable to find the file\n");

        return EXIT_FAILURE;
    }

    constexpr int instmaxlen = 256;
    char inst[instmaxlen];
    uint64_t cycle = 1;
    int64_t x = 1, v = 0;
    int64_t strengths = 0;
    // 240 pixels + One new line character per row + end of string
    char screen[247] = {[SCREEN_INDEX(40) + 1] = '\n',
                        [SCREEN_INDEX(80) + 1] = '\n',
                        [SCREEN_INDEX(120) + 1] = '\n',
                        [SCREEN_INDEX(160) + 1] = '\n',
                        [SCREEN_INDEX(200) + 1] = '\n',
                        [SCREEN_INDEX(240) + 1] = '\n',
                        [246] = '\0'};

    while (true) {
        logd("Starts Cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

        // Update strengths
        if (cycle % 40 == 20) {
            strengths += x * cycle;
            logt("Strength: %lld\n", strengths);
        }

        if (cycle <= 240) {
            // Do not compare signed ints with unsigned ones. x was not negative but it got to 0 so x-1 was converted to a large unsigned.
            if ((x - 1) <= (int64_t)PIXEL_COLUMN(cycle) && (int64_t)PIXEL_COLUMN(cycle) <= (x + 1)) {
                // The pixel should be drawn
                screen[SCREEN_INDEX(cycle)] = '#';
            } else {
                screen[SCREEN_INDEX(cycle)] = '.';
            }

            logd("During Cycle=%llu, x=%lld, PixelCol=%lld, ScreenInd=%lld, PixelPaintedWith=%c\n", cycle, x, PIXEL_COLUMN(cycle), SCREEN_INDEX(cycle),
                 screen[SCREEN_INDEX(cycle)]);
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
                logf("The instruction read is not valid: %s", inst);

                return EXIT_FAILURE;
            }
            inst[instlen - 1] = '\0'; // Remove trailing new line

            logt("inst=%s\n", inst);

            // Process the instruction
            if (inst[3] == 'x') {
                v = strtoll(inst + 5, NULL, 10); // Process addx: inst is a pointer :)
            } else {
                inst[0] = '\0';
            }
        } else {
            break;
        }

        logd("Ends Cycle=%llu, x=%lld, v=%lld, inst=%s\n", cycle, x, v, inst);

        cycle++;
    }

    logt("End of prog: cycle=%llu, x=%lld, v=%lld, s=%lld\n", cycle, x, v, strengths);

    fclose(file);

    logi("\n%s", screen);

    return EXIT_SUCCESS;
}
