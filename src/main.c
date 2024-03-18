#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("%s was running with %d args\n", argv[0], argc-1);

    if(argc <= 1){
        puts("Erro! precisa ter ao menos 7 argumentos");
        return EXIT_FAILURE;
    }

    const int num_threads = atoi(argv[1]);
    const int num_msize = atoi(argv[2]);

    printf("num_threads: %d\nnum_msize: %d\n", num_threads, num_msize);

    FILE *f1;
    FILE *f2;

    f1 = fopen(argv[3], "r");
    f2 = fopen(argv[4], "r");

    if(f1 == NULL || f2 == NULL){
        puts("Erro! Leitura dos arquivos falhou!");
        return EXIT_FAILURE;
    }

    printf("f1: %s\nf2: %s\n", argv[4], argv[5]);

    char **linhas_m1 = (char**) calloc(num_msize, sizeof(char*));

    if(linhas_m1 == NULL){
        puts("Erro! Espaco insuficiente!");
        return EXIT_FAILURE;
    }

    for(int i  = 0; i < num_msize; i++){
        linhas_m1[i] = (char*) calloc(1024, sizeof(char));
    }

    if(linhas_m1[1] == NULL){
        puts("Erro! Espaco insuficiente no vetor!");
        return EXIT_FAILURE;
    }

    int count = 0;

    while(!feof(f1)){
        fgets(linhas_m1[count], 1024, f1);
        count++;
    }

    for(int i = 0; i < num_msize; i++){
        printf("%s", linhas_m1[i]);
    }
    puts("");

    

    return 0;
}
