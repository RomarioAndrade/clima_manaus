#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 256
#define CLIMA_1E3 1000
#define CLIMA_1E4 5000
#define CLIMA_5E3 10000

typedef struct Qair{
    int id_sensor;
    char data[11];
    double temperatura;
    double p_umidade;
    int nivel_pm25;
} Qair;

typedef struct lista{
    Qair *dados;
    int n_elementos;
    int size;
} Lista;

bool isFull(Lista *list){
    if (list->n_elementos == list->size)
    {
        return true;
    }
    return false;
}

void add(Lista *lista, Qair qair){
    //printf(" - %d\n",qair.id_sensor);
    if (!isFull(lista))
    {
        lista->dados[lista->n_elementos - 1] = qair;
        lista->n_elementos = lista->n_elementos + 1;
    }
    else{
    }
}

void ler_Arquivo(char file[], Lista *list, char *token)
{
    // 1. Abre o arquivo CSV em modo de leitura ("r")
    FILE *arquivo = fopen(file, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo alunos.csv!\n");
        return;
    }

    char linha[MAX];

    // Opcional: Ler e descartar a linha de cabeçalho (ex: "ID_Sensor,Data,Temperatura_C,Umidade_Porcentagem,Nivel_PM25")
    if (fgets(linha, sizeof(linha), arquivo) == NULL)
    {
        printf("Arquivo vazio ou erro ao ler cabeçalho.\n");
        fclose(arquivo);
        return;
    }

    printf("--- DADOS LIDOS DO ARQUIVO CSV ---\n");

    // 2. Loop para ler cada linha do arquivo até o fim (EOF)
    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        token = strtok(linha, ",");
        Qair quality_air;
        quality_air.id_sensor = atoi(token);
        token = strtok(NULL,",");
        strcpy(quality_air.data,token);
        token = strtok(NULL,",");
        quality_air.temperatura = atof(token);
        token = strtok(NULL,",");
        quality_air.p_umidade = atof(token);
        token = strtok(NULL,",");
        quality_air.nivel_pm25 = atof(token);

        add(list,quality_air);
    }

    // 4. Fecha o arquivo para liberar a memória do sistema
    fclose(arquivo);
}

void bubble_sort(double arr[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Troca arr[j] e arr[j+1]
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{

    //nome e caminho do arquivo
    char arquivo[] = "dados_clima_manaus_1e3.csv";

    //ler cada vetor de char separado por virgula
    char *token;

    Qair dado1[CLIMA_1E3];
    Qair dado2[CLIMA_1E4];
    Qair dado3[CLIMA_5E3];

    Lista list_1e3 = {.dados = dado1, .n_elementos = 0, .size = CLIMA_1E3};
    Lista list_1e4 = {.dados = dado1, .n_elementos = 0, .size = CLIMA_1E4};
    Lista list_5e3 = {.dados = dado1, .n_elementos = 0, .size = CLIMA_5E3};

    ler_Arquivo(arquivo, &list_1e3, token);
    ler_Arquivo(arquivo, &list_1e4,token);
    ler_Arquivo(arquivo, &list_5e3,token);

    for (int i = 0; i < CLIMA_1E3 -1; i++)
    {
        printf(" - %d - | %d | %s | %lf | %lf | %d | \n",i,list_1e3.dados[i].id_sensor,list_1e3.dados[i].data,
        list_1e3.dados[i].temperatura,list_1e3.dados[i].p_umidade,list_1e3.dados[i].nivel_pm25);
    }
    

    return 0;
}
