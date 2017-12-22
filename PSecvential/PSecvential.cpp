// PSecvential.cpp : 
// tutorial : https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M

#include "stdafx.h"
#include "mergeSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

static unsigned  get_file_size(const char * file_name) {
	struct stat st;
	if(stat(file_name, &st) != 0) {
		fprintf(stderr, "error when you try to see the size of the file %s : %s \n", file_name, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return st.st_size;
}

char *pathFile = "D:\\Facultate\\Master\\Programarea paralela si concurenta\\Proiect\\PSecvential\\date.txt";
char *pathFile2 = "D:\\Facultate\\Master\\Programarea paralela si concurenta\\Proiect\\PSecvential\\fisierCriptat.txt";
char *pathFile3 = "D:\\Facultate\\Master\\Programarea paralela si concurenta\\Proiect\\PSecvential\\fisierDupaDecriptare.txt";

int generateRandom(int max) {
	return rand() % max;
}


void cryptFile(char *pathFile, char *pathFile2, vector<int> &randomVector, vector<int> &sortedVector) {
	FILE *f1 = fopen(pathFile, "r+");
	FILE *f2 = fopen(pathFile2, "w");
	if (f1 == NULL) {
		printf("can't open the file");
		return;
	}

	std::vector<int> copyRandomVector(randomVector.size(),-2);
	std::vector<int> copySortedVector(sortedVector.size(),-1);
	int k = 0; // copySortedVector indice

	for (int i = 0; i < sortedVector.size(); i++) {
		for (int j = 0; j < randomVector.size(); j++) {
			if (sortedVector[i] == randomVector[j]) {
				fseek(f1, j, SEEK_SET);
				char c = fgetc(f1);
				char specialCases[] = { '\n', '\t'};
				if (c == specialCases[0] || c == specialCases[1]) {
					fputc(c, f2);
					copySortedVector[k] = sortedVector[i]; k++;
					copyRandomVector[j] = randomVector[j];
					randomVector[j] = -1;
					if (j != 0) {
						fseek(f1, j - 1, SEEK_SET);
						c = fgetc(f1);
						if (c == '\n') {
							randomVector[j - 1] = -1;
						}
					}
					if (j + 1 < sortedVector.size()) {
						fseek(f1, j + 1, SEEK_SET);
						c = fgetc(f1);
						if (c == '\n') {
							randomVector[j + 1] = -1;
						}
					}
				} else {
					fputc(c, f2);
					copyRandomVector[j] = randomVector[j];
					randomVector[j] = -1;
					copySortedVector[k] = sortedVector[i]; k++;
					break;
				   }
				}
		}
	}
	sortedVector = copySortedVector;
	randomVector = copyRandomVector;
	fclose(f1);
	fclose(f2);
}


void decryptFile(char *pathFile2, char *pathFile3, vector<int> &randomVector, vector<int> &sortedVector) {
	FILE *f2 = fopen(pathFile2, "r+"); // criptat
	FILE *f3 = fopen(pathFile3, "w"); // decriptat
	if (f2 == NULL) {
		printf("can't open the file");
		return;
	}

	for (int i = 0; i < randomVector.size(); i++) {
		for (int j = 0; j < sortedVector.size(); j++) {
			if (sortedVector[j] == randomVector[i]) {
				fseek(f2, 0, SEEK_SET);
				int aux = j;
				char c;
				if (aux == 0) c = fgetc(f2);
				else {
					while (aux != -1) {
						c = fgetc(f2);
						aux--;
					}
				}
				fputc(c, f3);
				sortedVector[j] = -1;
				break;
			}
		}
	}
	
	
	fclose(f2);
	fclose(f3);
}



int main() {
	srand(time(NULL)); // need to be executed only 1 time
	// generate random vector
	long int fileSize = get_file_size(pathFile);
	std::vector<int> randomVector(fileSize);
	for (int i = 0; i < randomVector.size(); i++) {
		randomVector[i] = generateRandom(fileSize);
	}
	std::vector<int> sortedVector(randomVector);

	// sorting random vector
	mergeSort(sortedVector, fileSize); 
	

	printf("vectorul randomizat: \n");
	printArray(randomVector, fileSize);
	printf("sorted vector: \n");
	printArray(sortedVector, fileSize);

	// criptare fisier
	cryptFile(pathFile, pathFile2, randomVector, sortedVector);

	// decriptare fisier
	decryptFile(pathFile2, pathFile3, randomVector, sortedVector);
	
    return 0;
}

