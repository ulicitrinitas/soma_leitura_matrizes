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

    FILE *f1;
    FILE *f2;

    f1 = fopen(argv[4], "r");
    f2 = fopen(argv[5], "r");

    if(f1 == NULL || f2 == NULL){
        puts("Erro! Leitura dos arquivos falhou!");
        return EXIT_FAILURE;
    }

    

    return 0;
}
