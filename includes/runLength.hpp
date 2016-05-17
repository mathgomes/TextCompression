/**
    UNIVERSIDADE DE S�O PAULO - ICMC
    DEPARTAMENTO DE CI�NCIAS DE COMPUTA��O
    SCC0261 Multim�dia - 1o Sem/2016

    @author Matheus Gomes da Silva Horta - 8532321
            B�rbara Darques Barros       - 7243081
*/
#ifndef RUNLENGTH_HPP_INCLUDED
#define RUNLENGTH_HPP_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
/**
    Codifica a string de entrada pelo metodo run length e a comprime
    @param
        fInput_name : Nome do arquivo de entrada
        inputText : String de entrada
        compressedOut : String comprimida de saida no formato ( todos os caracteres + todas as repeti��es)
        output : Arquivo de saida para se guardar valores necessario para decodifica��o

*/
void RLencode(string &fInput_name, FILE *output, string *compressedOut);
string RLdecode(string *compressedString, int *maxBitQtd, int *charactersQtd);
#endif // RUNLENGTH_HPP_INCLUDED
