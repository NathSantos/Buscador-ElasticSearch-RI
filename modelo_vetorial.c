#include <stdio.h>
#include <math.h>

#define N 4 //num docs
#define palavras {"A", "B", "C"}

struct documento{
    char nome[2];
    //char palavras[];   palavras contidas no documento
}typedef documento;



//quantas vezes aquela palavra aparece no documento
//recebe um documento e uma palavra retorna a frequencia dela nele
int tf(char documento[], char palavra, int tamanho_documento){
    int frequencia_palavra = 0;
    for(int i=0; i<tamanho_documento; i++){
        if (documento[i] == palavra){
            frequencia_palavra = frequencia_palavra + 1;
        }
    }
    return frequencia_palavra;
}

//avaliacao da importancia da palavra
float idf(int nt){
    return log(N / nt);
}



int main(){
    return 0;
}