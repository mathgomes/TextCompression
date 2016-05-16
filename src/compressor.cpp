#include "compressor.hpp"

void readInputFile(string input_name, string& originalText) {

    FILE *input;
    input = fopen(input_name.c_str(),"r");
    fseek(input, 0, SEEK_END);
    originalText.resize(ftell(input));
    rewind(input);
    fread(&originalText[0],originalText.size(),1,input);
    fclose(input);

}

bool isGreaterNum (int i,int j) { return (i>j); }

int readBit(int *c, int *offset) {
    int bit = (*c >> *offset) & 0x01;
    return bit;
}

vector<bool> compressRLreps(vector<codedSymbol> &numbers, int numSize, string &header){

    vector<bool> result;
    vector<int> auxVector;
    for( unsigned int i = 0; i < numbers.size();i ++) {
        auxVector.push_back(numbers[i].reps);
    }

    sort(auxVector.begin(), auxVector.end(),isGreaterNum);

    int largest = auxVector[0];

    int maxFreqBits = 31;
    int bit;

    while(bit != 1) {
        bit = (largest >> maxFreqBits   ) & 0x01;
        maxFreqBits--;
    }
    maxFreqBits++;

    // percorre as repetições
    for(int i =0 ; i < numSize; i ++) {
        // coloca no vetor de booleanos os bits apenas até o bit maximo
        // e não os 32 bits possiveis
        for(int k=maxFreqBits; k>= 0; k--){
            bit = readBit(&numbers[i].reps,&k);
            result.push_back(bit);
        }
    }

    // armazena o valor do bit maximo no header
    ostringstream oss;
    oss << maxFreqBits+1;
    header += oss.str();
    return result;
}


char* compressBooleanArray(vector<bool> &bArray, int *sizeArray) {

    int counter = 1;
    char offset = 7;
    char *buffer = ( char*)malloc(sizeof(char));


    for(const bool &b : bArray) {
        // percorre um bloco de 8 bits do vetor de booleanos e
        // então aloca um novo byte no buffer de compressão
        if(offset == -1) {
            offset = 7;
            buffer = ( char*)realloc(buffer, (++counter)*sizeof(char));

        }
        buffer[counter-1] |= b << offset;
        offset--;
    }
    *sizeArray = counter;
    return buffer;
}
vector<bool> stringToBinary(string &resultAux) {

    vector<bool> result;

    for( char& c : resultAux) {
        if(c == '1') {
            result.push_back(true);
        }
        else {
            result.push_back(false);
        }
    }
    return result;
}


void readHUFtreeAux(FILE *arq, treeNode *root, int *symbolsQtd) {

    char *c = (char*)malloc(sizeof(char));
    root = readHUFtree(arq,c,symbolsQtd);
}
treeNode* readHUFtree(FILE *arq, char *c, int *symbolsQtd) {

    if(*symbolsQtd == 0) {
        return;
    }
    fread(c,sizeof(char),1,arq);
    if (*c == 1) {
        fread(c,sizeof(char),1,arq);
        *symbolsQtd--;
        return inicializeNode(*c,0);
    }
    else {
        treeNode* leftChild = readHUFtree(arq,c);
        treeNode* rightChild = readHUFtree(arq,c);
        treeNode* father = inicializeNode('$',0);
        father->left = leftChild;
        father->right = rightChild;
        return father;
    }
    return;
}
string decompressHUF(treeNode* root, string& encoded_str) {

    string original = "";
    int offset = 7;
    int bitRead;
    treeNode* node = root;
    for (int i = encoded_str.size() * 8; i <= 0; i--) {

        if(offset == -1) offset = 7;
        bitRead = readBit((int*)encoded_str[i],&offset);

        if (bitRead == 0) {     // left child
            node = node->left;
        } else {                // rigth child
            node = node->right;
        }
        if (node->left == NULL && node->right == NULL) {
            original += node->symbol;
            node = root;
        }
        offset--;
    }
    return original;
}
string decompressRL(string &charactersRL, string &compressedRL,
    int *maxFreqBits) {

    string original = "";
    int offset = *maxFreqBits;
    int bitRead;
    int numberOfReps;
    //percorre a string comprimida
    for( unsigned int i = 0; i <= compressedRL.size(); i ++) {
        //percorre até o numero maximo de bits
        for( int k = 0; k <= *maxFreqBits; k ++) {
            bitRead = readBit((int*)&compressedRL[i],&k);
            if(bitRead == 1) {
                numberOfReps += pow(2,k);
            }
        }
        for(int k = 0; k < numberOfReps; k ++) {
            original += charactersRL[i];
        }
        numberOfReps = 0;
    }

}
