#include "huffman.h"

using namespace std;

void applyHuffman(stringstream& input_ss, stringstream& output_ss){
    priority_queue<PAIR, vector<PAIR>, Comparator > ordered_freqs; // fila de prioridade de pairs<frequência, caracter>
    getOrderedFrequencies(input_ss, ordered_freqs, output_ss);
    // gera a árvore de Huffman
    while(ordered_freqs.size()>1){ 
        //cout<<ordered_freqs.top().first<<" times "<<ordered_freqs.top().second->ch<<endl;
        // pega os 2 nós de menor frequência
        node* left = ordered_freqs.top().second;
        ordered_freqs.pop();
        node* right = ordered_freqs.top().second;
        ordered_freqs.pop();
        //cout<<"["<<left->ch<<" "<<right->ch<<"]"<<endl;
        // cria um pai (um nó que só armazena a frequência acumulada)
        node* parent = new node;
        parent->left_child = left;
        parent->right_child = right;
        parent->freq = right->freq + left->freq;
        parent->ch = -1;
        // adiciona pai à lista de prioridade
        ordered_freqs.push(make_pair(parent->freq, parent));
    }
    node* root = ordered_freqs.top().second; // no final só sobra a raiz na fila
    root->code = "";
    map<char, string> codes; // códigos ordenados
    bfs(root, codes); // percorre a árvore criando os códigos
    //=================================
    // --- imprime códigos--- 
    //=================================
    // for(map<char,string>::iterator it = codes.begin(); it!=codes.end(); ++it){
    //   cout<<it->first<<" = "<<it->second<<endl;
    // }
    
    string codified = ""; // string resultante mas com chars '0' e '1'
    char ch;
    while(input_ss.get(ch)){ 
        codified += codes[ch];
    }
    int size = codified.size();
    while(size%8!=0){ // pra dar bytes inteiros
        codified += '0';
        ++size;
    }

    // transforma esses '0' e '1' em 0 e 1's lógicos de fato
    for(int i = 0; i<size; i+=8){ // de byte em byte
        unsigned char byte = 0; // 00000000
        string sub = codified.substr(i, 8);
        sub+='\0';
        for(int pos = 0; pos<8; ++pos){
            byte |= (sub[pos]=='1') << (7-pos);
        }
        //cout<<"string: "<<sub<<" binary: "<<bitset<8>(byte)<<endl;
        output_ss.put(byte);
    }
    
}

void getOrderedFrequencies(stringstream& input_ss, priority_queue<PAIR, vector<PAIR>, Comparator >& ordered_freqs, stringstream& output_ss){
    map<char, int> frequencies; // frequência de aparição de cada caracter
    char ch;
    while(input_ss.get(ch)){
        if(frequencies.count(ch)==0){ // se é primeira ocorrência desse caracter
            frequencies[ch] = 1;
        } else {
            ++frequencies[ch];
        }
    }
    int alphabet_size = frequencies.size();
    output_ss.write((char*)&alphabet_size, sizeof(int)); // coloca no arquivo comprimido quantos caracteres foram codificados
    for(map<char,int>::iterator it = frequencies.begin(); it!=frequencies.end(); ++it){
        //cout<<it->first<<" = "<<it->second<<endl;
        node* n = new node;
        n->freq = it->second;
        n->ch = it->first;
        n->right_child = nullptr;
        n->left_child = nullptr;
        ordered_freqs.push(make_pair(it->second, n)); // pairs <frequência, caracter>
        // salva o caracter e depois a frequência dele
        output_ss.write(&n->ch, sizeof(char));
        output_ss.write((char*)&n->freq, sizeof(int));
    }
    // volta pro começo da stream
    input_ss.clear(); // apaga as flags que indicavam que tinha chegado ao fim da stream
    input_ss.seekg(0, input_ss.beg);
}


void bfs(node* n, map<char, string>& codes){ 
    if(n==nullptr){
        cout<<"a raiz é nula. WUT!?"<<endl;
    } else if(n->left_child==nullptr && n->right_child==nullptr){ // se for uma folha, portanto um caracter de fato
        // cout<< n->ch <<" = "<< n->code << endl;
        codes[n->ch] = n->code;
    } else {
        // adiciona um bit a cada filho (esquerda sempre recebe 0 e direita 1)
        n->left_child->code = n->code + '0';
        n->right_child->code = n->code + '1';
        // continua busca até as folhas
        bfs(n->left_child, codes);
        bfs(n->right_child, codes);
    }
}


void decodeHuffman(stringstream& input_ss, stringstream& output_ss){
    int alphabet_size;
    input_ss.read((char*)&alphabet_size, sizeof(int));
    priority_queue<PAIR, vector<PAIR>, Comparator> ordered_freqs;
    for(int i=0; i<alphabet_size; ++i){
        char ch;
        int freq;
        input_ss.read(&ch, sizeof(char));
        input_ss.read((char*)&freq, sizeof(int));
        //cout<<ch<<" = "<<freq<<endl;
        node* n = new node;
        n->freq = freq;
        n->ch = ch;
        n->right_child = nullptr;
        n->left_child = nullptr;
        ordered_freqs.push(make_pair(freq, n)); // pairs <frequência, caracter>
    }
    while(ordered_freqs.size()>1){ 
        // pega os 2 nós de menor frequência
        node* left = ordered_freqs.top().second;
        ordered_freqs.pop();
        node* right = ordered_freqs.top().second;
        ordered_freqs.pop();
        //cout<<"["<<left->ch<<" "<<right->ch<<"]"<<endl;
        // cria um pai (um nó que só armazena a frequência acumulada)
        node* parent = new node;
        parent->left_child = left;
        parent->right_child = right;
        parent->freq = right->freq + left->freq;
        parent->ch = -1;
        // adiciona pai à lista de prioridade
        ordered_freqs.push(make_pair(parent->freq, parent));
    }
    node* root = ordered_freqs.top().second; // no final só sobra a raiz na fila
    root->code = "";
    map<char, string> codes; // códigos ordenados
    bfs(root, codes); // percorre a árvore criando os códigos
    
    // cria um mapa onde os códigos são as chaves
    map<string, char> respectiveChars;
    for(map<char,string>::iterator it = codes.begin(); it!=codes.end(); ++it){
            respectiveChars[it->second] = it->first;
    }

    char byte;
    string code = "";
    while(input_ss.get(byte)){
        string str = bitset<8>(byte).to_string(); // transforma byte em uma string de '0's e '1's
        for(int i = 0; i<8; ++i){
            code += str[i];
            if(respectiveChars.count(code)!=0){
                output_ss.put(respectiveChars[code]);
                code = "";
            }
        }
    }
}