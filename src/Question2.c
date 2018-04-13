#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Question2.h"
#include "Question1.h"

void partQ2A() {
	char fileName[1024];
	double allNumbers[2][30000];
	int totalVertices = 0;
	int counter = 0;
	int side = 0;
	
	printf("Please enter a proper file-name to test!\n");
	scanf("%s", fileName);
	
	if (!fileExist(fileName)) {
		printf("File does not exist!\n");
		return;
	}
	
	FILE * inFile = fopen(fileName, "r+");
	//takes in input and puts them in a 2d array to hold x's and y's
	while (fgets(fileName, 1024, inFile) != NULL) {
		sscanf(fileName, "%lf %lf", &allNumbers[0][counter], &allNumbers[1][counter]);
		counter++;
	}

	int i = 0, j = 0, k = 0;
	
	clock_t begin = clock();
	
	//runs through all iterations n * n * n times and checks for convex HULL
	while (i < 30000) {
		j = 0;
		while (j < 30000) {
			side = 0;
			k = 0;
			while (k < 30000) {
		
				double x = allNumbers[0][k], x1 = allNumbers[0][i], x2 = allNumbers[0][j];
				double y = allNumbers[1][k], y1 = allNumbers[1][i], y2 = allNumbers[1][j];
				
				double xSlope1 = x - x1, ySlope1 = y2 - y1, xSlope2 = y - y1, ySlope2 = x2 - x1;
				double finalSlope = (xSlope1 * ySlope1) - (xSlope2 * ySlope2);
				
				
				//if any point is unreachable exit
				if (finalSlope > 0) {
					if (side == -1) break;
					else side = 1;
				}
				else if (finalSlope < 0) {
					if (side == 1) break;
					else side = -1;
				}
				else {
					if (x > x1 && x > x2) break;
					else if (x < x1 && x > x2) break; 
					else if (y < y1 && y < y2) break; 
					else if (y > y1 && y > y2) break;
				}

				if (k == 29999) { // if every point is reachable after executing, increment totalVertices
					if (side != 0) {
						if (i != j) {
							printf("The coordinates within the convex hull is (%lf, %lf)\n", allNumbers[0][i], allNumbers[1][i]);
							totalVertices++;
							j++, i++;
						}
					}
				}

				k++;
			}
			j++;
		}
		i++;
	}
	
	clock_t end = clock();
	
	double executionTime = (double)(end - begin) / (CLOCKS_PER_SEC);
	
	printf("Total number of Vertices : %d\nTotal execution time : %lfs\n", totalVertices, executionTime);
	
}

void partQ2B() {
	char fileName[1024];
	double allNumbers[2][30000];
	int totalVertices = 0;
	int counter = 0;
	int side = 0;
	
	printf("Please enter a proper file-name to test!\n");
	scanf("%s", fileName);
	
	if (!fileExist(fileName)) {
		printf("File does not exist!\n");
		return;
	}
	
	FILE * inFile = fopen(fileName, "r+");
	
	while (fgets(fileName, 1024, inFile) != NULL) {
		sscanf(fileName, "%lf %lf", &allNumbers[0][counter], &allNumbers[1][counter]);
		counter++;
	}
	
	clock_t begin = clock();
	
	
	//gets leftmost and rightmost coordinates so that it may partition it into 2 arrays
	//then it starts looking through each array to find the longest hypotenus to the left and right
	//it adds extreme points into the convexHull list
	double leftMost[2];
	double rightMost[2];
	
	leftMost[0] = allNumbers[0][0];
	leftMost[1] = allNumbers[1][0];
	
	rightMost[0] = allNumbers[0][0];
	rightMost[1] = allNumbers[1][0];
	
	for (int i = 0; i < 30000; i ++) {
		if (leftMost[0] > allNumbers[0][i]) {
			leftMost[0] = allNumbers[0][i];
			leftMost[1] = allNumbers[1][i];
		}
		if (rightMost[0] < allNumbers[0][i]) {
			rightMost[0] = allNumbers[0][i];
			rightMost[1] = allNumbers[1][i];
		}
	}
	
	List * rightList = NULL;
	List * leftList = NULL;
	
	//Partitioning the array into leftmost and righest most values
	for (int i = 0; i < 30000; i++) {
		double x = allNumbers[0][i], x1 = leftMost[0], x2 = rightMost[0];
		double y = allNumbers[1][i], y1 = leftMost[1], y2 = rightMost[1];
				
		double xSlope1 = x - x1, ySlope1 = y2 - y1, xSlope2 = y - y1, ySlope2 = x2 - x1;
		double finalSlope = (xSlope1 * ySlope1) - (xSlope2 * ySlope2);
		
		if (finalSlope < 0) {
			leftList = insertBack(leftList, createNode(allNumbers[0][i], allNumbers[1][i]));
		}
		else if (finalSlope > 0) {
			rightList = insertBack(rightList, createNode(allNumbers[0][i], allNumbers[1][i]));
		}
	}
		
	List * convexHulls = NULL;
	
	//calling the recursive function with both partitions
	convexHulls = insertBack(convexHulls, createNode(leftMost[0], leftMost[1]));
	convexHulls = insertBack(convexHulls, createNode(rightMost[0], rightMost[1]));
	
	convexHullAlgorithm(leftList, createNode(leftMost[0], leftMost[1]), createNode(rightMost[0], rightMost[1]), convexHulls);
	convexHullAlgorithm(rightList, createNode(rightMost[0], rightMost[1]), createNode(leftMost[0], leftMost[1]), convexHulls);
			
	clock_t end = clock();
	
	List * temp = convexHulls;
	
	int counterx = 0;
	while (temp!=NULL) {
		counterx++;
		printf("The coordinate for the Convex Hull is : (%lf %lf)\n", temp->x, temp->y);
		temp = temp->next;
	}
	
	double executionTime = (double)(end - begin) / (CLOCKS_PER_SEC);
	
	printf("Total vertices : %d\nTotal execution Time : %lfs\n", counterx, executionTime);
		
}

