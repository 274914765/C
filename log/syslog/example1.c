#include <syslog.h>

int main(int argc, char **argv)
{
    openlog("MyMsgMARK", LOG_CONS | LOG_PID, 0);
    syslog(LOG_INFO,
           "This is a syslog test message generated by program '%s'\n",
           argv[0]);
    closelog();
    return 0;
}
