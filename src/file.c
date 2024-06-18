#include "file.h"

/**
 * @brief Lê as dimensões de uma matriz a partir de um arquivo.
 *
 * A função `read_dimensions` lê dois inteiros do arquivo especificado da primeira linha, 
 * interpretando-as como o número de linhas e colunas de uma matriz.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param rows Ponteiro para um inteiro onde o número de linhas será armazenado.
 * @param columns Ponteiro para um inteiro onde o número de colunas será armazenado.
 * 
 * @return Retorna 0 se as duas inteiras (número de linhas e colunas) forem 
 * lidas com sucesso. Retorna 1 se houver falha na leitura, como quando o arquivo
 * não contém dois inteiros ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos dois inteiros separados por espaços ou novas linhas. 
 * Em caso de erro de leitura, os valores apontados por `rows` e `columns` não serão
 * modificados.
 */
int read_dimensions(FILE *file, int *rows, int *columns) {
    return fscanf(file, "%i %i", rows, columns) == 2 ? 0 : 1;
}

/**
 * @brief Lê o número de facções de um arquivo.
 *
 * A função `read_num_factions` lê um único inteiro de um arquivo especificado, 
 * interpretando-o como o número de facções.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param num_factions Ponteiro para um inteiro onde o número de facções será armazenado.
 * 
 * @return Retorna 0 se o inteiro (número de facções) for lido com sucesso. 
 * Retorna 1 se houver falha na leitura, como quando o arquivo não contém 
 * um inteiro ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos um inteiro. Em caso de erro de leitura, o valor apontado 
 * por `num_factions` não será modificado.
 */
int read_num_factions(FILE *file, int *num_factions) {
    return fscanf(file, "%i", num_factions) == 1 ? 0 : 1;
}

/**
 * @brief Lê uma parte e uma ação de um arquivo.
 *
 * A função `read_part_action` lê duas strings de um arquivo especificado, 
 * interpretando-as como uma parte e uma ação.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param part Ponteiro para um buffer de caracteres onde a parte será armazenada. 
 * O buffer deve ser grande o suficiente para armazenar a string lida.
 * @param action Ponteiro para um buffer de caracteres onde a ação será armazenada. 
 * O buffer deve ser grande o suficiente para armazenar a string lida.
 * 
 * @return Retorna 0 se as duas strings (parte e ação) forem lidas com sucesso. 
 * Retorna 1 se houver falha na leitura, como quando o arquivo não contém duas 
 * strings ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos duas strings separadas por espaços ou novas linhas. Em caso 
 * de erro de leitura, os valores apontados por `part` e `action` não serão 
 * modificados. Além disso, os buffers fornecidos para `part` e `action` devem ser 
 * grandes o suficiente para armazenar as strings lidas.
 */
int read_part_action(FILE *file, char *part, char *action) {
    return fscanf(file, "%s %s", part, action) == 2 ? 0 : 1;
}

/**
 * @brief Lê o nome de uma facção de um arquivo.
 *
 * A função `read_alliances` lê uma string de um arquivo especificado, 
 * interpretando-a como o nome de uma facção.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param faction Ponteiro para um buffer de caracteres onde o nome da facção será armazenado. 
 * O buffer deve ser grande o suficiente para armazenar a string lida.
 * 
 * @return Retorna 0 se a string (nome da facção) for lida com sucesso. 
 * Retorna 1 se houver falha na leitura, como quando o arquivo não contém 
 * uma string ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos uma string. Em caso de erro de leitura, o valor apontado 
 * por `faction` não será modificado. Além disso, o buffer fornecido para `faction` 
 * deve ser grande o suficiente para armazenar a string lida.
 */
int read_alliances(FILE *file, char *faction) {
    return fscanf(file, "%s", faction) == 1 ? 0 : 1;
}

