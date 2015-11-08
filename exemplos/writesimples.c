#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main (){
 if ((write(1, "Alo Mundo\n", 18)) != 18)
 write (2, "write error on file descriptor 1\n", 33);
 exit(0);
}
