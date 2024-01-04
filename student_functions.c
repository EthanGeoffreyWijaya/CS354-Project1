/* name
 * uw net Id
*/

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"

int getSize(char str[]) {
	int i = 0;
	while(str[i] != '\0') {
		i++;
	}
	return i;
}
void Clean_Whitespace(char str[]) {
    int strSize = getSize(str);
    int i = 0;
    while (i < strSize) {
	   if(str[i] == '\t' || str[i] == '\n' || str[i] == '\r') {
		   arrayRemove(str, i, strSize--);
	   } else if(str[i] == ' ' && (str[i + 1] == ' ' || str[i - 1] == ' ')) {
		  arrayRemove(str, i, strSize--); 
	   }else {
		i++;   
	   }
    }
   if (str[0] == ' ') {
	arrayRemove(str, 0, strSize--);
   }
   if (str[strSize - 1] == ' ') {
	arrayRemove(str, strSize - 1, strSize);
	strSize--;
   }
    return;
}

void arrayRemove(char str[], int index, int size) {
	int i = 0;
	for (i = index + 1; i < size; i++) {
		str[i - 1] = str[i];
	}
	str[size - 1] = '\0';
		
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case(char str[]) {
	int diff = 'a' - 'A';
	int size = getSize(str);
        int i = 0;
	while (i < size) {
		if (i == 0 || str[i - 1] == ' ') {
		       	if (str[i] >= 'a' && str[i] <= 'z') { 
				str[i] -= diff;
			}
		} else if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += diff;
		}
		i++;
	}	
    return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    return atoi(str);
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {
    int size = getSize(str);
    int i = size - 1;
    while (i >= 0 && str[i - 1] != ' ') {
	i--;
    }
    for (int j = 0; j < i; j++) {
	arrayRemove(str, 0, size--);
    }
    return;
}


/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {
    return atof(str);
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
	long long suffixValue = 1;
	int size = getSize(str);
	//printf("%d%c\n", size, str[size - 1]);
    if (str[size - 1] == 'm' || str[size - 1] == 'M') {
	str[size - 1] = '\0';
	suffixValue = 1000000;
    } else if (str[size - 1] == 'k' || str[size - 1] == 'K') {
	str[size - 1] = '\0';
	suffixValue = 1000;
    }
    return atoll(str) * suffixValue;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
   for (int i = 0; i < num_movies; i++) {
	int state = 0;
	Fix_Case(csv[i]);
	int size = getSize(csv[i]);

	char dataStr[1024];
	int wordLength = 0;
	for (int j = 0; j < size; j++) {
		if (csv[i][j] != ',' && j != size - 1) {
			dataStr[wordLength++] = csv[i][j];
		} else {
			if (j == size - 1) {
				dataStr[wordLength++] = csv[i][j];
			}
			dataStr[wordLength] = '\0';
			Clean_Whitespace(dataStr);
			switch(state++) {
				case 0:
					sprintf(titles[i], "%s", dataStr);
					break;
				case 1:
					years[i] = String_To_Year(dataStr);
					break;
				case 3:
					Director_Last_Name(dataStr);
					sprintf(directors[i], "%s", dataStr);
					break;
				case 4:
					ratings[i] = String_To_Rating(dataStr);
					break;
				case 5:
					dollars[i] = String_To_Dollars(dataStr);
					break;
			}
			wordLength = 0;			
		}
	}
    }

    return;
}



/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    char title[] = "Title";
    char director[] = "Director";
    int longestTitle = getLongest(titles, num_movies) + 2;
    int longestDirector = getLongest(directors, num_movies) + 2;
    if (longestTitle < 7) {
	longestTitle = 7;
    }
    if (longestDirector < 10) {
	longestDirector = 10;
    }

    printf("Id %-*sYear  %-*sRating    Revenue\n", longestTitle, title, longestDirector, director);
    for (int i = 0; i < num_movies; i++) {
	printf("%-3d%-*s%-6d%-*s%6.1f%11llu\n", i + 1, longestTitle, titles[i], years[i], longestDirector, directors[i], ratings[i], dollars[i]);
    }
    return;
}

int getLongest(char list [10][1024], int num_movies) {
	int max = 0;
	for (int i = 0; i < num_movies; i++) {
		int length = getSize(list[i]);
		if (length > max) {
			max = length;
		}
	}
	return max;
}


