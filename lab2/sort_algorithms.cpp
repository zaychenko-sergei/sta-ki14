#include "sort_algorithms.hpp"

#include <memory.h>
#include <stdlib.h>


void bubbleSort ( int* _pData, int _N )
{
    for ( int i = 0; i < _N - 1; i++ )
        for ( int j = _N - 1; j > i; j-- )
            if ( _pData[ j - 1 ] > _pData[ j ] )
            {
                int temp = _pData[ j - 1 ];
                _pData[ j - 1 ] = _pData[ j ];
                _pData[ j ] = temp;
            }
}


void insertionSort ( int* _pData, const int _N )
{
    for ( int i = 1; i < _N; i++ )
    {
        int j = i;
        while ( j && ( _pData[ j ] < _pData[ j - 1 ] ) )
        {
            int temp = _pData[ j ];           
            _pData[ j - 1 ] = _pData[ j ];
            _pData[ j ] = temp;

            --j;
        }
    }
}

void selectionSort ( int* _pData, const int _N )
{
    for ( int i = 0; i < _N - 1; i++ )
    {
        int lowIndex = i;
        for ( int j = i + 1; j < _N; j++ )
            if ( _pData[ j ] < _pData[ lowIndex ] )
                lowIndex = j;

        int temp = _pData[ lowIndex ];
        _pData[ lowIndex ] = _pData[ i ];
        _pData[ i ] = temp;
    }
}


void mergeSorted ( const int * _pFirst,  int _firstSize,
                   const int * _pSecond, int _secondSize,
                   int * _pTarget )
{
    int firstIndex = 0, secondIndex = 0, targetIndex = 0;
    while ( firstIndex < _firstSize && secondIndex < _secondSize )
    {
        if ( _pFirst[ firstIndex ] <= _pSecond[ secondIndex ] )
        {
            _pTarget[ targetIndex ] = _pFirst[ firstIndex ];
            ++ firstIndex;
        }

        else
        {
            _pTarget[ targetIndex ] = _pSecond[ secondIndex ];
            ++ secondIndex;
        }

        ++ targetIndex;
    }

    if ( firstIndex < _firstSize )
        memcpy( _pTarget + targetIndex,
                _pFirst + firstIndex, 
                sizeof( int ) * ( _firstSize - firstIndex ) 
        );

    else if ( secondIndex < _secondSize )
        memcpy( _pTarget + targetIndex,
                _pSecond + secondIndex, 
                sizeof( int ) * ( _secondSize - secondIndex ) 
        );
}


void mergeSort ( int * _pData, int _N )
{
    if ( _N < 10 )
        selectionSort( _pData, _N );

    else
    {
        int halfSize = _N / 2;
        int otherHalfSize = _N - halfSize;

        int * pFirstHalf = new int[ halfSize ];
        memcpy( pFirstHalf, _pData, sizeof( int ) * halfSize );

        int * pSecondHalf = new int[ otherHalfSize ];
        memcpy( pSecondHalf, _pData + halfSize, sizeof( int ) * otherHalfSize );

        mergeSort( pFirstHalf,  halfSize );
        mergeSort( pSecondHalf, otherHalfSize );

        mergeSorted( pFirstHalf, halfSize, pSecondHalf, otherHalfSize, _pData );

        delete[] pFirstHalf;
        delete[] pSecondHalf;
    }
}


void quickSort ( int * _pData, int _N )
{
    if ( _N < 10 )
    {
        selectionSort( _pData, _N );
        return;
    }

    int leftIndex = -1, rightIndex = _N;

    int pivotIndex = rand() % _N;
    int pivot = _pData[ pivotIndex ];

    while ( true )
    {
        while ( leftIndex < _N && _pData[ ++ leftIndex ] < pivot );

        while ( rightIndex >= 0 && pivot < _pData[ --rightIndex ] )
            if ( rightIndex == leftIndex )
                break;

        if ( leftIndex >= rightIndex )
            break;

        int temp = _pData[ leftIndex ];
        _pData[ leftIndex ] = _pData[ rightIndex ];
        _pData[ rightIndex ] = temp;
    }

    if ( leftIndex == 0 )
        leftIndex = 1;
    else if ( leftIndex == _N )
        leftIndex = _N - 1;

    quickSort( _pData, leftIndex );
    quickSort( _pData + leftIndex, _N - leftIndex );
}

