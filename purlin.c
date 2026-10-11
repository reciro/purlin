#include "thread.h"
#include "argparse.h"

#ifndef DEFINE_FUNCS
void* run_program(void* arg);
#endif

int main(int argc, char** argv) {
    // Parse args
    // {threads, cores, binary_path}
    char **parsed_args = parse_args(argc, argv);

    char num_threads[4];
    snprintf(num_threads, sizeof(num_threads), "%d", MIN(atoi(parsed_args[0]), get_hardware_threads()));

    char cores[4];
    snprintf(cores, sizeof(cores), "%d", MIN(atoi(parsed_args[1]), get_hardware_cores()));

    char path[STR_LEN_MAX];
    snprintf(path, sizeof(path), "%s", parsed_args[2]);
    
    char *program_args[] = {num_threads, cores, path};

    run_multithreaded(run_program, program_args);
    
    goto release_mem;

    return 0;

#if 1
release_mem:
    for (int i = 0 ; i < POSSIBLE_ARGS; i++) {
        free(parsed_args[i]);
    }

    free(parsed_args);
#endif
}


void* run_program(void* _) {

    return NULL;
}
