// Current code is from the textbook
// Modified by: Afnan Ebrahim
// Comment file
/* 
    The following homework allows us to implement and see how various sort algorithms work
    and gain an idea of how long each algorithm takes using the clock that was used to time each function
*/
#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

/**
 * Simple insertion sort.
 */
template <typename Comparable>
void insertionSort( vector<Comparable> & a )
{
    for( int p = 1; p < a.size( ); ++p )
    {
        Comparable tmp = std::move( a[ p ] );

        int j;
        for( j = p; j > 0 && tmp < a[ j - 1 ]; --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j;

        for( j = p; j > left && tmp < a[ j - 1 ]; --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}

/* 
my implementation of insertion sort to use comparator
same as normal insertion sort except comparison is substituted with cmp
*/
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a, int left, int right, Comparator cmp )
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j;

        for( j = p; j > left && cmp(tmp, a[ j - 1 ]); --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable>
void shellsort( vector<Comparable> & a )
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); ++i )
        {
            Comparable tmp = std::move( a[ i ] );
            int j = i;

            for( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = std::move( a[ j - gap ] );
            a[ j ] = std::move( tmp );
        }
}
/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * This will create a Min heap
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
/*
original was changed to make use of comparator allowing heapsort to work
both increasing order and decreasing
*/
template <typename Comparable, typename Comparator>
void percDown( vector<Comparable> & a, int i, int n, Comparator cmp)
{
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child )
    {
        child = leftChild( i );
        if( child != n - 1 && cmp(a[ child ],a[ child + 1 ]) )
            ++child;
        if( cmp(tmp, a[ child ]))
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}
/**
 * Standard heapsort.
 */
/*
only change was that cmp is passed into percDown
*/
template <typename Comparable, typename Comparator>
void heapsort( vector<Comparable> & a, Comparator cmp)
{
    if(a.size() == 0)//check to see if vector size is 0: If this is the case return ERROR
    {
        cout<<"ERROR: vector of size 0 \n";
        return;
    }
    for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown( a, i, a.size( ), cmp );
    for( int j = a.size( ) - 1; j > 0; --j )
    {
        std::swap( a[ 0 ], a[ j ] );               /* deleteMax || deleteMin */
        percDown( a, 0, j, cmp );
    }
}



/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
/*comparator || == */
template <typename Comparable, typename Comparator>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
            int leftPos, int rightPos, int rightEnd, Comparator cmp)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if(cmp(a[ leftPos ], a[ rightPos]) || a[leftPos] == a[rightPos] )
            tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
        else
            tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    while( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );

    while( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );

    // Copy tmpArray back
    for( int i = 0; i < numElements; ++i, --rightEnd )
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
}


/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void mergeSort( vector<Comparable> & a,
                vector<Comparable> & tmpArray, int left, int right, Comparator cmp )
{
    if( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center, cmp );
        mergeSort( a, tmpArray, center + 1, right, cmp );
        merge( a, tmpArray, left, center + 1, right, cmp );
    }
}

/**
 * Mergesort algorithm (driver).
 */
/*
comparator is passed into mergesort
*/
template <typename Comparable, typename Comparator>
void mergeSort( vector<Comparable> & a, Comparator cmp )
{
    if(a.size() == 0)//check to see if vector size is 0: If this is the case return ERROR
    {
        cout<<"ERROR: vector of size 0 \n";
        return;
    }
    vector<Comparable> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1, cmp );
}





