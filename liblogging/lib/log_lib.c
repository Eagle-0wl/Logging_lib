#include "log_lib.h"
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>

struct Logs *insert_node (struct Logs *log_head,struct Logs *new_node){
    new_node->next = NULL;
    if(log_head == NULL)
        log_head = new_node;
    else
    {
        struct Logs *last_node = log_head;
        while(last_node->next != NULL)
        {
            last_node = last_node->next;
        }
        last_node->next = new_node;
    }
    return log_head;
}

struct Logs *create_node (char *name, char *message, char* level,char *time){
    struct Logs *new_node = (struct Logs*) malloc(sizeof(struct Logs));
    strncpy(new_node->name,name,NAMELENGTH);
    strncpy(new_node->message,message,MSGLENGTH);
    strncpy(new_node->level,level,LEVELLENGTH);
    strncpy(new_node->time,time,TIMELENGTH);
    return new_node;
};

struct Logs *read_logs(struct Logs *log_head)
{
    char name[NAMELENGTH];
    char message[MSGLENGTH];
    char level[LEVELLENGTH];
    char time[TIMELENGTH];
    char temp_string[256];
    int colon_counter;
    int counter;
    FILE *file;    
    file=fopen(PATH,"r");               //opening file for read operation
    if (file == NULL)                       //check if file opend
        {   
            printf("Error! Could not open file"); 
            exit(1);
        } 
    
    memset(temp_string, 0, sizeof temp_string);
    while ((fgets(temp_string, 256, file)) != NULL) 
    {
        counter = 0;
        colon_counter = 0;
        while (temp_string[counter] != ':'){
            strncat(level, &temp_string[counter], 1);
            counter++;
        }
        
        while (temp_string[counter] != '('){
            counter++;
        }
        counter++;
        while (temp_string[counter] != ')'){
            strncat(name, &temp_string[counter], 1);
            counter++;
        }
    
        counter+=2;
        while (colon_counter != 3){
            if (temp_string[counter] == ':'){
                colon_counter++;
                if ( colon_counter == 3)
                    break;
            }
            strncat(time, &temp_string[counter], 1);
            counter++;
        }
        counter+=2;
        while (temp_string[counter] != '\n'){
        strncat(message, &temp_string[counter], 1);    
        counter++;
        }
        
        log_head = insert_node (log_head, create_node (name,message,level,time));
        memset(time,'\0',TIMELENGTH);
        memset(level,'\0',LEVELLENGTH);
        memset(message,'\0',MSGLENGTH);
        memset(name,'\0',NAMELENGTH);
    }
    return log_head;
};

int log_writer(char *text, char *level, char *name)
{
    FILE *file;
    char *level_list[4] = {"Debug", "Error", "Warning", "Info"};
    for (int i = 0; i < 4; i++){
        if (strcmp(level,level_list[i]) == 0 ){
            if ((file = fopen(PATH, "a")))
            {
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                fprintf(file,"%.*s: program(%.*s) %d-%02d-%02d %02d:%02d:%02d: %.*s\n",LEVELLENGTH,level,NAMELENGTH, name, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,MSGLENGTH,text); //Time stamp with every line of logs
                fclose(file);
            }
            else
            {
                printf("Error! Failed to open log file");
                return 1;
            }
            return 0;
        }
    }
    return 1;
}
