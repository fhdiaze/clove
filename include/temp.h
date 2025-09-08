typedef int logger_function(char const *, ...);

extern logger_function *logger;

enum logs { log_pri, log_ign, log_ver, log_num };
