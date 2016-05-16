#ifndef COMPRESSOR_HPP_INCLUDED
#define COMPRESSOR_HPP_INCLUDED

#include<utility>
#include<map>
#include <queue>
#include<algorithm>
#include <cmath>
#include "runLength.hpp"
#include "huffman.hpp"
using namespace std;

/**
    Isola um bit da variável partindo do offset
    @param
        c : Caracter a ter o bit selecionado
        offset : Deslocamento do bit em relação ao menos significativo

    @return Vetor de bytes resultante da compressão
*/
int readBit(int *c, int *offset);
/**
    Le o conteudo do arquivo de entrada
    @param
        input_name : Nome do arquivo de entrada
        originalText : Irá armazenar o valor da string de entrada

    @return Vetor de bytes resultante da compressão
*/
void readInputFile(string input_name, string& originalText);
/**
    Realiza a compressão de um vetor de booleanos, agrupando
    de 8 em 8 bits em um vetor resultante

    @param
        bArray : Vetor de booleanos
        size : tamanho de vetor que será recebido dentro da função

    @return Vetor de bytes resultante da compressão
*/
char* compressBooleanArray(vector<bool> &bArray, int *size);
/**
    Transforma uma string binaria em um vetor de booleanos
    @param
        binaryString : String binaria a ser processada

    @return Vetor de booleanos
*/
vector<bool> stringToBinary(string &binaryString);
/**
    Transforma as todas repetições dos caracteres em um vetor de booleanos.
    Calcula o número de bytes da maior repetição e aplica a todas as outras. Todas as repetições
    terçao numero de bytes igual ao da maior repetição.

    @param
        RLstruct : Estrutura para os caracteres e repetições da codificação run length
        numSize ; Tamanho dessa estrutura
        header : Header do arquivo

    @return Vetor de booleanos
*/
vector<bool> compressRLreps(vector<codedSymbol>& RLstruct, int numSize, string &header);

string decompressHUF(treeNode* root, string& encoded_str);
treeNode* readHUFtree(FILE *arq, char *c, int* qtd);
void readHUFtreeAux(FILE *arq, treeNode *root, int* qtd);

/**

    charactersRL : String com os caracteres da saida de run length
    compressedRL : String com as repetiçes dos caracteres comprimidos
    maxFreqBits : o deslocamento até o bit maximo que o valor de uma repeitção pode ter
    @param
        RLstruct : Estrutura para os caracteres e repetições da codificação run length
        numSize ; Tamanho dessa estrutura
        header : Header do arquivo

    @return Vetor de booleanos
*/
string decompressRL(string &charactersRL, string &compressedRL,int *maxFreqBits);

#endif // COMPRESSOR_HPP_INCLUDED
