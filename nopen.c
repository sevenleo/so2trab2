#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

extern int isopen (int fd);

int main (void){
	 int nopen, fd;

	 //qts arquivos tem em /proc/ getpid() /fd/ 
	 //system( ls | wc -l /proc/ getpid() /fd/ );

	 for (nopen = fd = 0; fd < getdtablesize (); fd++) {
	 	if (fd ==0 || fd ==1 || fd ==2 ) nopen++;
		else if (isopen (fd)) nopen++;
	 }

	 printf ("Existem %d descritores abertos\n", nopen);
	 return (0);

} /* end main */ 



int isopen (int fd){
	char buffer[1];
	struct stat statbuf;		

	
	int open =fstat(fd,&statbuf);
	
	//printf("%i\n",open);
	//printf("read = %i\n", a);
	
	//printf ("ErrNO: %i\n",errno);
	//printf ("Erro: %s\n",strerror(errno));
	
	if (open !=0) { 
		//printf("Arquivo %i nao usado\n",fd);
		return 0;
	}
	else {
		//printf("Arquivo %i esta em usado\n",fd);
		return 1;
	}



	// ============= mode 2 

	// int a = read(fd, buffer, 1);
	// if (errno == 9) { 
	// 	//printf("Arquivo %i nao usado\n",fd);
	// 	return 0;
	// }
	// else if (errno == 0){
	// 	//printf("Arquivo %i esta em usado\n",fd);
	// 	return 1;
	// }


}


