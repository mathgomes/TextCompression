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

void RLencode(string &fInput_name, fstream& output, string *compressedOut);
string RLdecode(string *compressedString, int *maxBitQtd, int *charactersQtd);
#endif // RUNLENGTH_HPP_INCLUDED
