#define NAMELENGTH 50
#define MSGLENGTH 100
#define LEVELLENGTH 10
#define PATH "/home/darius/Desktop/Logging/program_logs.log"

struct Logs
{
    char name[NAMELENGTH];
    char message[MSGLENGTH];
    char level[LEVELLENGTH];    //Error, Warn, Info, Debug
    struct Logs *next;
};

struct Logs *read_logs(struct Logs *log_head);