/**
 * @brief Lê um parâmetro e uma lista de inteiros de um arquivo.
 *
 * A função `read_attack` lê uma string seguida de uma lista de inteiros de um 
 * arquivo especificado. A string é interpretada como um parâmetro e os inteiros 
 * são armazenados em um array fornecido.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param param Ponteiro para um buffer de caracteres onde o parâmetro será armazenado. 
 * O buffer deve ser grande o suficiente para armazenar a string lida.
 * @param params Ponteiro para um array de inteiros onde os parâmetros inteiros serão armazenados. 
 * O array deve ser grande o suficiente para armazenar todos os inteiros lidos.
 * 
 * @return Retorna 0 se a string (parâmetro) e a lista de inteiros forem lidas com sucesso. 
 * Retorna 1 se houver falha na leitura da string. Se a leitura dos inteiros falhar após 
 * a leitura bem-sucedida da string, os inteiros lidos até o ponto de falha serão armazenados.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos uma string seguida de inteiros. Em caso de erro na leitura da string, 
 * o valor apontado por `param` não será modificado. Além disso, os buffers fornecidos 
 * para `param` e `params` devem ser grandes o suficiente para armazenar a string e os inteiros lidos.
 */
int read_attack(FILE *file, char *param, int *params) {
    if (fscanf(file, "%s", param) != 1) {
        return 1;
    }
    int index = 0;
    while (fscanf(file, "%i", &params[index]) == 1) {
        index++;
    }
    return 0;
}

/**
 * @brief Lê os detalhes de um combate de um arquivo.
 *
 * A função `read_combat` lê um inteiro, uma string e outro inteiro de um 
 * arquivo especificado. Esses valores são interpretados como o valor próprio, 
 * o nome do inimigo e o valor do inimigo, respectivamente.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param enemy_name Ponteiro para um buffer de caracteres onde o nome do inimigo será armazenado. 
 * O buffer deve ser grande o suficiente para armazenar a string lida.
 * @param self_value Ponteiro para um inteiro onde o valor próprio será armazenado.
 * @param enemy_value Ponteiro para um inteiro onde o valor do inimigo será armazenado.
 * 
 * @return Retorna 0 se os três valores (valor próprio, nome do inimigo e valor do inimigo) 
 * forem lidos com sucesso. Retorna 1 se houver falha na leitura, como quando o arquivo 
 * não contém os três valores esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos um inteiro, uma string e outro inteiro. Em caso de erro de leitura, 
 * os valores apontados por `self_value`, `enemy_name` e `enemy_value` não serão modificados. 
 * Além disso, o buffer fornecido para `enemy_name` deve ser grande o suficiente para armazenar a string lida.
 */
int read_combat(FILE *file, char *enemy_name, int *self_value, int *enemy_value) {
    return fscanf(file, "%i %s %i", self_value, enemy_name, enemy_value) == 3 ? 0 : 1;
}

/**
 * @brief Lê a posição e a facção de um arquivo.
 *
 * A função `read_position_faction` lê dois inteiros de um arquivo especificado, 
 * interpretando-os como a posição e a facção de um elemento.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param params Ponteiro para um array de inteiros onde a posição e a facção serão armazenadas. 
 * O array deve ter pelo menos dois elementos, onde params[0] será a posição e params[1] será a facção.
 * 
 * @return Retorna 0 se os dois inteiros (posição e facção) forem lidos com sucesso. 
 * Retorna 1 se houver falha na leitura, como quando o arquivo não contém 
 * os dois inteiros esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos dois inteiros. Em caso de erro de leitura, os valores 
 * armazenados em `params` não serão modificados. Além disso, o array fornecido 
 * para `params` deve ter espaço para armazenar pelo menos dois inteiros.
 */
int read_position_faction(FILE *file, int *params) {
    return fscanf(file, "%i %i", &params[0], &params[1]) == 2 ? 0 : 1;
}

