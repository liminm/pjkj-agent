#include "quicksort.h"


// FUNCTION CALL
// Parameters: 1. node, 2. node-children[high]; high is end index
void quickSortCall( Node *node, int len, int max){
    quickSort(node,0,len,max);
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (Node *node, int low, int high, int max)
{
    //int pivot = arr[high];
    int pivot = node->children[high]->value; // pivot

    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if ((node->children[j]->value > pivot && max == 1) || (node->children[j]->value < pivot && max == 0))
        {
            i++; // increment index of smaller element
            Node *temp = node->children[i];
            node->children[i] = node->children[j];
            node->children[j] = temp;
        }

    }
    Node *temp = node->children[i+1];
    node->children[i+1] = node->children[high];
    node->children[high] = temp;

    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(Node *node, int low, int high, int max)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(node, low, high, max);

        // Separately sort elements before
        // partition and after partition
        quickSort(node, low, pi - 1,max);
        quickSort(node, pi + 1, high,max);

    }
}