void convexHullAlgorithm(List * dividedList, List * firstLimit, List * secondLimit, List * convexHulls) {
	
	List *temp = NULL, *extremeCase = NULL, *farthestUpper = NULL, *farthestLower = NULL;
	
	double tCord1 = 0, tCord2 = 0, tCord3 = 0;
	
	double maximumHeight = 0, point1 = (firstLimit->y - secondLimit->y), point2 = (secondLimit->x - firstLimit->x), 
	point3 = (firstLimit->x * secondLimit->y) - (secondLimit->x * firstLimit->y), point4 = 0, perimeter = 0, currentHeight = 0, currentDistance = 0, value = 0;
	
	if (dividedList == NULL) return;
	
	temp = dividedList;
	
	double x1 = firstLimit->x, x2 = secondLimit->x;
	double y1 = firstLimit->y, y2 = secondLimit->y;
	
	//calculates the length
	currentDistance = sqrt(((x2-x1) * (x2-x1)) + ((y2 - y1) * (y2 - y1)));

	while (temp != NULL) {
		
		double x1 = firstLimit->x, x2 = secondLimit->x, x3 = temp->x;
		double y1 = firstLimit->y, y2 = secondLimit->y, y3 = temp->y;
		
		perimeter = fabs((x1 * y2) + (x3 * y1) + (x2 * y3) - (x3 * y2) - (x2 * y1) - (x1 * y3));
		//gets the height using a math formula
		currentHeight = perimeter / currentDistance;
		
		//checks if current Height is greater than previously recorded max height
		if (currentHeight > maximumHeight) maximumHeight = currentHeight, extremeCase = temp; //if yes save it
				
		temp = temp->next;
	}
	
	//add extreme cases into convexHull list, because it is a property that we know for sure works!
	extremeCase = createNode(extremeCase->x, extremeCase->y);	
	convexHulls = insertBack(convexHulls, extremeCase);
	
	List * n = convexHulls;
	
	//otherwise continue gathering all the farthest out points and check them recursively
	while (dividedList != NULL) {
		
		double x1 = firstLimit->x, x2 = secondLimit->x, x3 = extremeCase->x, x4 = dividedList->x;
		double y1 = firstLimit->y, y2 = secondLimit->y, y3 = extremeCase->y, y4 = dividedList->y;
		
		tCord1 = ((y2 - y3) * (x4 - x3) + (x3 - x2) * (y4 - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
		
		tCord2 = ((y3 - y1) * (x4 - x3) + (x1 - x3) * (y4 - y3)) / ((y2 - y3) * (x1 - x3) +  (x3 - x2) * (y1 - y3));
		
		tCord3 = 1.0 - tCord1 - tCord2;

    
		if (!(tCord1 > 0 && tCord2 > 0 && tCord3 > 0)) {
			
			point1 = x3 - x1;
			point2 = y4 - y1;
			point3 = x4 - x1;
			point4 = y3 - y1;
			
			value = (point1 * point2) - (point3 * point4);
						
			if (value > 0) farthestUpper = insertBack(farthestUpper, createNode(dividedList->x, dividedList->y));
			
			point1 = x3 - x2;
			point2 = y4 - y2;
			point3 = x4 - x2;
			point4 = y3 - y2;
			
			value = (point1 * point2) - (point3 * point4);
						
			if (value < 0) farthestLower = insertBack(farthestLower, createNode(dividedList->x, dividedList->y));
		
		}
		
		dividedList = dividedList->next;
	}

  //recurses the leftmost and rightmost points to check if they are convexHulls
  convexHullAlgorithm(farthestUpper, firstLimit, extremeCase, convexHulls);
  convexHullAlgorithm(farthestLower, extremeCase, secondLimit, convexHulls);
}

void partQ2C() {
	char fileName[1024];
	double allNumbers[2][30000];
	double allNumbers2[2][30000];
	int totalVertices = 0;
	int counter = 0;
	int side = 0;
	
	printf("Please enter a proper file-name to test!\n");
	scanf("%s", fileName);
	
	if (!fileExist(fileName)) {
		printf("File does not exist!\n");
		return;
	}
	
	FILE * inFile = fopen(fileName, "r+");
	
	while (fgets(fileName, 1024, inFile) != NULL) {
		sscanf(fileName, "%lf %lf", &allNumbers[0][counter], &allNumbers[1][counter]);
		counter++;
	}
	
	for (int i = 0; i < 30000; i++) {
		allNumbers2[0][i] = allNumbers[0][i];
		allNumbers2[1][i] = allNumbers[1][i];
	}

	int i = 0, j = 0, k = 0;
	
	clock_t begin = clock();
	
	while (i < 30000) {
		j = 0;
		while (j < 30000) {
			side = 0;
			k = 0;
			while (k < 30000) {
		
				double x = allNumbers[0][k], x1 = allNumbers[0][i], x2 = allNumbers[0][j];
				double y = allNumbers[1][k], y1 = allNumbers[1][i], y2 = allNumbers[1][j];
				
				double xSlope1 = x - x1, ySlope1 = y2 - y1, xSlope2 = y - y1, ySlope2 = x2 - x1;
				double finalSlope = (xSlope1 * ySlope1) - (xSlope2 * ySlope2);
				
				
				
				if (finalSlope > 0) {
					if (side == -1) break;
					else side = 1;
				}
				else if (finalSlope < 0) {
					if (side == 1) break;
					else side = -1;
				}
				else {
					if (x > x1 && x > x2) break;
					else if (x < x1 && x > x2) break; 
					else if (y < y1 && y < y2) break; 
					else if (y > y1 && y > y2) break;
				}

				if (k == 29999) { // every point successfull
					if (side != 0) {
						if (i != j) {
							totalVertices++;
							j++, i++;
						}
					}
				}

				k++;
			}
			j++;
		}
		i++;
	}
	
	clock_t end = clock();
	
	double executionTime = (double)(end - begin) / (CLOCKS_PER_SEC);
	
	clock_t begin2 = clock();
	
	double leftMost[2];
	double rightMost[2];
	
	leftMost[0] = allNumbers2[0][0];
	leftMost[1] = allNumbers2[1][0];
	
	rightMost[0] = allNumbers2[0][0];
	rightMost[1] = allNumbers2[1][0];
	
	for (int i = 0; i < 30000; i ++) {
		if (leftMost[0] > allNumbers2[0][i]) {
			leftMost[0] = allNumbers2[0][i];
			leftMost[1] = allNumbers2[1][i];
		}
		if (rightMost[0] < allNumbers2[0][i]) {
			rightMost[0] = allNumbers2[0][i];
			rightMost[1] = allNumbers2[1][i];
		}
	}
	
	List * rightList = NULL;
	List * leftList = NULL;
	
	for (int i = 0; i < 30000; i++) {
		double x = allNumbers2[0][i], x1 = leftMost[0], x2 = rightMost[0];
		double y = allNumbers2[1][i], y1 = leftMost[1], y2 = rightMost[1];
				
		double xSlope1 = x - x1, ySlope1 = y2 - y1, xSlope2 = y - y1, ySlope2 = x2 - x1;
		double finalSlope = (xSlope1 * ySlope1) - (xSlope2 * ySlope2);
		
		if (finalSlope < 0) {
			leftList = insertBack(leftList, createNode(allNumbers2[0][i], allNumbers2[1][i]));
		}
		else if (finalSlope > 0) {
			rightList = insertBack(rightList, createNode(allNumbers2[0][i], allNumbers2[1][i]));
		}
	}
		
	List * convexHulls = NULL;
	
	convexHulls = insertBack(convexHulls, createNode(leftMost[0], leftMost[1]));
	convexHulls = insertBack(convexHulls, createNode(rightMost[0], rightMost[1]));
	
	convexHullAlgorithm(leftList, createNode(leftMost[0], leftMost[1]), createNode(rightMost[0], rightMost[1]), convexHulls);
	convexHullAlgorithm(rightList, createNode(rightMost[0], rightMost[1]), createNode(leftMost[0], leftMost[1]), convexHulls);
			
	clock_t end2 = clock();
	
	List * temp = convexHulls;
	
	int counterx = 0;
	while (temp!=NULL) {
		counterx++;
		temp = temp->next;
	}
	
	double executionTime2 = (double)(end2 - begin2) / (CLOCKS_PER_SEC);
		
	printf("Brute Force :\nTotal vertices : %d\nTotal execution Time : %lfs\n", totalVertices, executionTime);
	
	printf("Divide and ConquerTotal vertices : %d\nTotal execution Time : %lfs\n", counterx, executionTime2);
	
	double difference = executionTime - executionTime2;
	
	printf("The differente between the 2 algorithms is %lfs\n", difference);
	
	
}

List * createNode(double x, double y) {
	List * l = malloc(sizeof(List));
	l->x = x;
	l->y = y;
	l->next = NULL;
	
	return l;
}

List * insertBack (List * head, List * node) {
	

	if (head == NULL) head = node;
	
	else if (node == NULL) return head;
	
	else {
		
		List * temp = head;
		
		while (temp->next != NULL) temp = temp->next;
	
		if (node != NULL) {
			temp->next = node;
		}
	}
	
	return head;
	
}