/**
 * @brief Lê a posição e informações de uma unidade de um arquivo.
 *
 * A função `read_position_unit` lê três inteiros de um arquivo especificado, 
 * interpretando-os como a posição e informações de uma unidade.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param params Ponteiro para um array de inteiros onde a posição e informações 
 * da unidade serão armazenadas. O array deve ter pelo menos três elementos, onde:
 * params[0] será a posição X,
 * params[1] será a posição Y,
 * params[2] será a informação adicional da unidade.
 * 
 * @return Retorna 0 se os três inteiros (posição X, posição Y e informação adicional) 
 * forem lidos com sucesso. Retorna 1 se houver falha na leitura, como quando o arquivo 
 * não contém os três inteiros esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos três inteiros. Em caso de erro de leitura, os valores 
 * armazenados em `params` não serão modificados. Além disso, o array fornecido 
 * para `params` deve ter espaço para armazenar pelo menos três inteiros.
 */
int read_position_unit(FILE *file, int *params) {
    return fscanf(file, "%i %i %i", &params[0], &params[1], &params[2]) == 3 ? 0 : 1;
}

/**
 * @brief Lê as informações de um prédio de um arquivo.
 *
 * A função `read_building` lê quatro inteiros de um arquivo especificado, 
 * interpretando-os como informações de um prédio.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param params Ponteiro para um array de inteiros onde as informações do prédio 
 * serão armazenadas. O array deve ter pelo menos quatro elementos, onde:
 * params[0] será a posição X,
 * params[1] será a posição Y,
 * params[2] será o tipo do prédio,
 * params[3] será a idade do prédio.
 * 
 * @return Retorna 0 se os quatro inteiros (posição X, posição Y, tipo e idade do prédio) 
 * forem lidos com sucesso. Retorna 1 se houver falha na leitura, como quando o arquivo 
 * não contém os quatro inteiros esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos quatro inteiros. Em caso de erro de leitura, os valores 
 * armazenados em `params` não serão modificados. Além disso, o array fornecido 
 * para `params` deve ter espaço para armazenar pelo menos quatro inteiros.
 */
int read_building(FILE *file, int *params) {
    return fscanf(file, "%i %i %i %i", &params[0], &params[1], &params[2], &params[3]) == 4 ? 0 : 1;
}

/**
 * @brief Lê as informações de um movimento de um arquivo.
 *
 * A função `read_move` lê três inteiros de um arquivo especificado, 
 * interpretando-os como informações de um movimento.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param params Ponteiro para um array de inteiros onde as informações do movimento 
 * serão armazenadas. O array deve ter pelo menos três elementos, onde:
 * params[0] será a posição inicial,
 * params[1] será a posição final,
 * params[2] será a distância do movimento.
 * 
 * @return Retorna 0 se os três inteiros (posição inicial, posição final e distância do movimento) 
 * forem lidos com sucesso. Retorna 1 se houver falha na leitura, como quando o arquivo 
 * não contém os três inteiros esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos três inteiros. Em caso de erro de leitura, os valores 
 * armazenados em `params` não serão modificados. Além disso, o array fornecido 
 * para `params` deve ter espaço para armazenar pelo menos três inteiros.
 */
int read_move(FILE *file, int *params) {
    return fscanf(file, "%i %i %i", &params[0], &params[1], &params[2]) == 3 ? 0 : 1;
}

/**
 * @brief Lê as informações de coleta de um arquivo.
 *
 * A função `read_collect` lê dois inteiros de um arquivo especificado, 
 * interpretando-os como informações de coleta.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param params Ponteiro para um array de inteiros onde as informações de coleta 
 * serão armazenadas. O array deve ter pelo menos dois elementos, onde:
 * params[0] será a posição de coleta,
 * params[1] será a quantidade coletada.
 * 
 * @return Retorna 0 se os dois inteiros (posição de coleta e quantidade coletada) 
 * forem lidos com sucesso. Retorna 1 se houver falha na leitura, como quando o arquivo 
 * não contém os dois inteiros esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos dois inteiros. Em caso de erro de leitura, os valores 
 * armazenados em `params` não serão modificados. Além disso, o array fornecido 
 * para `params` deve ter espaço para armazenar pelo menos dois inteiros.
 */
