/**
    UNIVERSIDADE DE SÃO PAULO - ICMC
    DEPARTAMENTO DE CIÊNCIAS DE COMPUTAÇÃO
    SCC0261 Multimídia - 1o Sem/2016
    huffman.cpp
    Objetivo: Codificar e decodificar cadeias de caracteres
    usando o método de Huffman.

    @author Matheus Gomes da Silva Horta - 8532321
            Bárbara Darques Barros       - 7243081
*/
#include"huffman.hpp"
#include "compressor.hpp"

using namespace std;



void HUFencode(string& simbols,string& resultHUF, string &header) {


    int size_tree = 0;

    map<char,short> symbolAndFreq = setFrequencies(simbols);
    map<char,string> symbolAndCode = generateTree(symbolAndFreq,header,&size_tree);
    resultHUF = applyCodesToString(symbolAndCode,simbols);

}

char* HUFcompress(string& resultHUF, int *sizeCompressed) {

    char *compressedHUF;

    vector<bool> binaryHUF = stringToBinary(resultHUF);
    compressedHUF = compressBooleanArray(binaryHUF,sizeCompressed);
    return compressedHUF;

}
void writeToFileHUF(string &header, string &output, int *sizeCompressed,
char *compressedHUF) {

    FILE *arq;
    arq = fopen(output.c_str(),"wb+");
    // escreve o header
    fwrite(&header[0],header.size(),1,arq);
    // escreve o tamanho do vetor comprimido de códigos
    fwrite(sizeCompressed,sizeof(int),1,arq);
    // escreve o vetor comprimido de códigos
    fwrite(&compressedHUF[0],*sizeCompressed * sizeof(char),1,arq);

    fclose(arq);
}

string applyCodesToString(map<char,string>& encodedSymbols, string &symbols) {

    string resultAux;
    for( char s : symbols) {
        resultAux += encodedSymbols.at(s);
    }

    return resultAux;
}

void generateCodes(treeNode *root,map<char,string> *encodedSymbols,
    string code, string &header, int* size_tree){
        if(!root->left && !root->right) {
            // Adiciona ao header o identificador de nó interno e o símbolo desse nó
            header += '1';
            header += root->symbol;
            *size_tree += 2*sizeof(char);
            printf("%c %s\n",root->symbol, code.c_str());
            encodedSymbols->insert(pair<char,string>(root->symbol,code.c_str()));
            return;
        }
        if(root->symbol == '$') {
        // Adiciona ao header o identificador de nó folha e o símbolo desse nó
            header += '0';
            *size_tree += sizeof(char);
            generateCodes(root->left,encodedSymbols,code + '0',header, size_tree);
            generateCodes(root->right,encodedSymbols,code + '1',header,size_tree);

        }
}

treeNode* inicializeNode(char symbol, short freq){
    treeNode *node = new treenode;
    node->symbol = symbol;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

map<char,short> setFrequencies(string &symbols) {

    map<char,short> symbolAndFreq;
    pair<map<char,short>::iterator,bool> ret;

    for(char& s : symbols) {
        ret = symbolAndFreq.insert ( pair<char,short>(s,1) );
        // se ja existir aquele simbolo no mapa, aumente a frequencia dele
        if (ret.second==false) {
            ret.first->second++;
        }
    }


    return symbolAndFreq;
}

map<char,string> generateTree(map<char,short> &symbols, string &header,
    int *size_tree) {

    map<char,string> encodedSymbols;
    map<char,short>::iterator it;
    treeNode *left, *right, *top;

     //Cria uma fila de prioridades e insere todos os nós
    priority_queue<treeNode*, vector<treeNode*>, compare> minHeap;
    for (it = symbols.begin(); it != symbols.end(); it++) {
        minHeap.push(inicializeNode(it->first,it->second));
    }

    while (minHeap.size() != 1) {

        // Extrai os nós com menor frequencia da min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Cria um novo nó interno com frequencia igual a soma dos anteriores
        // "$" caracter identificador de nó interno
        top = inicializeNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }


    generateCodes(minHeap.top(),&encodedSymbols,"",header,size_tree);
    // Adiciona o tamanho da arvore ao header
    ostringstream oss;
    oss << *size_tree;
    header.insert(0,oss.str());
    return encodedSymbols;
}


