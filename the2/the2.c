#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int not_in_here(char *p, int length, char letter){
    int i;
    for (i=0; i<length; i++){
        if (p[i] == letter){
            return 0;
        }
    }
    return 1;
}

void sequence(char *p, int length){
    int i,j,t;
    for (i=0; i<length; i++){
        for (j=0; j<length; j++){
            if (p[j] > p[i]){
                t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
}

int value_of_letter(char *p1, char *p2, char n){
    int i;
    for (i=0; ; i++){
        if (p1[i] == n){
            if (p2[i] == 'T'){
                return 1;
            }
            else {
                return 0;
            }
        }
    }
}

char *curpos;
int read_and_eval_from_curpos(char *p1, char *p2){
    int left, right;
    char op;
    if (*curpos == '('){
        curpos++;
        left = read_and_eval_from_curpos(p1, p2);
        op = *curpos++;
        right = read_and_eval_from_curpos(p1, p2);
        curpos++;

        switch (op){
            case '&': return (left && right);
                break;
            case '|': return (left || right);
                break;
            case '=': return (left == right);
                break;
            case '>': {
                if ((left == 1) && (right == 0)){
                    return 0;
                }
                else return 1;
                break;
            }
        }
    }
    
    else {
        if (*curpos == '-'){
            curpos++;
            left = (!read_and_eval_from_curpos(p1,p2));
        }
        else {
            left = value_of_letter(p1, p2, *curpos);
            curpos++;
        }
        return left;
    }
}


int eval(char *p, char *p1, char *p2){
    curpos = p;
    return read_and_eval_from_curpos(p1,p2);
}


int main(){
    int element, i, h, b, k, length_of_str=0, length_of_ch=1, result;
    char *string, *characters, *truth_table;
    string = (char*)malloc(sizeof(char));
    characters = (char*)calloc(1, sizeof(char));
    for (i=1; (element = getchar()) != EOF; ){
        if ((element != ' ') && (element != '\n')){
            string = realloc(string, sizeof(char)*i);
            string[i-1] = element;
            length_of_str++;
            i++;
        }
    }
    length_of_str++;
    string = realloc(string,sizeof(char)*length_of_str);
    string[length_of_str-1]=0;
    for (i=0; i<length_of_str-1; i++){
        if ((string[i] > 96) && (string[i] < 123)){
            if (characters[0] == 0){
                characters[0] = string[i];
            }
            else if (not_in_here(characters, length_of_ch, string[i])){
                length_of_ch++;
                characters = realloc(characters, length_of_ch);
                characters[length_of_ch-1] = string[i];
            }
        }
    }
    sequence(characters,length_of_ch);
    length_of_ch+=2;
    characters = realloc(characters,sizeof(char)*length_of_ch);
    characters[length_of_ch-2] = 'R';
    characters[length_of_ch-1] = 0;

    truth_table = (char*)malloc(sizeof(char)*length_of_ch);
    for (i=0; i<length_of_ch-2; i++){
        truth_table[i] = 'T';
    }
    truth_table[length_of_ch-2] = 0;
    
    for (k=0; k<length_of_ch-2; k++){
            printf("%c ",characters[k]);
        }
        printf("%c\n",characters[length_of_ch-2]);

    for (i=0; i<(int)pow(2,length_of_ch-2); i++){
        for (h=length_of_ch-3, b=0; h>=0; b++, h--){
            if (i == 0);
            else if (i % (int)pow(2, h) == 0){
                if (truth_table[b] == 'T'){
                    truth_table[b] = 'F';
                }
                else {
                    truth_table[b] = 'T';
                }
            }
        }
        
        result = eval(string, characters, truth_table);
        if (result == 1){
            truth_table[length_of_ch-1] = 'T';
        }
        else {
            truth_table[length_of_ch-1] = 'F';
        }

        for (k=0; k<length_of_ch-2; k++){
            printf("%c ",truth_table[k]);
        }
        printf("%c\n",truth_table[length_of_ch-1]);
    }
    
    return 0;
    
}