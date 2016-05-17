#include "burrowswheeler.h"

using namespace std;

void BWTencode(string input_name, stringstream& output_ss, int std_block_size){
    ifstream input;
    input.open(input_name.c_str(), ios::binary | ios::in);
    if(!input.is_open()){
        cout<<"Arquivo de entrada não encontrado."<<endl;
        return;
    }
    int block_size = std_block_size;
    string original;
    original.resize(block_size);
    input.seekg(0, input.end);
    int size = input.tellg(); // tamanho do arquivo
    input.seekg(0, input.beg);
    int pos = 0;
    int final_block_size = size%std_block_size; // tamanho do último bloco de texto
    
    output_ss.write((char*)&final_block_size, sizeof(int)); // só um "placeholder", no final vai ser reescrito novamente o valor certo
    output_ss.write((char*)&block_size, sizeof(int)); // tamanho do bloco padrão

    while(input.read(&original[0], block_size)){
        priority_queue<string, vector<string>, greater<string> > rotations; // vai armazenar as strings ordenadas alfabeticamente
        for(int i=0; i<block_size; i++) {
            string str;
            str += original[i];
            for(int j=i+1; j!=i; j++) {
                if(j==block_size){
                    j=0;
                }
                str += original[j];
                if(j==block_size-1){
                    j=-1;
                }
            }
            rotations.push(str);
        }
        string coded; // string codificada
        int end_pos; // posição onde o último caracter da string vai ficar na string codificada
        int counter = 0;
        while(!rotations.empty()){
            coded.push_back(rotations.top()[block_size-1]);
            if(rotations.top().compare(original)==0){
                end_pos = counter;
            }
            rotations.pop();
            ++counter;
        }
        
        output_ss.write((char*) &end_pos, sizeof(int));
        output_ss.write(&coded[0], block_size);
        pos = input.tellg();
        if(block_size==final_block_size){ // se o bloco lido tiver sido o último do arquivo
            break;
        } else if(size-pos<block_size && (size-pos!=0)){ // se o último bloco do arquivo tiver que ser menor que o tamanho padrão
            block_size = final_block_size; 
            original.resize(final_block_size);
        }
    }
    
    input.close();
}

void BWTdecode(stringstream& input_ss, string output_name){
    ofstream output;
    
    input_ss.seekg(0, input_ss.end);
    int size = input_ss.tellg();
    input_ss.seekg(0, input_ss.beg);
    
    output.open(output_name.c_str(), ios::binary | ios::out);
    int final_block_size, block_size;
    input_ss.read((char*)&final_block_size, sizeof(int));
    input_ss.read((char*)&block_size, sizeof(int));
    int end_pos; // posição do último caractere da string original na string codificada
    int file_pos = 0;
    while(input_ss.read((char*)&end_pos, sizeof(int))){
        // traz bloco pra memória
        string last; // última coluna resultante da BWT
        last.resize(block_size);
        
        input_ss.read(&last[0], block_size);
        
        // cria as estruturas auxiliares
        map<char, int> how_many; // (K) quantos daquele caracter existem no bloco
        vector<int> n_before(block_size, -1); // (C) quantos daquele caracter antes da ocorrência i
        map<char, int> start; // (M) posição da primeira ocorrência de cada caracter
        
        for(int i=0; i<block_size; ++i){
            if(how_many.count(last[i])==0){ // se for primeira ocorrência do caracter
                start[last[i]] = -1; // insere no mapa pra depois ser percorrido e calculado
                n_before[i] = 0;
                how_many[last[i]] = 1;
            } else {
                n_before[i] = how_many[last[i]];
                ++how_many[last[i]];
            }
        }
        
        // gera as posições da primeira ocorrência de cada caracter
        int pos = 0;
        for(map<char,int>::iterator it=start.begin(); it!=start.end(); ++it){
            it->second = pos;
            pos += how_many[it->first];
        }
        
        // faz a decodificação de fato
        int i = end_pos;
        string original; // string decodificada
        original.resize(block_size);
        
        for(int j = block_size-1; j>=0; --j){
            original[j] = last[i];
            i = n_before[i] + start[last[i]];
        }
        
        // passa a string decodificada pro arquivo
        output.write(&original[0], block_size);
        file_pos = input_ss.tellg();
        //cout<<"["<<original<<"]"<<endl;
        if(block_size == final_block_size){ // significa que o bloco lido era o último
            
            break;
        } else if(size-file_pos==final_block_size+4){ // se for o último bloco
            block_size = final_block_size;
            //cout<<"["<<original<<"]"<<endl;
        }
        
    }
    
    output.close();
}
