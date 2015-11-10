//https://docs.python.org/2/library/stat.html
// LEONARDO NEVES E FELIPE PAIXAO
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int todos=0, regulares=0, pastas=0, elos=0, estrut=0,nestrut=0,outro=0;
char parametro;
void icount2(char *inode);
int walk_dir (const char *path, void (*func) (const char *));


//========================================== main



//executar :  icount -rdbcl pasta
//contar arquivos de cada tipo na pasta especificada
int main( int argc, char *argv[ ] ){
   	int cont=0;
   	char *full_path;


	if (argc == 1) {
   		parametro ='r';
   		//full_path = '';
   		full_path = ".";
   	}

	else if (argc == 2) {
   		if(argv[1][0] == '-' && argv[1][2] == '\0' ) {
   			parametro = argv[1][1];
   			full_path = ".";
   		}

   		else {
   			parametro ='r';
   			full_path =  argv[1];
   		}
   	}


   	else if (argc == 3 && argv[1][0] == '-') {
   			parametro = argv[1][1];
   			full_path = argv[2];
   	}
   	
   	 	
   	else { 
   		printf("Os parametros foram inseridos da forma errada \ntente: icount [-rdlbc] [<dir> ...]\n"); 
   		return;
   	}




 	//usando walk_dir
	walk_dir(full_path, icount2);


	printf("____________\n");
	switch ( parametro )  {
		case 'r' :
		printf ("regulares = %i\n",regulares);
		break;

		case 'd' :
		printf ("Diretorios = %i\n",pastas);
		break;

		case 'l' :
		printf ("elos = %i\n",elos);
		break;

		case 'b' :
		printf ("Estruturados = %i\n",estrut);
		break;

		case 'c' :
		printf ("Nao estruturados = %i\n",nestrut);
		break;

		default :
		printf("O parametro desejado nao faz parte da nossa lista, veja todos os tipos conhecidos dentre os _%i_ inodes:\n",todos);
		printf("\t( ) reg=%i\t(>>) pastas=%i\t\t(@) elos=%i\t\n\t(#) estrut=%i\t( *) nestrut=%i\t(_) outros=%i\n",regulares,pastas,elos,estrut,nestrut,outro);
	}
	
    return 0;

}




//========================== auxiliares =====================
void icount2(char *inode){
		DIR *dp;
		struct dirent *entry;
		struct stat statbuf;		
		
		//copia o statbuff para o entry.d_name
		stat(inode, &statbuf);

		//ignorar pasta atual e pasta pai
		if(strcmp(".",inode) == 0 || strcmp("..",inode) == 0) return ;

		 /*
		 -r: arquivo regularesular (S_IFregulares)
		 -d: diretório (S_IFDIR)
		 -l: elos simbólico (S_IFLNK)
		 -b: dispositivo estruturado (S_IFBLK)
		 -c: dispositivo não-estruturado (S_IFCHR)

		 https://docs.python.org/2/library/stat.html
		 S_IFMT = Return the portion of the file’s mode that describes the file type.*/
		

		if( (statbuf.st_mode & S_IFMT) == S_IFDIR) {
 				if(parametro == 'd') printf(">>  %s \n",inode);
				todos++; pastas++;
		}
		else if( (statbuf.st_mode & S_IFMT) == S_IFLNK) {
 				if(parametro == 'l') printf("@ %s \n",inode);
				todos++; elos++;
		}
		else if( (statbuf.st_mode & S_IFMT) == S_IFBLK) {
 				if(parametro == 'b') printf("# %s \n",inode);
				todos++; estrut++;
		}
		else if( (statbuf.st_mode & S_IFMT) == S_IFCHR) {
 				if(parametro == 'c') printf("* %s \n",inode);
				todos++; nestrut++;
		}
		else if( (statbuf.st_mode & S_IFMT) == S_IFREG) {
 				if(parametro == 'r') printf(" %s \n",inode);
				todos++; regulares++;
		}
		else{
				//printf(" %s \n",inode);
			outro++;

		}
}



int walk_dir (const char *path, void (*func) (const char *)){
	DIR *dirp;
	struct dirent *dp;
	char *p, *full_path;
	int len;
	
 /* abre o diretório */
	if ((dirp = opendir (path)) == NULL)
		return (-1);
	len = strlen (path);
	
 /* aloca uma área na qual, garantidamente, o caminho caberá */
	if ((full_path = malloc (len + NAME_MAX + 2)) == NULL)	{
		closedir (dirp);
		return (-1);
	}
 /* copia o prefixo e acrescenta a '/' ao final */
	memcpy (full_path, path, len);
		
	p = full_path + len; *p++ = '/'; /* deixa "p" no lugar certo! */
	while ((dp = readdir (dirp)) != NULL)	{
 /* ignora as entradas "." e ".." */
		if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0)
			continue;
		strcpy (p, dp->d_name);
 /* "full_path" armazena o caminho */
		(*func) (full_path);
	}
	free (full_path);
	closedir (dirp);
	return (0);
} /* end walk_dir */