int read_collect(FILE *file, int *params) {
    return fscanf(file, "%i %i", &params[0], &params[1]) == 2 ? 0 : 1;
}

/**
 * @brief Lê as informações de defesa de um arquivo.
 *
 * A função `read_defend` lê dois inteiros de um arquivo especificado, 
 * interpretando-os como informações de defesa.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param params Ponteiro para um array de inteiros onde as informações de defesa 
 * serão armazenadas. O array deve ter pelo menos dois elementos, onde:
 * params[0] será a posição de defesa,
 * params[1] será a força de defesa.
 * 
 * @return Retorna 0 se os dois inteiros (posição de defesa e força de defesa) 
 * forem lidos com sucesso. Retorna 1 se houver falha na leitura, como quando o arquivo 
 * não contém os dois inteiros esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contém pelo menos dois inteiros. Em caso de erro de leitura, os valores 
 * armazenados em `params` não serão modificados. Além disso, o array fornecido 
 * para `params` deve ter espaço para armazenar pelo menos dois inteiros.
 */
int read_defend(FILE *file, int *params) {
    return fscanf(file, "%i %i", &params[0], &params[1]) == 2 ? 0 : 1;
}

/**
 * @brief Lê as informações de vitória de um arquivo.
 *
 * A função `read_win` lê três informações de um arquivo especificado, 
 * interpretando-os como resultados de uma vitória entre dois tipos de entidades.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param type_a Ponteiro para um inteiro onde será armazenado o tipo da entidade A.
 * @param name_b Array de caracteres onde será armazenado o nome da entidade B, com no máximo 14 caracteres (mais o terminador nulo).
 * @param type_b Ponteiro para um inteiro onde será armazenado o tipo da entidade B.
 * 
 * @return Retorna o número de itens atribuídos com sucesso, que deve ser 3 para indicar 
 * que todos os valores (tipo A, nome B e tipo B) foram lidos corretamente. Retorna 
 * um valor diferente de 3 se houver falha na leitura, como quando o arquivo não 
 * contém os três itens esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contenha exatamente três itens para serem lidos. Em caso de erro de leitura, 
 * os valores armazenados em `type_a`, `name_b` e `type_b` podem ser inconsistentes 
 * ou não modificados. O nome da entidade B deve ter no máximo 14 caracteres para 
 * garantir que haja espaço para o terminador nulo.
 */
int read_win(FILE *file, int* type_a, char name_b[15], int* type_b)
{
    return fscanf(file, "%i %s %i", &(*type_a), name_b, &(*type_b));
}

/**
 * @brief Lê as informações de derrota de um arquivo.
 *
 * A função `read_lose` lê três informações de um arquivo especificado,
 * interpretando-os como resultados de uma derrota entre dois tipos de entidades.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde
 * os dados serão lidos. Este arquivo deve estar previamente aberto em modo
 * de leitura.
 * @param type_a Ponteiro para um inteiro onde será armazenado o tipo da entidade A.
 * @param name_b Array de caracteres onde será armazenado o nome da entidade B, com no máximo 14 caracteres (mais o terminador nulo).
 * @param type_b Ponteiro para um inteiro onde será armazenado o tipo da entidade B.
 *
 * @return Retorna o número de itens atribuídos com sucesso, que deve ser 3 para indicar
 * que todos os valores (tipo A, nome B e tipo B) foram lidos corretamente. Retorna
 * um valor diferente de 3 se houver falha na leitura, como quando o arquivo não
 * contém os três itens esperados ou ocorre um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura
 * e contenha exatamente três itens para serem lidos. Em caso de erro de leitura,
 * os valores armazenados em `type_a`, `name_b` e `type_b` podem ser inconsistentes
 * ou não modificados. O nome da entidade B deve ter no máximo 14 caracteres para
 * garantir que haja espaço para o terminador nulo.
 */
