#include <stdio.h>
#include <stdlib.h>

#define n_show 30

char** leitura_das_matrizes(FILE *f, int size);
void show(int n);

int main(int argc, char **argv)
{
    printf("%s was running with %d args\n", argv[0], argc-1);

    if(argc <= 1){
        puts("Erro! precisa ter ao menos 7 argumentos");
        return EXIT_FAILURE;
    }

    const int num_threads = atoi(argv[1]);
    const int num_msize = atoi(argv[2]);

    show(n_show);
    printf("num_threads: %d\nnum_msize: %d\n", num_threads, num_msize);

    FILE *f1;
    FILE *f2;

    f1 = fopen(argv[3], "r");
    f2 = fopen(argv[4], "r");

    if(f1 == NULL || f2 == NULL){
        puts("Erro! Leitura dos arquivos falhou!");
        return EXIT_FAILURE;
    }

    show(n_show);
    printf("f1: %s\nf2: %s\n", argv[4], argv[5]);

    char **linhas_m1 = leitura_das_matrizes(f1, num_msize);
    char **linhas_m2 = leitura_das_matrizes(f2, num_msize);

    show(n_show);
    puts("m1: ");
    for(int i = 0; i < num_msize; i++){
        printf("%s", linhas_m1[i]);
    }
    puts("");

    show(n_show);
    puts("m2: ");
    for(int i = 0; i < num_msize; i++){
        printf("%s", linhas_m2[i]);
    }
    puts("");
    show(n_show);

    return 0;
}

void show(int n)
{
    int i = 0;
    while(i < n){
        printf("=-"); 
        i++;
    }
    printf("\n");
}

char** leitura_das_matrizes(FILE *f, int size)
{
    char **linhas = (char**) calloc(size, sizeof(char*));

    if(linhas == NULL){
        puts("Erro! Espaco insuficiente!");
        exit(EXIT_FAILURE);
    }

    for(int i  = 0; i < size; i++){
        linhas[i] = (char*) calloc(1024, sizeof(char));
    }

    if(linhas[1] == NULL){
        puts("Erro! Espaco insuficiente no vetor!");
        exit(EXIT_FAILURE);
    }

    int count = 0;

    while(!feof(f)){
        fgets(linhas[count], 1024, f);
        count++;
    }

    return linhas;
}
