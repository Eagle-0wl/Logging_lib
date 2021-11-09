#define NAMELENGTH 50
#define MSGLENGTH 180
#define LEVELLENGTH 10
#define TIMELENGTH 20
#define PATH "/var/log/log_lib.log"

struct Logs
{
    char name[NAMELENGTH];
    char message[MSGLENGTH];
    char level[LEVELLENGTH];    //Error, Warn, Info, Debug
    char time[TIMELENGTH];
    struct Logs *next;
};
/*! \fn struct Logs *read_logs(struct Logs *log_head);
 *  \brief Function that reads logs from log file
 *  \param *log_head log list head
 *  \return log_head
 */
struct Logs *read_logs(struct Logs *log_head);

/*! \fn int log_writer(char *text, char *level, char *name)
 *  \brief Function that writes logs
 *  \param *text log message
 *  \param *level log level ("Debug","Error","Warning","Info")
 *  \param *name program name
 *  \return int 0 = success, 1 = failure
 */
int log_writer(char *text, char *level, char *name);
