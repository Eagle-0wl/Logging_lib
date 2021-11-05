#include <stdio.h>
#include <signal.h>
#include <memory.h>
#include <stdlib.h>
#include <syslog.h>

#include "log_lib.h"

volatile int interrupt = 0;

void sigHandler(int signo) {
    signal(SIGINT, NULL);
    interrupt = 1;
}

/* Main program */
int main(int argc, char *argv[])
{   
    char *msgOut;
    int counter = 1;
    
    
    // struct sigaction action;
    // memset(&action, 0, sizeof(struct sigaction));
    // /* Set signal handlers */
    // signal(SIGINT, sigHandler);
    // signal(SIGTERM, sigHandler);
    // sigaction(SIGTERM, &action, NULL);

    while (1){
        asprintf(&msgOut, "Count: %d", counter++);
        log_writer(msgOut, "Warr", "Program2");
        sleep (3);
    }

    return 0;
}