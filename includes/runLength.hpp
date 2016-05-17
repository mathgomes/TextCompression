/**
    UNIVERSIDADE DE SÃO PAULO - ICMC
    DEPARTAMENTO DE CIÊNCIAS DE COMPUTAÇÃO
    SCC0261 Multimídia - 1o Sem/2016

    @author Matheus Gomes da Silva Horta - 8532321
            Bárbara Darques Barros       - 7243081
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
        compressedOut : String comprimida de saida no formato ( todos os caracteres + todas as repetições)
        output : Arquivo de saida para se guardar valores necessario para decodificação

*/
void RLencode(string &fInput_name, FILE *output, string *compressedOut);
string RLdecode(string *compressedString, int *maxBitQtd, int *charactersQtd);
#endif // RUNLENGTH_HPP_INCLUDED
