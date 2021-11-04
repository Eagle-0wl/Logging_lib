#include "log_lib.h"
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>

struct Logs *insert_node (struct Logs *log_head,struct Logs *new_node){
    new_node->next = log_head;
    log_head = new_node;
    return log_head;
}

struct Logs *create_node (char *name, char *message, char* level){
    struct Logs *new_node = (struct Logs*) malloc(sizeof(struct Logs));
    strncpy(new_node->name,name,NAMELENGTH);
    strncpy(new_node->message,message,MSGLENGTH);
    strncpy(new_node->level,level,LEVELLENGTH);
    
    return new_node;
};

struct Logs *read_logs(struct Logs *log_head)
{

    char *name = "prog1";
    char *message = "some message";
    char* level = "Info";

    // FILE *file;    
    // file=fopen(PATH,"r");               //opening file for read operation
    // if (file == NULL)                       //check if file opend
    //     {   
    //         log_writer("Error! Could not open file"); 
    //         exit(1);
    //     } 
    //  char temp_string[4096];
    // memset(temp_string, 0, sizeof temp_string);
    // while ((fgets(temp_string, 256, file)) != NULL) 
    // {
    
    log_head = insert_node (log_head, create_node (name,message,level));
   
    return log_head;
};



void log_writer(char *text, char *level, char *name)
{
    FILE *file;
    if ((file = fopen(PATH, "a")))
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(file,"%s: program(%s) %d-%02d-%02d %02d:%02d:%02d: %s\n",level, name, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, text); //Time stamp with every line of logs
        fclose(file);
    }
    else
    {
        printf("Error! Failed to open log file");
        exit(1);
    }
}