/**
    UNIVERSIDADE DE SÃO PAULO - ICMC
    DEPARTAMENTO DE CIÊNCIAS DE COMPUTAÇÃO
    SCC0261 Multimídia - 1o Sem/2016
    huffman.hpp
    Objetivo: Codificar e decodificar cadeias de caracteres
    usando o método de Huffman.

    @author Matheus Gomes da Silva Horta - 8532321
            Bárbara Darques Barros       - 7243081
*/
#ifndef HUFFMAN_HPP_INCLUDED
#define HUFFMAN_HPP_INCLUDED
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<queue>
#include<sstream>
using namespace std;


/**
    Representa um nó da arvore de Huffman

    @param
        symbol : simbolo do texto original
        freq : frequencia desse simbolo no texto
        *left : ponteiro para o filho esquerdo
        *right : ponteiro para o filho direito
*/
typedef struct treenode{


    char symbol;
    short freq;
    treenode *left;
    treenode *right;


}treeNode;

/**
    Estrutura usada como operador de comparação usado na fila de prioridades
*/
struct compare
{
    bool operator()(treenode* l, treenode* r)
    {
        return (l->freq > r->freq);
    }
};

/**
    Inicializa o nó e inicializa os valores desse nó de acordo

    @param
        *symbol : Ponteiro para o caracter da frase original
        *freq : Ponteiro para a frequencia desse caracter

    @return treeNode* : Um nó da árvore alocado
*/

treeNode* inicializeNode(char symbol, short freq);

/**
    Determina a frequencia de cada simbolo na frase original

    @param
        text : O texto original

    @return Mapa que liga os símbolos da frase original com suas respectivas frequencias
*/
map<char,short> setFrequencies(string &text);

/**
    Gera a árvore de Huffman

    @param
        symbols : Mapa para os simbolos e suas frequencias
        header : O header que será armazenado no inicio do arquivo destivo

    @return Mapa que liga o símbolos da frase original com seus respectivos cdigos
*/
map<char,string> generateTree( map<char,short> &symbols, string &header, int*);
void generateCodes(treeNode*, map<char,string>*, string, int*);

/**
    Função auxiliar que chama todas as funções que realizam a codificação
    do metodo de huffman

    @param
        symbols : Texto original
        resultHUF : Texto não comprimido resultante da codificação por Huffman
        header : O header que será armazenado no inicio do arquivo destivo

*/
void HUFencode(string& simbols,string& resultHUF, string &header);

void writeToFileHUF(string &header, string &output, int *sizeCompressed,char *compressedHUF);
/**
    Função auxiliar que chama todas as funções que realizam a compressão
    da string resultante do método de huffman e a armazena no arquivo de saida
    junto com o header

    @param

        resultHUF : Texto não comprimido resultante da codificação por Huffman

*/
char* HUFcompress(string& resultHUF, int* sizeCompressed);
/**
    Aplica a tabela mapeada à string original

    @param
        encodedSymbols : Mapa para os simbolos e seus códigos
        symbols : Texto original

    @return String codificada
*/
string applyCodesToString(map<char,string> &encodedSymbols, string &symbols);
#endif // HUFFMAN_HPP_INCLUDED