int read_lose(FILE *file, int* type_a, char name_b[15], int* type_b)
{
    return fscanf(file, "%i %s %i", &(*type_a), name_b, &(*type_b));
}

/**
 * @brief Lê a quantidade ganha de um arquivo.
 *
 * A função `read_earn` lê um único inteiro de um arquivo especificado, 
 * interpretando-o como a quantidade ganha.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde 
 * o dado será lido. Este arquivo deve estar previamente aberto em modo 
 * de leitura.
 * @param param Ponteiro para um inteiro onde a quantidade ganha será armazenada.
 * 
 * @return Retorna 0 se o inteiro for lido com sucesso. Retorna 1 se houver falha 
 * na leitura, como quando o arquivo não contém o inteiro esperado ou ocorre 
 * um erro de leitura.
 *
 * @note Certifique-se de que o arquivo fornecido esteja aberto em modo de leitura 
 * e contenha exatamente um inteiro para ser lido. Em caso de erro de leitura, 
 * o valor armazenado em `param` pode ser inconsistente ou não modificado.
 */
int read_earn(FILE *file, int* param)
{
    return fscanf(file, "%i", param) == 1 ? 0 : 1;
}

/**
 * @brief Lê e processa todas as operações de um arquivo de entrada, simulando um jogo.
 *
 * A função `read_all_file` lê sequencialmente as operações de um arquivo especificado,
 * realiza o processamento adequado para cada operação e determina o vencedor do jogo
 * com base nas facções envolvidas.
 *
 * @param file Ponteiro para um objeto FILE, que representa o arquivo de onde serão lidos os dados.
 *             Este arquivo deve estar previamente aberto em modo de leitura.
 * 
 * @return Retorna 0 se todas as operações foram lidas e processadas com sucesso.
 *         Retorna 1 se houve uma falha ao ler alguma informação essencial do arquivo,
 *         como dimensões do tabuleiro ou número de facções.
 *
 * @note A função assume que o arquivo fornecido contém operações válidas que seguem um
 *       formato específico para serem lidas e processadas corretamente. Cada operação é
 *       processada por uma função específica de manipulação (por exemplo, `handle_attack`,
 *       `handle_combat`, `handle_collect`, etc.), que executa as ações correspondentes no jogo.
 *       Ao final, a função determina o vencedor com base nos critérios de poder e recursos das facções.
 *       Certifique-se de que o arquivo de saída "saida.txt" seja criado e esteja acessível para
 *       armazenar informações relevantes, como o vencedor do jogo.
 */
