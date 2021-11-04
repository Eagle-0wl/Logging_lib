#include <stdio.h>
#include <signal.h>
#include <memory.h>
#include <stdlib.h>
#include <syslog.h>
#include "log_lib.h"

/* Usage text */
void usage() {
    printf ("This program used to read logs for all or one specific program\n\n");
    printf ("Usage: log_reading [Flag] [argument]\n");
    printf ("Flags: -P, --program [Program_name] prints log only for specific program\n");
    printf ("       -H, --help\n");
    exit(1);
}
/* Get and process command line options */
char *getopts(int argc, char** argv)
{   
    if (argc == 1){
        return NULL;
    }
    if (argc == 2){
        usage();
    }
    if (argc > 2){
        if (strcmp(argv[1], "--program") == 0  || strcmp(argv[1], "-P")  == 0){
            return argv[2];
        }
        else {
            usage();
        }
    }
}
void log_print (struct Logs *ptr, char *prog_name){
    while(ptr != NULL) {                        //through whole list
        if (prog_name == NULL){
            printf ("%s: program(%s) %s\n",ptr->level, ptr->name, ptr->message);          //print node elements
        }
        else if (strcmp(ptr->name,prog_name) == 0 ){       //check if element with that name exist  
            printf ("%s: program(%s) %s\n",ptr->level, ptr->name, ptr->message);          //print node elements
        }
        ptr = ptr->next;
    }
}
/* Main program */
int main(int argc, char *argv[])
{
    /* get argument options */
    struct Logs *log_list = NULL;
    char* prog_name;
    prog_name = getopts(argc, argv);
    log_list = read_logs(log_list);
    log_print(log_list,prog_name);
    


cleanUp:

    return 0;
}