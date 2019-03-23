#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int main()
{
	char *argv[3]= {"killall","soal5",NULL};
	execv ("/usr/bin/killall",argv);
}
