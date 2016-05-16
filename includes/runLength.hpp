/**
    UNIVERSIDADE DE SÃO PAULO - ICMC
    DEPARTAMENTO DE CIÊNCIAS DE COMPUTAÇÃO
    SCC0261 Multimídia - 1o Sem/2016
    runLength.hpp
    Objetivo: Codificar e decodificar cadeias de caracteres
    usando o método run length.

    @author Matheus Gomes da Silva Horta - 8532321
            Bárbara Darques Barros       - 7243081
*/
#ifndef RUNLENGTH_HPP_INCLUDED
#define RUNLENGTH_HPP_INCLUDED
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;



typedef struct character {

    char symbol;
    int reps;

}codedSymbol;

/**
    Realiza a codificação de uma string pelo método Run Length.

    @param
        symbols : Referencia para a string a ser codificada

    @return Um vetor de estruturas onde cada membro representa
    o símbolo e suas repetições consecutivas.
*/
vector<codedSymbol> generateReps(string &symbols);

/**
    Função auxiliar que chama as funções necessárias para
    realizar o método Run-Length sem compressão.

    @param
        simbols : Texto a ser codificado
        resultRL : O resultado da codificação num vetor
        de estruturas onde cada membro possui o caracter
        e o nmero de repetiçẽos.
        compressedFreqs : Vetor de booleanos com as repetições
        padronizadas com o numero máximo de bits aquele da maior repetição.
        header : O header do arquivo, que ira conter o número maximo de quantidade
        de bits que uma repetição pode ter.

*/
void RLencode(string& simbols,vector<codedSymbol>& resultRL,
    vector<bool>& compressedFreqs, string &header);

/**
    Função auxiliar que chama as funções necessárias para
    comprimir o resultado do método de run-length e armazena-lo
    no arquivo

    @param
        resultRL : O resultado da codificação num vetor
        de estruturas onde cada membro possui o caracter
        e o nmero de repetiçẽos.
        compressedFreqs : Vetor de booleanos com as repetições
        padronizadas com o numero máximo de bits aquele da maior repetição.
        header : O header do arquivo, que ira conter o número maximo de quantidade
        de bits que uma repetição pode ter.
        output : O nome do arquivo de saida

*/
char* RLcompress(vector<codedSymbol>& resultRL,vector<bool> &booleanReps,
    int *sizeCompressed);

void writeToFileRL(string &output, string &header, char *compressedReps,
    int *sizeCompressed,vector<codedSymbol>& resultRL);

#endif // RUNLENGTH_HPP_INCLUDED
