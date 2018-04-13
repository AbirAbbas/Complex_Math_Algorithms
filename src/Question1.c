#include <stdio.h>
#include <math.h>
#include "Question1.h"
#include <time.h>

void partQ1A() {
	
	char fileName[1024];
	int allNumbers[50000];
	int counter = 0;
	
	printf("Please enter a proper file-name to test!\n");
	scanf("%s", fileName);
	
	if (!fileExist(fileName)) {
		printf("File does not exist!\n");
		return;
	}
	
	FILE * inFile = fopen(fileName, "r+");
	
	//Takes in input
	while (fgets(fileName, 1024, inFile) != NULL) {
		sscanf(fileName, "%d %d %d %d %d", &allNumbers[counter], &allNumbers[counter + 1], &allNumbers[counter + 2], &allNumbers[counter + 3], &allNumbers[counter + 4]);
		counter+=5;
	}
	
	counter = 0;
	
	printf("Processing your request...\n");
	
	//Timer start
	clock_t begin = clock();
	
	for (int i = 0; i < 50000; i++) {
		
		for (int j = i + 1; j < 50000; j++) {
			//compares all values to each other and looks for inverses
			if (allNumbers[i] > allNumbers[j]) {
				counter++;
			}
		}
		
	}
	
	clock_t end = clock();
	
	double executionTime = (double)(end-begin) / (CLOCKS_PER_SEC);
	
	printf("Total inverses : %d\nTotal time : %lfs\n", counter, executionTime);
	
	
	
}

void partQ1B() {
	char fileName[1024];
	int allNumbers[50000];
	int counter = 0;
	
	printf("Please enter a proper file-name to test!\n");
	scanf("%s", fileName);
	
	if (!fileExist(fileName)) {
		printf("File does not exist!\n");
		return;
	}
	
	printf("Test\n");
	
	FILE * inFile = fopen(fileName, "r+");
	
	while (fgets(fileName, 1024, inFile) != NULL) {
		sscanf(fileName, "%d %d %d %d %d", &allNumbers[counter], &allNumbers[counter + 1], &allNumbers[counter + 2], &allNumbers[counter + 3], &allNumbers[counter + 4]);
		counter+=5;
	}
	
	counter = 0;
	
	printf("Processing your request...\n");
	
	clock_t begin = clock();
	
	counter = divideConqQ1(allNumbers,0,49999);
	
	clock_t end = clock();
	
	double executionTime = (double)(end-begin) / (CLOCKS_PER_SEC);
	
	printf("Total inverses : %d\nTotal time : %lfs\n", counter, executionTime);
}

int mergeQ1 (int *totalNumbers, int left, int middle, int right) {
	
	//merges the two arrays
	int i = 0, j = left, k = middle, totalInversions = 0;
	int currentArray[right - left + 1];
	
	for (;j < middle && k < right + 1;i++) {
		if (totalNumbers[j] < totalNumbers[k]) {
			//only place where it checks if greater or not, so increments the counter
			currentArray[i] = totalNumbers[j];
			j++;
		}
		else {
			currentArray[i] = totalNumbers[k];
			k++;
			totalInversions += middle - j;
		}
	}
	
	for (; middle > j; i++, j++) {
		currentArray[i] = totalNumbers[j];
	}
	
	for (; right + 1 > k; i++, k++) {
		currentArray[i] = totalNumbers[k];
	}
	
	for (int x = 0; right + 1 > left; x++, left++) {
		totalNumbers[left] = currentArray[x];
	}
	
	return totalInversions;
}

int divideConqQ1 (int * allNumbers, int left, int right) {
	int totalInversions = 0;
	//so it gets typcasted and floored down to avoid errors
	
	if (right > left) {
		int middle = (left + right) / 2;
		
		//divides the array up into two and sorts them
		totalInversions += divideConqQ1(allNumbers, left, middle);
		totalInversions += divideConqQ1(allNumbers, middle + 1, right);
		totalInversions += mergeQ1(allNumbers, left, middle + 1, right);
		return totalInversions;
		
		//return divideConqQ1(allNumbers,left,middle) + divideConqQ1(allNumbers,middle+1,right) + mergeQ1(allNumbers,left,middle+1,right);
	}
	else return totalInversions;
}

void partQ1C() {
	
	//runs both part A and B and then calculates the difference
	
	char fileName[1024];
	int allNumbers[50000];
	int counter = 0;
	
	printf("Please enter a proper file-name to test!\n");
	scanf("%s", fileName);
	
	if (!fileExist(fileName)) {
		printf("File does not exist!\n");
		return;
	}
	
	FILE * inFile = fopen(fileName, "r+");
	
	while (fgets(fileName, 1024, inFile) != NULL) {
		sscanf(fileName, "%d %d %d %d %d", &allNumbers[counter], &allNumbers[counter + 1], &allNumbers[counter + 2], &allNumbers[counter + 3], &allNumbers[counter + 4]);
		counter+=5;
	}
	
	int temp[50000];
	
	for (int i = 0; i < 50000; i ++) {
		temp[i] = allNumbers[i];
	}

	//for brute force
	clock_t begin1 = clock();
	
	for (int i = 0; i < 50000; i++) {
		
		for (int j = i + 1; j < 50000; j++) {
			if (allNumbers[i] > allNumbers[j]) {
				counter++;
			}
		}
		
	}
	
	clock_t end1 = clock();
	
	double executionTime1 = (double)(end1-begin1) / (CLOCKS_PER_SEC);
	
	//for divide and ConqQ1
	clock_t begin = clock();
	
	counter = divideConqQ1(temp,0,49999);
	
	clock_t end = clock();
	
	double executionTime = (double)(end-begin) / (CLOCKS_PER_SEC);
	printf("B\n");
	
	double difference = executionTime1 - executionTime;
	printf("Brute force took %lfs\nDivide and Conquer took %lfs\n", executionTime1, executionTime);
	printf("The difference between the 2 algorithms is %lfs\n", difference);
}

int fileExist (const char * fileName) {
	
	FILE * f = NULL;
	if ((f = fopen(fileName, "r"))) {
		fclose(f);
		return 1;
	}
	
	return 0;
}
