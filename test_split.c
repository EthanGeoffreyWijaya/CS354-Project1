#include <stdio.h>
#include "student_functions.h"


void Read_CSV(char *filename, char csv[10][1024], int *num_movies) {    
    FILE *fp;
    fp = fopen(filename, "r");
    fscanf(fp, "%d", num_movies);
    char read_rest_of_line[1024];
    fgets(read_rest_of_line, 1024, fp);
    for (int i=0; i<*num_movies; i++) 
        fgets(csv[i], 1024, fp);
    fclose(fp);
    return;
}

int Length_Of_Longest_String_soln(char str[10][1024], int num_movies) {
    int longest=0;
    for (int i = 0; i<num_movies; i++) {
        char *p = str[i];
        int n = 0;
        while (*p++) n++;
        if (n>longest) longest = n;
    }
    return longest;
}

void Print_Table_Soln(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    int title_length = Length_Of_Longest_String_soln(titles, num_movies)+2;
    if (title_length < 7) title_length = 7;

    int director_length = Length_Of_Longest_String_soln(directors, num_movies)+2;
    if (director_length < 10) director_length = 10;

    // print the header
    printf("%-3s%-*s%-6s%-*s%6s%11s\n","Id",title_length,"Title","Year",director_length,"Director","Rating","Revenue");    
    for (int i = 0; i<num_movies; i++) {
        printf("%-3d%-*s%-6d%-*s%6.1f%11lld\n",i+1,title_length,titles[i],years[i],director_length,directors[i],ratings[i],dollars[i]);    
    }

    return;
}


int main() {

    char csv[10][1024]; // data structure for the entire movie csv file
    int num_movies;
    char titles[10][1024];
    int years[10];
    char directors[10][1024];
    float ratings[10];
    long long dollars[10];
    
    char csv_file[256];
    scanf("%[^\n]", csv_file);
     
    Read_CSV(csv_file, csv, &num_movies);
    Split(csv, num_movies, titles, years, directors, ratings, dollars);
    Print_Table_Soln(num_movies, titles, years, directors, ratings, dollars);

    return 0;
}
