#include "runlength.h"

using namespace std;

void RLcompress(stringstream& input_ss, stringstream& output_ss){ // <quantidade> <caracter>
    int times = 0;
    char ch, prev;
    //caso especial pro primeiro caracter da string
    input_ss.get(prev);
    int count = 1; 
    
    while(input_ss.get(ch)){
        ++times;
        if(ch==prev){
            ++count;
        } else {
            // escreve quantidade
            output_ss.write((char*)&count, sizeof(int));
            // escreve qual caracter
            output_ss.write(&prev, sizeof(char));
            prev = ch;
            count = 1;
        }
    }
    // como no loop só se adiciona ao arquivo o char i qnd se está no i+1, o último vai sobrar
    // escreve dados do último caracter
    output_ss.write((char*)&count, sizeof(int));
    output_ss.write(&prev, sizeof(char));
}

void RLdecompress(stringstream& input_ss, stringstream& output_ss){
    int count;
    while(input_ss.read((char*)&count, sizeof(int))){
        char ch;
        input_ss.get(ch);
        string sequence(count, ch);
        output_ss.write(&sequence[0], count);
    }
    // arrumar último caracter
}
