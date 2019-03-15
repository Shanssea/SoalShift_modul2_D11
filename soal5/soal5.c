#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <locale.h>

void delext (char *name)
{
    char *back = name + strlen(name);
    while (back > name && *back != '.') --back;
    if (back > name) *back = '\0';
}

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    FILE *fr, *fw;
	time_t times;
	struct tm *timeptr;
	char buf[100];
	char waktu[255];

	char path[255];
	char ext[10];
	char pathh[255];
	char ang[50];
	char C;

	int t=1800;

	strcpy(path,"/home/sea/Documents/Sisop/Modul_2/");

	sleep(t);
	setlocale(LC_ALL,"/QSYS.LIB/EN_US.LOCALE");
	times = time(NULL);
	timeptr = localtime(&times);
	strftime(buf,sizeof(buf), "%d:%m:%Y-%H:%M", timeptr);
	mkdir(buf,0777);
	strcat(path,buf);
	strcat(path,"/");
	


	int x=60;
	while(1){
		fr = fopen("/var/log/syslog","r");
		char baru[255]="";
		sprintf(baru,"log%d.log",x);
		strcpy(pathh,path);
		strcat(pathh,baru);
		fw = fopen(pathh,"w+");


		C = fgetc(fr);
		while(C != EOF)
		{
			fputc(C, fw);
			C = fgetc(fr);
		}
		x++;
		fclose(fr);
		fclose(fw);

		sleep(1);
		if(x>30) break;

	}

	memset (pathh, 0 ,sizeof (pathh));
  
}
}
