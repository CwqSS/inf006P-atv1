#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct point {
    double x;
    double y;
    double euclidianDistanceToOrigin;
} point;

void writeOutput(char * line, FILE * output, int lineNumber);
void writeStrings(FILE * output, char strings[500][500], int count);
void writeIntegers(FILE * output,  int * integers, int count);
void writeFloats(FILE * output,  float * floats, int count);
void writePoints(FILE * output,  point * points, int count);
void extractWord(char * array, int * indexes);
void copySubStr(char * line, char * word, int init, int limit);
void copySubStrMatrix(char * line, char word[500][500], int row, int init, int limit);
void insertion_sort_point(point * array, int size);
void insertion_sort_int(int * array, int size);
void insertion_sort_float(float * array, int size);
void insertion_sort_strings(char array[500][500], int size);
int isPoint(char * word);
int isFloat(char * word);
int isInteger(char * word);
int verifyType(char * word);
double strToNumber(char * str);
double euclidianDistanceToTheOrigin(point p);
point strToPoint(char * str);

int main() {
    char * line = malloc(1001 * sizeof(char));
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

    char strings[500][500];
    int * integers = malloc(1000 * sizeof(int));
    float * floats = malloc(1000 * sizeof(float));
    point * points = malloc(1000 * sizeof(point));
    int i = 0, f = 0, sRow = 0, p = 0;


    while(line[indexes[1]] != '\n' && line[indexes[1]]) {
        extractWord(line, indexes);
        char * word = malloc(sizeof(char) * (indexes[1] - indexes[0]));
        copySubStr(line, word, indexes[0], indexes[1]);
        result = verifyType(word);
        
        if(result == 0){ 
            point newP = strToPoint(word);
            points[p] = newP;
            p = p + 1;
        }
        else if(result == 1) {
            float number = (float) strToNumber(word);
            floats[f] = number;
            f = f + 1;
        }
        else if(result == 2) {
            int number = (int) strToNumber(word);
            integers[i] = number;
            i = i + 1;
        }
        else if(result == 3) {
            copySubStrMatrix(word, strings, sRow, 0, 500);
            sRow = sRow + 1;
        }
    }

    insertion_sort_int(integers, i);
    insertion_sort_float(floats, f);
    insertion_sort_point(points, p);
    insertion_sort_strings(strings, sRow);

    if(lineNumber > 1) {
        fprintf(output, "\n");
    }

    writeStrings(output, strings, sRow);
    writeIntegers(output, integers, i);
    writeFloats(output, floats, f);
    writePoints(output, points, p);
}

void extractWord(char * array, int * indexes) {
    int i;
    for(i = indexes[1] + 1; array[i] && array[i] != ' ' && array[i] != '\n'; i = i + 1);
    indexes[0] = indexes[1] == 0 ? indexes[1] : indexes[1] + 1;
    indexes[1] = i;
}

void copySubStr(char * line, char * word, int init, int limit) {
    int j = 0;
    for(int i = init; i < limit && line[i]; i = i + 1, j = j + 1) {
        word[j] = line[i];
    }
    word[j] = '\0';
}

void copySubStrMatrix(char * line, char word[500][500], int row, int init, int limit) {
    int j = 0;
    for(int i = init; i < limit && line[i]; i = i + 1, j = j + 1) {
        word[row][j] = line[i];
    }
    word[row][j] = '\0';
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

double strToNumber(char * str) {
    double number = 0;
    int isNegative = 0;
    int i = 0;

    if(str[0] == '-') {
        isNegative = 1;
        i = 1;
    }

    double b10 = 10;
    int afterDot = 0;
    for(i; str[i]; i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            if(afterDot) {
                number = number + ((str[i] - '0') / b10);
                b10 = b10 * 10;
            }
            else
                number = number * b10 + str[i] - '0';
        }
        else if(str[i] == '.') {
            afterDot = 1;
            b10 = 10;
        }
    }

    if(isNegative)
        number = number * -1;

    return number;
}

point strToPoint(char * str) {
    point p;
    char number[30];
    int formatCharsPositions[3], f = 0;

    for(int i = 0; str[i]; i++) {
        if(str[i] == '(' || str[i] == ',' || str[i] == ')') {
            formatCharsPositions[f++] = i;
        } 
    }
    copySubStr(str, number, formatCharsPositions[0] + 1, formatCharsPositions[1]);
    p.x = strToNumber(number);
    copySubStr(str, number, formatCharsPositions[1] + 1, formatCharsPositions[2]);
    p.y = strToNumber(number);
    p.euclidianDistanceToOrigin = euclidianDistanceToTheOrigin(p);

    return p;
}

double euclidianDistanceToTheOrigin(point p) {
    return sqrt(pow(p.x, 2) + pow(p.y, 2));
}


void writeStrings(FILE * file, char strings[500][500], int count) {
    fprintf(file, "str:");
    for(int i = 0; i < count; i++) {
        if(i >= 1) {
            fprintf(file, " ");
        }
        fprintf(file, "%s", strings[i]);
    }
}
void writeIntegers(FILE * file,  int * integers, int count) {
    fprintf(file, " ");
    fprintf(file, "int:");
    for(int i = 0; i < count; i++) {
        if(i >= 1) {
            fprintf(file, " ");
        }
        fprintf(file, "%d", integers[i]);
    }
}
void writeFloats(FILE * file,  float * floats, int count) {
    fprintf(file, " ");
    fprintf(file, "float:");
    for(int i = 0; i < count; i++) {
        if(i >= 1) {
            fprintf(file, " ");
        }
        fprintf(file, "%.2f", floats[i]);
    }
}
void writePoints(FILE * file,  point * points, int count) {
    fprintf(file, " ");
    fprintf(file, "p:");
    for(int i = 0; i < count; i++) {
        if(i >= 1) {
            fprintf(file, " ");
        }
        fprintf(file, "(%.2f,%.2f)", points[i].x, points[i].y);
    }
}

void insertion_sort_point(point * array, int size) {
    for(int j = 1; j < size; j++) {
        int i = j - 1;
        point key = array[j];
        while(i > -1 && array[i].euclidianDistanceToOrigin > key.euclidianDistanceToOrigin) {
            array[i + 1] = array[i];
            i = i - 1;
        } 
        array[i + 1] = key;
    }
}

void insertion_sort_int(int * array, int size) {
    for(int j = 1; j < size; j++) {
        int i = j - 1;
        int key = array[j];
        while(i > -1 && array[i] > key) {
            array[i + 1] = array[i];
            i = i - 1;
        } 
        array[i + 1] = key;
    }
}

void insertion_sort_float(float * array, int size) {
    for(int j = 1; j < size; j++) {
        int i = j - 1;
        float key = array[j];
        while(i > -1 && array[i] > key) {
            array[i + 1] = array[i];
            i = i - 1;
        } 
        array[i + 1] = key;
    }
}

void insertion_sort_strings(char array[500][500], int size) {
    for(int j = 1; j < size; j++) {
        int k = 0;
        int i = j - 1;
        char * key = malloc(sizeof(char) * 500);
        copySubStr(array[j], key, 0 , 500);
        while(i > -1 && array[i][k] >= key[k]) {
            while(array[i][k] == key[k]) {
                k = k + 1;
            }
            if(array[i][k] > key[k]) {
                copySubStr(array[i], array[i + 1], 0, 500);
                i = i - 1;
            }
        } 
        copySubStr(key, array[i + 1], 0, 500);
    }
}