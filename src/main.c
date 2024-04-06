#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_show 30

char** leitura_das_matrizes(FILE *f, int size);

void show(int n);
void print_cmatrix(char **m_str, int num);
void print_nmatrix(int **m_int, int num);
void substitui_char(char **m_str, int num, char antigo, char novo);

int** gerar_nmatriz(int num);
int** inserir_nmatriz(int** matriz, char** c_matriz, int num_msize, char padrao);
int** gerar_nmatriz_lida(char** c_matriz, int num, char padrao);

int** soma_matrizes(int** m1, int** m2, int num);

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

    FILE *fA;
    FILE *fB;

    fA = fopen(argv[3], "r");
    fB = fopen(argv[4], "r");

    if(fA == NULL || fB == NULL){
        puts("Erro! Leitura dos arquivos falhou!");
        return EXIT_FAILURE;
    }

    show(n_show);
    printf("fA: %s\nfB: %s\n", argv[4], argv[5]);

    char **linhas_m1 = leitura_das_matrizes(fA, num_msize);
    char **linhas_m2 = leitura_das_matrizes(fB, num_msize);

    fclose(fA);
    fclose(fB);

    print_cmatrix(linhas_m1, num_msize);

    print_cmatrix(linhas_m2, num_msize);

    char padrao = '$';

    substitui_char(linhas_m1, num_msize, ' ', padrao);

    print_cmatrix(linhas_m1, num_msize);

    substitui_char(linhas_m2, num_msize, ' ', padrao);

    
    print_cmatrix(linhas_m2, num_msize);

    int** m1 = gerar_nmatriz_lida(linhas_m1, num_msize, padrao);
    int** m2 = gerar_nmatriz_lida(linhas_m2, num_msize, padrao);

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

int** gerar_nmatriz(int num)
{
    int** matriz = (int**) calloc(num, sizeof(int*));

    if(matriz == NULL){
        puts("Erro! Espaco insuficiente!");
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < num; i++){
        matriz[i] = (int*) calloc(num, sizeof(int));

        if(matriz[i] == NULL){
            puts("Erro! Espaco insuficiente!");
            exit(EXIT_FAILURE);
        }
    }

    return matriz;
}

int** inserir_nmatriz(int** matriz, char** c_matriz, int num, char padrao)
{
    for(int i = 0; i < num; i++){
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

int** gerar_nmatriz_lida(char** c_matriz, int num, char padrao)
{
    int** matriz = gerar_nmatriz(num);
    matriz = inserir_nmatriz(matriz, c_matriz, num, padrao);

    return matriz;
}

int** soma_matrizes(int** m1, int** m2, int num)
{
    int** resultado = gerar_nmatriz(num);

    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            resultado[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return resultado;

}
