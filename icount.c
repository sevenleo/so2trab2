//https://docs.python.org/2/library/stat.html
// LEONARDO NEVES E FELIPE PAIXAO
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>




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
	if ((full_path = malloc (len + NAME_MAX + 2)) == NULL)
	{
		closedir (dirp);
		return (-1);
	}
 /* copia o prefixo e acrescenta a '/' ao final */
	memcpy (full_path, path, len);
p = full_path + len; *p++ = '/'; /* deixa "p" no lugar certo! */
	while ((dp = readdir (dirp)) != NULL)
	{
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


/* ENUNCIADO
Sua tarefa é utilizar walk_dir para construir o programa icount, que informa a quantidade de
INODEs de um determinado tipo em cada um dos diretórios cujos caminhos são dados como argumentos:
icount [-rdlbc] [<dir> ...]
onde os modificadores rdlbc têm os seguintes significados:
 -r: arquivo regularesular (S_IFregulares)
 -d: diretório (S_IFDIR)
 -l: elos simbólico (S_IFLNK)
 -b: dispositivo estruturado (S_IFBLK)
 -c: dispositivo não-estruturado (S_IFCHR)
<dir>: caminho para diretório
Os modificadores são mutuamente exclusivos: no máximo um deles pode ser mencionado em uma
invocação do programa. Na ausência de modificadores, deve ser assumido -r. Na ausência de caminhos
para diretórios, deve ser assumido o diretório corrente. Utilize a função getopt da biblioteca padrão
para obter e tratar educadamente os modificadores do programa.
Exemplos:
icount /etc conta arquivos regularesulares em “/etc”
icount -d /home conta subdiretórios em “/home”
icount -b /dev conta dispositivos estruturados em “/dev”
icount conta arquivos regularesulares em “.”
*/



//funcao da ultima aula
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
						// Found a directory, but ignore . and .. 
						if(strcmp(".",entry->d_name) == 0 ||
						strcmp("..",entry->d_name) == 0)
						continue;
						printf("%*s%s/\n",space,"",entry->d_name);
						//* Recurse at a new indent level 
						printdir(entry->d_name,space+4);
				}
				else printf("%*s%s\n",space,"",entry->d_name);
		}
		chdir("..");
		closedir(dp);
}








void icount(char parametro, char *dir){
		DIR *dp;
		struct dirent *entry;
		struct stat statbuf;
		int todos=0, regulares=0, pastas=0, elos=0, estrut=0,nestrut=0,outro=0;

		if((dp = opendir(dir)) == NULL) {
				fprintf(stderr,"cannot open directory: %s\n", dir);
				return;
		} 
		else{
			printf("\nPasta: %s \n\n",dir);
		}


		chdir(dir);
		while((entry = readdir(dp)) != NULL) {

				//copia o statbuff para o entry.d_name
				lstat(entry->d_name, &statbuf);

				//ignorar pasta atual e pasta pai
 				if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) continue;

				 /*
				 -r: arquivo regularesular (S_IFregulares)
				 -d: diretório (S_IFDIR)
				 -l: elos simbólico (S_IFLNK)
				 -b: dispositivo estruturado (S_IFBLK)
				 -c: dispositivo não-estruturado (S_IFCHR)

				 https://docs.python.org/2/library/stat.html
				 S_IFMT = Return the portion of the file’s mode that describes the file type.*/
				

				if( (statbuf.st_mode & S_IFMT) == S_IFDIR) {
		 				if(parametro == 'd') printf(">>  %s \n",entry->d_name);
						todos++; pastas++;
				}
				else if( (statbuf.st_mode & S_IFMT) == S_IFLNK) {
		 				if(parametro == 'l') printf("@ %s \n",entry->d_name);
						todos++; elos++;
				}
				else if( (statbuf.st_mode & S_IFMT) == S_IFBLK) {
		 				if(parametro == 'b') printf("# %s \n",entry->d_name);
						todos++; estrut++;
				}
				else if( (statbuf.st_mode & S_IFMT) == S_IFCHR) {
		 				if(parametro == 'c') printf("* %s \n",entry->d_name);
						todos++; nestrut++;
				}
				else if( (statbuf.st_mode & S_IFMT) == S_IFREG) {
		 				if(parametro == 'r') printf(" %s \n",entry->d_name);
						todos++; regulares++;
				}
				else{
	 				//printf(" %s \n",entry->d_name);
					outro++;

				}

				 
		}
		chdir("..");
		closedir(dp);


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
			printf("O parametro desejado nao faz parte da nossa lista, veja todos os tipos conhecidos dentre os %i inodes:\n",todos);
			printf("\t( ) reg=%i\t(>>) pastas=%i\t(@) elos=%i\t\n\t(#) estrut=%i\t( *) nestrut=%i\t(_) outros=%i\n",regulares,pastas,elos,estrut,nestrut,outro);
		}
 


		

}


//executar :  icount pasta
//contar arquivos de cada tipo na pasta especificada
int main( int argc, char *argv[ ] ){
   	int cont=0;
   	char *full_path;
   	char parametro;


	if (argc == 1) {
   		parametro ='r';
   		//full_path = '';
   		full_path = ".";
   	}

	else if (argc == 2) {
   		if(argv[1][0] == '-' && argv[1][2] == NULL ) {
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

   	//printar parametros
   	//printf("Funcao: %s\n", argv[cont]);
   	//if ( argc <=1) return;
   	//else for(cont=1; cont < argc; cont++) printf("  Parametro %d:  %s\n", cont,argv[cont]);



    //PRINT DIRETORIO DO PRIMEIRO ARGUMENTO
    //printdir(argv[1],2);



   	//sem usar walk_dir
    icount(parametro,full_path);
	
    return 0;

}