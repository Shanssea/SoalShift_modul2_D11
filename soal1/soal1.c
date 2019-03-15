#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

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
    DIR *sdir;
    struct dirent *sdirent;

    char fname[256][256];
    const char *xname;
    char pname[256][256];
    char path[255];
    char spath[255];
    char dpath[255];
    char fpath[255];
    char lname[255];
    int ren, i=0, k=0;

    strcpy(lname, "_grey.png");
    strcpy(path, "/home/sea/Documents/Sisop/Modul_2/Media");
    sdir = opendir(path);
    if (sdir != NULL)
    {
        while ((sdirent=readdir(sdir))!=NULL)
        {
	    strcpy(fname[i],sdirent->d_name);
	    xname = strrchr(sdirent->d_name,'.');
	    if (strcmp(xname,".png")==0)
	    {
		strcpy(spath, "Media/");
    		strcpy(dpath, "gambar/");
		strcpy(pname[k],fname[i]);
		delext(pname[k]);
		strcat(pname[k],lname);
		strcat(spath,fname[i]);
	        strcat(dpath,pname[k]);

		ren = rename(spath,dpath);
		printf ("%d. %s --> %s\n",k , sdirent->d_name, pname[k]);
		if (ren != 0) perror("Error");

		memset(spath, 0, sizeof spath);
		memset(dpath, 0, sizeof dpath);
		k++;
		printf ("%d\n",k);
	    }
	    i++;
	    printf("%d\n",i);
        }
        closedir(sdir);
    }
  }
}


