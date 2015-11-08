#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>



void printdir(char *dir, int space){
		DIR *dp;
		struct dirent *entry;
		struct stat statbuf;
		if((dp = opendir(dir)) == NULL) {
				fprintf(stderr,"cannot open directory: %s\n", dir);
				return;
		}
		chdir(dir);
		while((entry = readdir(dp)) != NULL) {
				lstat(entry->d_name,&statbuf);
				if(S_ISDIR(statbuf.st_mode)) {
						/* Found a directory, but ignore . and .. */
						if(strcmp(".",entry->d_name) == 0 ||
						strcmp("..",entry->d_name) == 0)
						continue;
						printf("%*s%s/\n",space,"",entry->d_name);
						/* Recurse at a new indent level */
						printdir(entry->d_name,space+4);
				}
				else printf("%*s%s\n",space,"",entry->d_name);
		}
		chdir("..");
		closedir(dp);
}


/* Now we move onto the main function. */
int main(){
		printf("Directory scan of /home/leonardo/ufrj/so2:\n");
		printdir("/home/leonardo/ufrj/so2",0);
		printf("done.\n");
		exit(0);
}