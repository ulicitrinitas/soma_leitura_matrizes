#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_show 30

char** leitura_das_matrizes(FILE *f, int size);
void show(int n);
void substitui_char(char **m_str, int num, char antigo, char novo);
void print_cmatrix(char **m_str, int num);
int** gerar_matriz(char** c_matriz, int num_msize, char padrao);
void print_nmatrix(int **m_int, int num);

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

    fclose(f1);
    fclose(f2);

    print_cmatrix(linhas_m1, num_msize);

    print_cmatrix(linhas_m2, num_msize);

    char padrao = '$';

    substitui_char(linhas_m1, num_msize, ' ', padrao);

    print_cmatrix(linhas_m1, num_msize);

    substitui_char(linhas_m2, num_msize, ' ', padrao);

    
    print_cmatrix(linhas_m2, num_msize);

    int** m1 = gerar_matriz(linhas_m1, num_msize, padrao);
    int** m2 = gerar_matriz(linhas_m2, num_msize, padrao);

    print_nmatrix(m1, num_msize);
    print_nmatrix(m2, num_msize);

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

void substitui_char(char **m_str, int num, char antigo, char novo)
{

    for(int i = 0; i < num; i++){
        for(int j = 0; j < 1024; j++){
            if(m_str[i][j] == antigo){
                m_str[i][j] = novo;
            }
        }
    }
}

void print_cmatrix(char **m_str, int num)
{
    show(n_show);

    for(int i = 0; i < num; i++){
        printf("%s", m_str[i]);
    }
    puts("");
}

void print_nmatrix(int **m_int, int num)
{
    show(n_show);

    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            printf("%d ", m_int[i][j]);
        }
        puts("");
    }
}

int** gerar_matriz(char** c_matriz, int num_msize, char padrao)
{
    int** matriz = (int**) calloc(num_msize, sizeof(int*));

    if(matriz == NULL){
        puts("Erro! Espaco insuficiente!");
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < num_msize; i++){
        matriz[i] = (int*) calloc(num_msize, sizeof(int));

        if(matriz[i] == NULL){
            puts("Erro! Espaco insuficiente!");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < num_msize; i++){
        char* substring = strtok(c_matriz[i], &padrao);

        int j = 0;

        while(substring != NULL){
            
            matriz[i][j] = atoi(substring);

            substring = strtok(NULL, &padrao);

            j++;
        }
    }

    return matriz;
}
