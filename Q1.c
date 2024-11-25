#include <stdio.h>
#include <stdlib.h>
#include "Q1.h"

int main() {

    FILE* L0Q1 = fopen("L0Q1.txt", "r");

    if(L0Q1 == NULL) {
        printf("Nao foi possivel ler/encontrar o arquivo de entrada.");
        return 1;
    }

    FILE* RL0Q1 = fopen("RL0Q1.txt", "w");
    if(L0Q1 == NULL) {
        printf("Nao foi possivel abrir/criar o arquivo de saida.");
        return 1;
    }
    char* line = malloc(sizeof(char) * 256);

    while(fscanf(L0Q1, "%s", line) == 1) {
        if(strStr(line, "points")) {
            int count = 0;
            double distance = 0;
            point* points = malloc(sizeof(point) * MAX_POINT);
            point p;
            while(fscanf(L0Q1, " (%lf, %lf)", &p.x, &p.y) == 2) {
                if(count > 0) {
                    distance += euclidianDistanceBtw2Points(points[count - 1], p);
                }
                p.euclidianDistanceToOrigin = euclidianDistanceToTheOrigin(p);
                points[count] = p;
                count = count + 1;
            }
            if(count > 0) {
                distance_insertion_sort(points, count);
                double shortcut = euclidianDistanceBtw2Points(points[0], points[count - 1]);
                fprintf(RL0Q1, "points ");
                for(int i = 0; i < count; i++) {
                    point a = points[i];
                    fprintf(RL0Q1, "(%.2f, %.2f) ", a.x, a.y);
                }
                fprintf(RL0Q1, "distance %.2f ", distance);
                fprintf(RL0Q1, "shortcut %.2f\n", shortcut);
            }
        }
    }

    fclose(L0Q1);
    fclose(RL0Q1);

    printf("Processo finalizado.");
}


int strStr(char * str, char * Str) {
    int isEqual = 1;
    for(int i = 0; str[i]; i++) {
        if(str[i] != Str[i]) {
            isEqual = 0;
        }
    }
    return isEqual;
}

double euclidianDistanceToTheOrigin(point p) {
    return sqrt(pow(p.x, 2) + pow(p.y, 2));
}
double euclidianDistanceBtw2Points(point p1, point p2) {
    return sqrt(pow((p1.x - p2.x), 2.0) + pow((p1.y - p2.y), 2.0));
}
void distance_insertion_sort(point * p, int size) {
    for(int j = 1; j < size; j++) {
        int i = j - 1;
        point key = p[j];
        while(i > -1 && p[i].euclidianDistanceToOrigin > key.euclidianDistanceToOrigin) {
            p[i + 1] = p[i]; 
            i = i - 1;
        }
        p[i + 1] = key;
    }
}