#undef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_ALL

#include "log.h"
#include <stdio.h>
#include <stdlib.h>

static constexpr unsigned LINE_BUFFER_SIZE = 100;

typedef enum : uint8_t {
		DIVIDE,
		MULTIPLY,
} Operation;

typedef struct {
		unsigned items[256];
		size_t true_monkey_id;
		size_t false_monkey_id;
} Monkey;

int main(void)
{
		FILE *file = fopen("./data/aoc/twytwo/eleven.txt", "r");
		if (file == nullptr) {
				loge("the input puzzle 'eleven.txt' was not found");
				return EXIT_FAILURE;
		}

		char line_buffer[LINE_BUFFER_SIZE];

		while (fgets(line_buffer, sizeof(line_buffer), file) != nullptr) {
				logi("Read: %s", line_buffer);
		}

		fclose(file);
		return EXIT_SUCCESS;
}
