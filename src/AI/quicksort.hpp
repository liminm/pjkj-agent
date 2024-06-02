#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdlib.h>
#include <stdio.h>

#include "Node.h"

void quickSortCall( Node *node, int len, int max);
void quickSort(Node *node, int low, int high, int max);
int partition (Node *node, int low, int high, int max);

#endif //QUICKSORT_H
