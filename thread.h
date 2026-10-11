#ifndef THREAD_H
#define THREAD_H
#include "common.h" 
#include <stdio.h>

// Gets the number of logical threads
int get_hardware_threads() {
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

int get_hardware_cores() {
#ifdef _WIN32
    return 8;
#else
    return 8;
#endif
}

int run_multithreaded(void* (*run_program)(void *), void* argument) {
    // NOTE: This is fine :)
    char **args = argument;

    int hardware_threads = atoi(args[0]);
    printf("Running with %d threads\n", hardware_threads);
    printf("Running with %s cores\n", args[1]);
    pthread_t threads[hardware_threads];



    for (int i = 0; i < hardware_threads; i++) {
        pthread_t thread;
        args[2] = (char*)malloc(8 * sizeof(char));
        snprintf(args[2], 8, "%d", i); // TODO: Use sizeof(args[2])
        if (pthread_create(&thread, NULL, run_program, args) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }

        threads[i] = thread;
    }


    for (int i = 0; i < hardware_threads; i++) { 
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}

#endif
