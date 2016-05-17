/**
    UNIVERSIDADE DE S�O PAULO - ICMC
    DEPARTAMENTO DE CI�NCIAS DE COMPUTA��O
    SCC0261 Multim�dia - 1o Sem/2016
    huffman.hpp
    Objetivo: Codificar e decodificar cadeias de caracteres
    usando o m�todo de Huffman.

    @author Matheus Gomes da Silva Horta - 8532321
            B�rbara Darques Barros       - 7243081
*/
#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED

#include<string>
#include<cstdio>
#include<algorithm>
#include<fstream>
using namespace std;
/**
    Le o arquivo de entrada e armazena seu conteudo na strin de entrada
    @param
        fInput_name : Nome do arquivo de entrada
        inputText : String de entrada

*/
void readInputFile(string& fInput_name,string &inputText);

bool isGreaterNum (int i,int j);

/**
    Le um bit de uma entrada
    @param
        c : Entrada a ter o bit lido
        offset : Deslocamento da direita para esquerda
*/
int readBit(int *c, int *offset);

/**
    Comprime um vetor de booleanos em blocos de 8 bytes e coloca numa string
*/
string compressBooleanArray(vector<bool> &bArray);

#endif // UTIL_HPP_INCLUDED
