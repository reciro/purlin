#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include <stdlib.h>

#ifndef DEFINE_CONST
#define HELP_PRINT \
"Purlin: Testing programs in singular threaded/multithreaded and multiprocessed environments\n" \
"   Example usage: ./main <path to binary> --threads=<n> --cores=<m>\n" \
"           Cores value: 1 to hardware amount\n" \
"           Threads value: 1 to hardware amount\n"
#define MISSING_ARG \
"Missing required arguments: \n" \
"       --threads (-t) x\n" \
"       --cores (-c)\n y" \
"       --threads (-t)\n z" \
"See ./purlin -h for more information"
#define ARG1v1 "--threads=" 
#define ARG1v2 "-t="
#define ARG2v1 "--cores="
#define ARG2v2 "-c="
#define STR_LEN_MAX 256
#define POSSIBLE_ARGS 2
#endif

typedef enum {
    BINARY_PATH_ARG,
    THREADS_ARG,
    CORES_ARG,
} ARG_TYPES;

char **parse_args(int argc, char** argv);
void arg_extraction(char* arg, ull* arg_value, ARG_TYPES arg_type);

char **parse_args(int argc, char** argv) {
    printf("\nNumber of args: %d\n", argc); // TODO: Print out the args
    char **parsed_args = (char**)malloc(sizeof (char*) * POSSIBLE_ARGS);
    ull thread = INT_MAX;
    ull core = INT_MAX;
    switch (argc) {
        case 1: 
            goto quit;
            break;
        case 2:
            if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
                printf(HELP_PRINT);
            }
            else {
                // char msg[STR_LEN_MAX];
                // snprintf(msg, sizeof(msg), "Invalid argument: %s\n", argv[1]);
                log_print(ERROR_LEVEL, MISSING_ARG);
            }
            goto quit;
            break;
        quit:
            free(parsed_args);
            exit(-1);
        default:
            for (int i = 1; i < argc; i++) {
                // thread arg
                if (strncmp(argv[i], ARG1v1, sizeof ARG1v1 - 2) == 0 ||
                    strncmp(argv[i], ARG1v2, sizeof ARG1v2 - 2) == 0) {
                    arg_extraction(argv[i], &thread, THREADS_ARG);
                }
                // core arg
                else if (strncmp(argv[i], ARG2v1, sizeof ARG2v1 - 2) == 0 ||
                         strncmp(argv[i], ARG2v2, sizeof ARG2v2 - 2) == 0) {
                    arg_extraction(argv[i], &core, CORES_ARG);
                }
                else {
                    char msg[STR_LEN_MAX];
                    snprintf(msg, sizeof(msg), "Invalid argument: %s\n", argv[i]);
                    log_print(ERROR_LEVEL, msg);
                    exit(EXIT_FAILURE);
                }
            }

            parsed_args[0] = (char*)malloc(STR_LEN_MAX);
            parsed_args[1] = (char*)malloc(STR_LEN_MAX);
            snprintf(parsed_args[0], STR_LEN_MAX, "%lld", thread);
            snprintf(parsed_args[1], STR_LEN_MAX, "%lld", core);
            break;
    }
    return parsed_args;
}

void arg_extraction(char* arg, ull* arg_value, ARG_TYPES arg_type) {
    const char *equals = strchr(arg, '=');
    if (equals == NULL || equals[1] == '\0') {
        if (arg_type == THREADS_ARG) log_print(ERROR_LEVEL, "Missing value for thread argument");
        else if (arg_type == CORES_ARG) log_print(ERROR_LEVEL, "Missing value for core argument");
        exit(EXIT_FAILURE);
    }

    const char *value = equals + 1;
    if (value == NULL) {
        if (arg_type == THREADS_ARG) log_print(ERROR_LEVEL, "Missing value for thread argument");
        else if (arg_type == CORES_ARG) log_print(ERROR_LEVEL, "Missing value for core argument");
        exit(EXIT_FAILURE);
    }

    if (*arg_value == INT_MAX) {
        char *end;
        errno = 0;
        long parsed = strtol(value, &end, 0);

        if (errno == ERANGE || end == value || *end != '\0' ||
            parsed <= INT_MIN || parsed >= INT_MAX) {
            if (arg_type == THREADS_ARG) log_print(ERROR_LEVEL, "Error trying to convert thread argument");
            else if (arg_type == CORES_ARG) log_print(ERROR_LEVEL, "Error trying to convert core argument");
            exit(EXIT_FAILURE);
        }
        *arg_value = (int)parsed;
    } else {
        char msg[STR_LEN_MAX];
        if (arg_type == THREADS_ARG) snprintf(msg, sizeof(msg),
                 "Duplicate argument for thread: %s ... not setting\n", arg);
        else if (arg_type == CORES_ARG) snprintf(msg, sizeof(msg),
                 "Duplicate argument for core: %s ... not setting\n", arg);
        log_print(WARNING_LEVEL, msg);
    }

}

#endif
