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
#include <dirent.h>
#include <sys/wait.h>

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

int main() {
  pid_t child_id;
  int fd[2];
  int i=0,k=0;
  int status;

  DIR *sdir;
  struct dirent *sdirent;

  FILE *f;

  char fname[255][255];
  char pname[255];
  const char *xname;
  
	
  if(pipe(fd)==-1) die("pipe");

  child_id = fork();

  if (child_id == 0) {
  	pid_t grchild_id;
  	

  	grchild_id = fork();

  	if (grchild_id == 0){
		
		pid_t grgrchild_id;
		grgrchild_id = fork();

		if(grgrchild_id == 0){
			//this is grand grand child
			char *argv[3]={"unzip","campur2.zip",NULL};
			execv("/usr/bin/unzip",argv);
		}else{
			//this is grandchild
			wait(NULL);
	
			char *argv[5]={"touch","daftar.txt",NULL};
			execv("/usr/bin/touch",argv);
			die("execv");
						
		}
    	}else{
		//this is child
		wait(NULL);

		close(fd[0]);
		
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		char *argv[5]={"find","campur2/","-name","*.txt",NULL};
		execv("/usr/bin/find",argv);
		
	}


  } else {
  	// this is parent
	wait(NULL);

	close(fd[1]);
	read(fd[0], pname, sizeof(pname));
	close(fd[0]);
	f = fopen("daftar.txt","w");
	fputs(pname,f);
	fclose(f);
	
  }
   return 0;
}
