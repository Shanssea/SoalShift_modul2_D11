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

int main(){
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

	  if ((chdir("/home/sea/Documents/Sisop/Modul_2/makanan")) < 0) {
	    exit(EXIT_FAILURE);
	  }

	  close(STDIN_FILENO);
	  close(STDOUT_FILENO);
	  close(STDERR_FILENO);	
	  
	  while (1){

		FILE *f;
        	struct stat filestat;
		char fp[255]="makan_enak.txt";
		char baru[255];
		long int act,ctm,sub;
		
        	stat(fp,&filestat);
		time_t act = filestat.st_atime;
		ctm = time(NULL);
		sub = ctm - act;	
		
		int i=1;
		if(sub<30){
				
			while(1){
				sprintf(baru,"Makan_sehat%d.txt",i);
				if(fopen(baru,"r")==0){
					f=fopen(baru,"w+");
					break;
				}	
				i++;
			}
		
		}
		sleep (5);

	   }
	
	
}

