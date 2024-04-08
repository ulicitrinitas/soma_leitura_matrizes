#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_show 30

struct matriz{
    FILE* f;
    char** lida;
    int** gerada;
};

struct resultante{
    int** matriz;
};

typedef struct matriz Matriz;
typedef struct resultante Resultante;

char** leitura_das_matrizes(FILE *f, int size);

void show(int n);
void print_cmatrix(char **m_str, int num);
void print_nmatrix(int **m_int, int num);
void substitui_char(char **m_str, int num, char antigo, char novo);

int** gerar_nmatriz(int num);
int** inserir_nmatriz(int** matriz, char** c_matriz, int num_msize, char padrão);
int** gerar_nmatriz_lida(char** c_matriz, int num, char padrão);

int** soma_matrizes(int** m1, int** m2, int num);

void gravar_matriz(FILE* f  , int** matriz, int num);

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

    Matriz* matrizA = (Matriz*) malloc(sizeof(Matriz));
    Matriz* matrizB = (Matriz*) malloc(sizeof(Matriz));

    if(matrizA == NULL || matrizB == NULL){
        puts("Erro! Memoria Insuficiente!");
        return EXIT_FAILURE;
    }


    matrizA->f = fopen(argv[3], "r");
    matrizB->f = fopen(argv[4], "r");

    if(matrizA->f == NULL || matrizB->f == NULL){
        puts("Erro! Leitura dos arquivos falhou!");
        return EXIT_FAILURE;
    }

    show(n_show);
    printf("matrizA->f: %s\nmatrizB->f: %s\n", argv[4], argv[5]);

    matrizA->lida = leitura_das_matrizes(matrizA->f, num_msize);
    matrizB->lida = leitura_das_matrizes(matrizB->f, num_msize);

    fclose(matrizA->f);
    fclose(matrizB->f);

    print_cmatrix(matrizA->lida, num_msize);

    print_cmatrix(matrizB->lida, num_msize);

    const char padrão = '$';

    substitui_char(matrizA->lida, num_msize, ' ', padrão);

    print_cmatrix(matrizA->lida, num_msize);

    substitui_char(matrizB->lida, num_msize, ' ', padrão);

    
    print_cmatrix(matrizB->lida, num_msize);

    matrizA->gerada = gerar_nmatriz_lida(matrizA->lida, num_msize, padrão);
    matrizB->gerada = gerar_nmatriz_lida(matrizB->lida, num_msize, padrão);

    print_nmatrix(matrizA->gerada, num_msize);
    print_nmatrix(matrizB->gerada, num_msize);

    Resultante* matrizD = (Resultante*) malloc(sizeof(Resultante));

    matrizD->matriz = soma_matrizes(matrizA->gerada, matrizB->gerada, num_msize);

    print_nmatrix(matrizD->matriz, num_msize);

    // TODO: Gravação da Matriz D

    FILE* fD = fopen(argv[6], "w");

    if(fD == NULL){
        puts("Erro! Gravacao da Matriz D falhou!");
        return EXIT_FAILURE;
    }

    gravar_matriz(fD, matrizD->matriz, num_msize);

    fclose(fD);

    // TODO: Leitura da Matriz C
    Matriz *matrizC = (Matriz*) malloc(sizeof(Matriz));

    matrizC->f = fopen(argv[5], "r");

    matrizC->lida = leitura_das_matrizes(matrizC->f, num_msize);

    fclose(matrizC->f);

    print_cmatrix(matrizC->lida, num_msize);

    // TODO: Multiplicação das Matrizes D x C = E
    // TODO: Gravação da Matriz E
    // TODO: Redução da Matriz E
    // TODO: Criar Threads

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
        puts("Erro! Espaço insuficiente!");
        exit(EXIT_FAILURE);
    }

    for(int i  = 0; i < size; i++){
        linhas[i] = (char*) calloc(1024, sizeof(char));
    }

    if(linhas[1] == NULL){
        puts("Erro! Espaço insuficiente no vetor!");
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
        puts("Erro! Espaço insuficiente!");
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < num; i++){
        matriz[i] = (int*) calloc(num, sizeof(int));

        if(matriz[i] == NULL){
            puts("Erro! Espaço insuficiente!");
            exit(EXIT_FAILURE);
        }
    }

    return matriz;
}

int** inserir_nmatriz(int** matriz, char** c_matriz, int num, char padrão)
{
    for(int i = 0; i < num; i++){
        char* substring = strtok(c_matriz[i], &padrão);

        int j = 0;

        while(substring != NULL){
                
            matriz[i][j] = atoi(substring);
            substring = strtok(NULL, &padrão);
            
            j++;
        }
    }

    return matriz;
}

int** gerar_nmatriz_lida(char** c_matriz, int num, char padrão)
{
    int** matriz = gerar_nmatriz(num);
    matriz = inserir_nmatriz(matriz, c_matriz, num, padrão);

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

void gravar_matriz(FILE* f  , int** matriz, int num)
{
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            fprintf(f, "%d ", matriz[i][j]);
        }
        fprintf(f, "\n");
    }

}

