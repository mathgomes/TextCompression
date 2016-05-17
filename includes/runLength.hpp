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

void RLencode(string &fInput_name, fstream& output, string *compressedOut);
string RLdecode(string *compressedString, int *maxBitQtd, int *charactersQtd);
#endif // RUNLENGTH_HPP_INCLUDED
