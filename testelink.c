// LEONARDO NEVES 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>


int main( int argc, char *argv[ ] ){

		struct stat linkbuf; 
		struct stat nebuf;

		char *link= "/dev/stderr"; //link
		char *nestruturado="/dev/tty1"; //nestruturado = nao estruturado

		stat(link, &linkbuf);
		stat(nestruturado, &nebuf);
		printf("\n--------------------------------------------------\n");
		//teste o caminho do diretorio
		printf("- %s   ::",nestruturado);
		printf("  um nao-estruturado? %s \n", (S_ISCHR(nebuf.st_mode)) ? "(SIM)" : "(NAO)");
		//teste2
		if( (nebuf.st_mode & S_IFMT) == S_IFCHR) 
 				printf("Encontrei nestruturado no arquivo %s \n\n",nestruturado);
		else printf("Nao encontrei um nestruturado\n\n");

		//teste o caminho de link
		printf("- %s   ::",link);
		printf(" um link? %s\n", (S_ISLNK(linkbuf.st_mode)) ? "(SIM)" : "(NAO)");
		//teste2
		if( (linkbuf.st_mode & S_IFMT) == S_IFLNK) 
 				printf("Encontrei um link no arquivo %s \n\n",link);
		else printf("Nao encontrei um link\n\n");

    return 0;

}