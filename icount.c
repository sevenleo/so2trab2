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
 -r: arquivo regular (S_IFREG)
 -d: diretório (S_IFDIR)
 -l: elo simbólico (S_IFLNK)
 -b: dispositivo estruturado (S_IFBLK)
 -c: dispositivo não-estruturado (S_IFCHR)
<dir>: caminho para diretório
Os modificadores são mutuamente exclusivos: no máximo um deles pode ser mencionado em uma
invocação do programa. Na ausência de modificadores, deve ser assumido -r. Na ausência de caminhos
para diretórios, deve ser assumido o diretório corrente. Utilize a função getopt da biblioteca padrão
para obter e tratar educadamente os modificadores do programa.
Exemplos:
icount /etc conta arquivos regulares em “/etc”
icount -d /home conta subdiretórios em “/home”
icount -b /dev conta dispositivos estruturados em “/dev”
icount conta arquivos regulares em “.”
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








void icount(char *dir){
		DIR *dp;
		struct dirent *entry;
		struct stat statbuf;
		int todos=0, reg=0, folder=0, elo=0, estrut=0,nestrut=0,outro=0;

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

				 /*-r: arquivo regular (S_IFREG)
				 -d: diretório (S_IFDIR)
				 -l: elo simbólico (S_IFLNK)
				 -b: dispositivo estruturado (S_IFBLK)
				 -c: dispositivo não-estruturado (S_IFCHR)*/
				

				if( statbuf.st_mode & S_IFDIR) {
		 				printf(">>  %s  <<\n",entry->d_name);
						todos++; folder++;
				}
					 if( statbuf.st_mode & S_IFLNK) {
		 				printf("@ %s \n",entry->d_name);
						todos++; elo++;
				}
					 if( statbuf.st_mode & S_IFBLK) {
		 				printf("# %s \n",entry->d_name);
						todos++; estrut++;
				}
					 if( statbuf.st_mode & S_IFCHR) {
		 				printf("* %s \n",entry->d_name);
						todos++; nestrut++;
				}
					 if( statbuf.st_mode & S_IFREG) {
		 				printf("_%s \n",entry->d_name);
						todos++; reg++;
				}
				// else	{
				// 	printf("%s \n",entry->d_name);
				// 	todos++; outro++;
				// }
		}
		chdir("..");
		closedir(dp);
		printf("____________\nTODOS:%i\n(_)regular=%i\t(>>)folder=%i\t(@)elo=%i\t\n(#)estrut=%i\t(*)nestrut=%i\toutros=%i\n", todos,reg,folder,elo,estrut,nestrut,outro);

}


//executar :  icount pasta
//contar arquivos de cada tipo na pasta especificada
int main( int argc, char *argv[ ] ){
   	int cont=0;
   	char *full_path;
   	
   	//printar parametros
   	//printf("Funcao: %s\n", argv[cont]);
   	//if ( argc <=1) return;
   	//else for(cont=1; cont < argc; cont++) printf("  Parametro %d:  %s\n", cont,argv[cont]);

    //PRINT DIRETORIO DO PRIMEIRO ARGUMENTO
    //printdir(argv[1],2);

   	//sem usar walk_dir
    icount(argv[1]);

    return 0;
}