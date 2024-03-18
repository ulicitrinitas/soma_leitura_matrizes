#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("%s was running with %d args\n", argv[0], argc-1);

    if(argc <= 1){
        puts("Erro! precisa ter ao menos 7 argumentos");
        return EXIT_FAILURE;
    }

    const int num_threads = atoi(argv[2]);
    const int num_msize = atoi(argv[3]);

    

    return 0;
}