/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
/*comparator was used to determine how to sort the three elements*/
template <typename Comparable, typename Comparator>
const Comparable & median3( vector<Comparable> & a, int left, int right, Comparator cmp )
{
    int center = ( left + right ) / 2;
    
    if( cmp(a[ center ],  a[ left ]) )
        std::swap( a[ left ], a[ center ] );
    if( cmp(a[ right ], a[ left ] ))
        std::swap( a[ left ], a[ right ] );
    if( cmp(a[ right ], a[ center ] ))
        std::swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

/**
 * Return middleElement
 * swaps center element and right elemnt to move pivot out of the way
 */
template <typename Comparable>
const Comparable & middleElement( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    
    std::swap( a[ center ], a[ right ] );
    return a[right];
}


/**
 * Return leftElement
 * swaps left element and right elemnt to move pivot out of the way
 */
template <typename Comparable>
const Comparable & leftElement( vector<Comparable> & a, int left, int right )
{
    std::swap( a[ left ], a[ right ] );
    return a[right];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses first element partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksortC( vector<Comparable> & a, int left, int right, Comparator cmp )
{
    if(a.size() == 0)//check to see if vector size is 0: If this is the case return ERROR
    {
        cout<<"ERROR: vector of size 0 \n";
        return;
    }
    if( left + 10 <= right )
    {
        const Comparable & pivot = leftElement(a, left, right);

            // Begin partitioning
        int i = left, j = right ;
        for( ; ; )
        {
            while( cmp(a[ i ], pivot) ) {i++;}
            while( cmp(pivot, a[ --j ] )) {}
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[right] );  // Restore pivot

        quicksortC( a, left, i - 1, cmp );     // Sort small elements
        quicksortC( a, i + 1, right, cmp );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, cmp );
}
/**
 * Internal quicksort method that makes recursive calls.
 * Uses middleElement partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksortB( vector<Comparable> & a, int left, int right, Comparator cmp )
{
    if(a.size() == 0)//check to see if vector size is 0: If this is the case return ERROR
    {
        cout<<"ERROR: vector of size 0 \n";
        return;
    }
    if( left + 10 <= right )
    {
        const Comparable & pivot =middleElement(a, left, right);

            // Begin partitioning
        int i = left, j = right;
        for( ; ; )
        {
            while( cmp(a[ i ], pivot) ) {i++; }
            while( cmp(pivot, a[ --j ] )) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right] );  // Restore pivot

        quicksortB( a, left, i - 1, cmp );     // Sort small elements
        quicksortB( a, i + 1, right, cmp );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, cmp );
}
/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksort( vector<Comparable> & a, int left, int right, Comparator cmp )
{
    if(a.size() == 0)//check to see if vector size is 0: If this is the case return ERROR
    {
        cout<<"ERROR: vector of size 0 \n";
        return;
    }
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right,cmp );

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( cmp(a[ ++i ], pivot) ) { }
            while( cmp(pivot, a[ --j ] ) ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

        quicksort( a, left, i - 1, cmp );     // Sort small elements
        quicksort( a, i + 1, right, cmp );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, cmp );
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable,typename Comparator>
void quicksort( vector<Comparable> & a, Comparator cmp )
{
    quicksort( a, 0, a.size( ) - 1, cmp );
}
/**
 * Quicksort2 algorithm (driver).
 */
template <typename Comparable,typename Comparator>
void quicksort2( vector<Comparable> & a, Comparator cmp )
{
    quicksortB( a, 0, a.size( ) - 1, cmp );
}
/**
 * Quicksort3 algorithm (driver).
 */
template <typename Comparable,typename Comparator>
void quicksort3( vector<Comparable> & a, Comparator cmp )
{
    quicksortC( a, 0, a.size( ) - 1, cmp );
}


template <typename Comparable>
void SORT( vector<Comparable> & items )
{
    if( items.size( ) > 1 )
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;
        
        auto chosenItem = items[ items.size( ) / 2 ];
        
        for( auto & i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );
            else if( chosenItem < i )
                larger.push_back( std::move( i ) );
            else
                same.push_back( std::move( i ) );
        }
        
        SORT( smaller );     // Recursive call!
        SORT( larger );      // Recursive call!
        
        std::move( begin( smaller ), end( smaller ), begin( items ) );
        std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
        std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );

/*
        items.clear( );
        items.insert( end( items ), begin( smaller ), end( smaller ) );
        items.insert( end( items ), begin( same ), end( same ) );
        items.insert( end( items ), begin( larger ), end( larger ) );
*/
    }
}


//   Provide code for the following functions.
//   See PDF for full details.
//   Note that you will have to modify some of the functions above, or/and add new helper functions.

// Driver for HeapSort.
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable> &a, Comparator less_than) {
  // Add code. You can use any of functions above (after you modified them), or any other helper
  // function you write.
    

    heapsort( a, less_than);

}
 
// Driver for MergeSort.
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable> &a, Comparator less_than) {
  // Add code. You can use any of functions above (after you modified them), or any other helper
  // function you write.

    mergeSort(a, less_than);

}

// Driver for QuickSort (median of 3 partitioning).
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable> &a, Comparator less_than) {
  // Add code. You can use any of functions above (after you modified them), or any other helper
  // function you write.

    quicksort(a, less_than);

}

// Driver for QuickSort (middle pivot).
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable> &a, Comparator less_than) {
  // quicksort implementation
  // to be filled
    quicksort2(a, less_than);

}

// Driver for quicksort using first as pivot
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable> &a, Comparator less_than) {
  // quicksort implementation
  // to be filled
    quicksort3(a, less_than);

}


#endif  // SORT_H
