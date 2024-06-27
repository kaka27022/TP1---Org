#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

Instruction *generateRandomInstructions(int ramSize)
{
    Instruction *instructions = (Instruction *)malloc(10 * sizeof(Instruction));

    for (int i = 0; i < 9; i++)
    {
        instructions[i].opcode = rand() % 4;      // 0, 1, 2, 3
        instructions[i].info1 = rand() % ramSize; // 0 ... RAM_SIZE
        do
        {
            instructions[i].info2 = rand() % ramSize; // 0 ... RAM_SIZE
        } while (instructions[i].info1 == instructions[i].info2);
        instructions[i].info3 = rand() % ramSize; // 0 ... RAM_SIZE
    }

    // inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[9].opcode = -1;
    instructions[9].info1 = -1;
    instructions[9].info2 = -1;
    instructions[9].info3 = -1;

    return instructions;
}

Instruction *readInstructions(char *fileName, int *ramSize)
{
    printf("FILE -> %s\n", fileName);
    FILE *file = fopen(fileName, "r"); // Abrindo arquivo no modo leitura

    if (file == NULL)
    {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", ramSize, &n);
    Instruction *instructions = (Instruction *)malloc(n * sizeof(Instruction));
    while (i < n)
    {
        fscanf(file, "%d %d %d %d", &instructions[i].opcode, &instructions[i].info1, &instructions[i].info2, &instructions[i].info3);
        i++;
    }
    fclose(file); // Fechando o arquivo

    return instructions;
}

void store_instructions(Instruction instruction, int *ramSize)
{
    instruction.info1 = rand() % *ramSize; // 0 ... RAM_SIZE
    do
    {
        instruction.info2 = rand() % *ramSize; // 0 ... RAM_SIZE
    } while (instruction.info1 == instruction.info2);
    instruction.info3 = rand() % *ramSize; // 0 ... RAM_SIZE
}

Instruction *generateMultiInstructions(int multiplicando, int multiplicador)
{
    printf("MULTIPLICAÇÃO: %d com %d:\n", multiplicando, multiplicador);
    Instruction *instructions = (Instruction *)malloc((3 + multiplicador) * sizeof(Instruction));

    // Gera instrucoes para carregar valores iniciais na RAM
    instructions[0].opcode = 0;            // Levando informacoes para a RAM
    instructions[0].info1 = multiplicando; // Valor a ser multiplicado;
    instructions[0].info2 = 0;             // Endereco da RAM onde o valor sera armazenado
    instructions[0].info3 = 0;

    // Gera instrucoes para realizar a multiplicacao
    for (int i = 1; i < multiplicador; i++)
    {
        instructions[i].opcode = 1;    // Somando
        instructions[i].info1 = i - 1; // Endereco da RAM com o resultado parcial
        instructions[i].info2 = 0;     // Endereco da RAM com o valor a ser multiplicado
        instructions[i].info3 = i;     // Endereco da RAM onde o resultado parcial sera armazenado
    }

    // inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[multiplicador + 2].opcode = -1;
    instructions[multiplicador + 2].info1 = -1;
    instructions[multiplicador + 2].info2 = -1;
    instructions[multiplicador + 2].info3 = -1;

    return instructions;
}
void attInstructions(Machine *machine, Instruction *inst) {
    machine->instructions = inst;
}
Instruction *generateDiviInstructions(int divisor, int dividendo)
{
    Instruction *instructions = (Instruction *)malloc((5 + dividendo / divisor) * sizeof(Instruction));

    // Gera instrucoes para carregar valores iniciais na RAM
    instructions[0].opcode = 0;        // Levando informacoes para a RAM
    instructions[0].info1 = dividendo; // Valor a ser dividido
    instructions[0].info2 = 0;         // Endereco da RAM onde o valor sera armazenado
    instructions[0].info3 = -1;

    instructions[1].opcode = 0;      // Levando informacoes para a RAM
    instructions[1].info1 = divisor; // Valor divisor
    instructions[1].info2 = 1;       // Endereco da RAM onde o valor sera armazenado
    instructions[1].info3 = -1;

    // Gera instrucoes para realizar a divisao
    int i = 0;
    while ((i + 1) * divisor <= dividendo)
    {
        instructions[i + 2].opcode = 2;    // Subtraindo
        instructions[i + 2].info1 = 0; // Endereco da RAM com o dividendo parcial
        instructions[i + 2].info2 = 1;     // Endereco da RAM com o valor divisor
        instructions[i + 2].info3 = 0; // Endereco da RAM onde o resultado parcial sera armazenado
        i++;                           // Contador do resultado
    }

    // Imprime o resultado da divisao
    instructions[i + 2].opcode = 0; // Levando informacao para a RAM
    instructions[i + 2].info1 = 0;  // Valor especial para indicar o fim da execucao
    instructions[i + 2].info2 = i + 2;  // Endereco da RAM com o resultado final
    instructions[i + 2].info3 = -1;

    // Armazena o dividendo e o resultado na RAM
    instructions[i + 3].opcode = 0; // Salvar na memoria
    instructions[i + 3].info1 = dividendo; // Valor dividendo
    instructions[i + 3].info2 = i + 3; // Endereco da RAM onde o dividendo sera armazenado
    instructions[i + 3].info3 = -1;

    // Inserindo a ultima instrucao do programa
    instructions[i + 4].opcode = -1;
    instructions[i + 4].info1 = -1;
    instructions[i + 4].info2 = -1;
    instructions[i + 4].info3 = -1;

    return instructions;
}
