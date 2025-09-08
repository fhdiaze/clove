#include <stdio.h>
#include <stdlib.h>
#include "temp.h"

extern int logger_verbose(const char *, ...);
static int logger_ignore(const char *, ...) { return 0; }
logger_function *logger = logger_ignore;
static logger_function *loggers = {
    [log_pri] = printf,
    [log_ign] = logger_ignore,
    [log_ver] = logger_verbose,
};

int main(void) {
    unsigned uint = -4;
    signed sint = -4;

    printf("unsigned=%u\n", uint);
    printf("signed=%d\n", sint);

    return EXIT_SUCCESS;
}
