#ifndef QUESTION_2
#define QUESTION_2

typedef struct List {
	double x;
	double y;
	
	struct List * next;
} List;

void partQ2A();

void partQ2B();

void partQ2C();

List * insertBack (List * head, List * node);

List * createNode(double x, double y);

void convexHullAlgorithm(List * dividedList, List * firstLimit, List * secondLimit, List * convexHulls);

void findHull(List * ptr, List *p, List *q,
              List *hullHead);

#endif
