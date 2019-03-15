#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>


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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
	sleep(3);
	struct group *gr;
        struct passwd *pw;

	DIR *sdir;
	struct dirent *sdirent;

        char fname[255][255];
	char pname[255][255];
	char elen[10];
	strcpy(elen,"elen.ku");
	int i=0,k=0;
	char path[255];

	sdir = opendir("/home/sea/Documents/Sisop/Modul_2/hatiku");
	if(sdir != NULL){
		while ((sdirent=readdir(sdir)) != NULL){
			strcpy(path,"/home/sea/Documents/Sisop/Modul_2/hatiku/");
			strcpy(fname[i],sdirent->d_name);
			if(strcmp(fname[i],"elen.ku")==0){
				struct stat info;
				strcpy(pname[k],fname[i]);
				strcat(path,pname[k]);
				chmod(path, S_IRWXU|S_IRWXG|S_IRWXO);
				stat(path, &info);

				uid_t uid=info.st_uid;
				gid_t gid=info.st_gid;
				gr = getgrgid(gid);
				pw = getpwuid(uid);
				printf ("%s : %s , %s\n",pname[i],gr->gr_name,pw->pw_name);


				if(strcmp(gr->gr_name,"www-data")==0 && strcmp(pw->pw_name,"www-data")==0) remove (path);
				memset(path, 0,sizeof path);
				k++;
			}
			i++;
		}
	}
	closedir(sdir);
  }
}

