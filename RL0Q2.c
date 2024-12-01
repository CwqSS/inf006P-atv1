#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    double x;
    double y;
    double euclidianDistanceToOrigin;
} point;

void writeOutput(char * line, FILE * output, int lineNumber);
void extractWord(char * array, int * indexes);
void printStr(char * array, int init, int limit);
void copySubStr(char * line, char * word, int init, int limit);
int addSubStrToStr(char * line, char * word, int index, int space, int maxLength);
int isPoint(char * word);
int isFloat(char * word);
int isInteger(char * word);
int verifyType(char * word);

int main() {
    char * line = malloc(1000 * sizeof(char));
    int lineNumber = 1;

    FILE * input;
    FILE * output;

    input = fopen("L0Q2.in", "r");
    output = fopen("L0Q2.out", "w");

    if(input == NULL || output == NULL) {
        printf("ALgum erro ao ler os arquivos.");
        return EXIT_FAILURE;
    }

    while(fgets(line, 1000, input)) {
        writeOutput(line, output, lineNumber);
        lineNumber += 1;
    }

    fclose(input);
    fclose(output);

    return EXIT_SUCCESS;
}

void writeOutput(char * line, FILE * output, int lineNumber) {
    int result;
    int indexes[2] = {0, 0};

    char * text = malloc(1000 * sizeof(point));
    char * points = malloc(1000 * sizeof(point));
    char * floats = malloc(1000 * sizeof(float));
    char * integers = malloc(1000 * sizeof(int));
    char * strings = malloc(1000 * sizeof(char));
    int i = 0, f = 0, s = 0, p = 0;

    points[0] = floats[0] = integers[0] = strings[0] = '\0';

    while(line[indexes[1]] != '\n' && line[indexes[1]]) {
        extractWord(line, indexes);
        char * word = malloc(sizeof(char) * (indexes[1] - indexes[0]));
        copySubStr(line, word, indexes[0], indexes[1]);
        result = verifyType(word);
        
        if(result == 0){ 
            int space = p == 0 ? 0 : 1;
            p = addSubStrToStr(points, word, p, space, 1000);
        }
        else if(result == 1) {
            int space = f == 0 ? 0 : 1;
            f = addSubStrToStr(floats, word, f, space, 1000);
        }
        else if(result == 2) {
            int space = i == 0 ? 0 : 1;
            i = addSubStrToStr(integers, word, i, space, 1000);
        }
        else if(result == 3) {
            int space = s == 0 ? 0 : 1;
            s = addSubStrToStr(strings, word, s, space, 1000);
        }
    }
    
    if(lineNumber > 1) {
        fprintf(output, "\n");
    }

    fprintf(output, "str:%s ", strings);
    fprintf(output, "int:%s ", integers);  
    fprintf(output, "float:%s ", floats);  
    fprintf(output, "p:%s ", points);  
}

void extractWord(char * array, int * indexes) {
    int i;
    for(i = indexes[1] + 1; array[i] && array[i] != ' ' && array[i] != '\n'; i = i + 1);
    indexes[0] = indexes[1] == 0 ? indexes[1] : indexes[1] + 1;
    indexes[1] = i;
}

void copySubStr(char * line, char * word, int init, int limit) {
    int j = 0;
    for(int i = init; i < limit; i = i + 1, j = j + 1) {
        word[j] = line[i];
    }
    word[j] = '\0';
}

int isPoint(char * word) {
    int isPoint = 0;
    if(word[0] == '(')
        isPoint = 1;
    return isPoint;
}

int isFloat(char * word) {
    int isFloat = 0;
    for(int i = 0; word[i] && !isFloat; i++) {
        if(word[i] == '.')
            isFloat = 1;
    }
    return isFloat;
}

int isInteger(char * word) {
    int isInteger = 1;
    int i = word[0] == '-' ? 1 : 0; 
    for(i; word[i] && isInteger; i++) {
        if(word[i] < '0' || word[i] > '9') {
            isInteger = 0;
        }
    }
    return isInteger;
}

int verifyType(char * word) {
    int result = 3;
    if(isPoint(word)) {
        result = 0;
    }
    else if(isFloat(word)) {
        result = 1;
    }
    else if(isInteger(word)) {
        result = 2;
    }
    return result;
}

int addSubStrToStr(char * line, char * word, int index, int space, int maxLength) {
    if(space && index != maxLength - 1) {
        line[index] = ' ';
        index += 1;
    }
    for(int i = 0; word[i] && index != maxLength - 1; i++) {
        line[index++] = word[i];
    }
    line[index] = '\0';
    return index;
}

void printStr(char * array, int init, int limit) {
    for(int i = init; i < limit; i++) {
        printf("%c", array[i]);
    }
}