int read_all_file(FILE *file) {
    FILE *log = fopen("saida.txt", "w+");
    fclose(log);

    log = fopen("saida.txt", "a");

    int rows, columns;
    // Lê as dimensões do tabuleiro
    if (read_dimensions(file, &rows, &columns) != 0) {
        printf("Falha ao ler as dimensões do tabuleiro.\n");
        return 1;
    }

    // Cria o tabuleiro com as dimensões lidas
    board_t *board = create_board(rows, columns);
    int map[columns][rows];
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            int random = rand() % 10;

            map[i][j] = ((random >= 0 && random < 6) ? 0 : (random >= 6 && random < 9) ? 1 : 2);
        }
    }

    // Inicializa as listas para facções, construções, unidades e alianças
    faction_t *factions = NULL;
    building_t *buildings = NULL;
    unit_t *units = NULL;
    alliance_t *alliances = NULL;

    int num_factions;
    // Lê o número de facções
    if (read_num_factions(file, &num_factions) != 0) {
        printf("Falha ao ler o número de facções.\n");
        return 1;
    }

    char part[MAX_PART_LEN];
    char action[MAX_ACTION_LEN];

    // Processa cada operação no arquivo até o final
    while (!feof(file)) {
        srand(time(NULL)); // Reinicia a semente do gerador de números aleatórios

        // Lê a parte e a ação da operação
        if (read_part_action(file, part, action) != 0) {
            printf("Falha ao ler a parte e a ação.\n");
            break;
        }

        // Verifica a ação e realiza o processamento correspondente
        if (strcmp(action, "alianca") == 0) {
            char faction[MAX_FACTION_NAME_LEN];
            // Lê a aliança entre facções
            if (read_alliances(file, faction) == 0) {
                handle_alliance(log, &factions, part, faction);
            }
        } else if (strcmp(action, "ataca") == 0) {
            char param[MAX_FACTION_NAME_LEN];
            int params[MAX_PARAMS];
            // Lê a ação de ataque
            if (read_attack(file, param, params) == 0) {
                handle_attack(log, &factions, part, param);
            }
        } else if (strcmp(action, "combate") == 0) {
            char enemy_name[MAX_FACTION_NAME_LEN];
            int self_value, enemy_value;
            // Lê a operação de combate
            if (read_combat(file, enemy_name, &self_value, &enemy_value) == 0) {
                handle_combat(log,board, &units, part, enemy_name);
            }
        } else if (strcmp(action, "ganha") == 0) {
            int power;
            if(read_earn(file, &power) == 0){
                handle_earn(log, &factions, part, power);
            }
        } else if (strcmp(action, "perde") == 0) {
            // Operação de perda (não implementada)
        } else if (strcmp(action, "vence") == 0) {
            // Operação de vitória (não implementada)
        } else if (strcmp(action, "pos") == 0) {
            int params[MAX_PARAMS];
            // Lê a posição de uma facção ou unidade
            if (num_factions > 0) {
                if (read_position_faction(file, params) == 0) {
                    handle_position_faction(log, &board, &factions, part, params);
                    num_factions--;
                }
            } else {
                if (read_position_unit(file, params) == 0) {
                    handle_position_unit(log, &board, &factions, &units, part, params);
                }
            }
        } else if (strcmp(action, "move") == 0) {
            int params[MAX_PARAMS];
            // Lê a operação de movimento
            if (read_move(file, params) == 0) {
                handle_move(log, board, &units, part, params);
            }
        } else if (strcmp(action, "coleta") == 0) {
            int params[MAX_PARAMS];
            // Lê a operação de coleta de recursos
            if (read_collect(file, params) == 0) {
                handle_collect(log, &factions, &units, columns, rows, map, part);
            }
        } else if (strcmp(action, "constroi") == 0) {
            int params[MAX_PARAMS];
            // Lê a operação de construção
            if (read_building(file, params) == 0) {
                handle_building(log, &board, &factions, &buildings, part, params);
            }
        } else if (strcmp(action, "defende") == 0) {
            int params[MAX_PARAMS];
            // Lê a operação de defesa
            if (read_defend(file, params) == 0) {
                handle_defend(log, &factions, part);
            }
        }

        fprintf(log, "=== Fim do turno ===\n");
        faction_t *temp = factions;
        while(temp != NULL){
            fprintf(log, "Turno do jogador %s finalizado.\n", temp->name);
            fprintf(log, "Recursos atualizados: %d.\n", temp->resources);
            fprintf(log, "Poder atualizado: %d.\n", temp->power);
            fprintf(log, "\n");
            temp = temp->next;
        }
    }

    fclose(file);

    faction_t *winner = NULL;
    faction_t *current_faction = factions;

    while (current_faction != NULL) {
        // Verifica se ainda não há vencedor ou se a facção atual supera o vencedor atual
        if (winner == NULL || current_faction->power + current_faction->resources > winner->power + winner->resources) {
            winner = current_faction;
        }
        current_faction = current_faction->next;
    }


    fprintf(log, "=== Vitória alcançada ===\n");
    fprintf(log, "Facção %s alcançou a vitória!\n", part);
    fprintf(log, "Parabéns!\n\n");

    fclose(log);
    free_factions(&factions);
    free_buildings(&buildings);
    free_units(&units);
    free_alliances(&alliances);
    free_board(board);
    free(board);
    return 0;
}