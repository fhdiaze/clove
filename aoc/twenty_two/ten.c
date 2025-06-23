#include <stdio.h>

int main()
{
    int x = 1;
    int clock = 0;
    int instruction_len = 256;
    char instruction[instruction_len];

    FILE *input_file = fopen("./aoc/twenty_two/ten.txt", "r");
    if (input_file == NULL)
    {
        printf("Unable to find the file");
        return -1;
    }

    while (fgets(instruction, instruction_len, input_file) != NULL)
    {
        clock++;
        printf("%s, %d", instruction, clock);
    }

    fclose(input_file);

    return 0;
}