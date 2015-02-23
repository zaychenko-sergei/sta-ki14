#include "integer_queue.hpp"
#include <cassert>


struct IntegerQueue
{
    int * m_pData;
    int m_Size;
    int m_FrontIndex;
    int m_BackIndex;
};

IntegerQueue * IntegerQueueCreate ( int _fixedSize )
{
    assert( _fixedSize > 0 );
    
    IntegerQueue * pNewQueue = new IntegerQueue;
    
    pNewQueue->m_Size       = _fixedSize + 1;
    pNewQueue->m_pData      = new int[ pNewQueue->m_Size ];
    IntegerQueueClear( * pNewQueue );

    return pNewQueue;
}

void IntegerQueueDestroy ( IntegerQueue * _pQueue )
{
    delete[] _pQueue->m_pData;
    delete _pQueue;
}

void IntegerQueueClear ( IntegerQueue & _queue )
{
    _queue.m_FrontIndex = 0;
    _queue.m_BackIndex  = 0;
}

int IntegerQueueSize ( const IntegerQueue & _queue )
{
    // |-|-|-|-|-|-|        |-|-|-|-|-|-|  
    //   F     B                B     F

    return ( _queue.m_FrontIndex <= _queue.m_BackIndex ) ? 
               _queue.m_BackIndex - _queue.m_FrontIndex : 
               _queue.m_BackIndex + _queue.m_Size - _queue.m_FrontIndex;

}

bool IntegerQueueIsEmpty ( const IntegerQueue & _queue )
{
    return IntegerQueueSize( _queue ) == 0;
}

bool IntegerQueueIsFull ( const IntegerQueue & _queue )
{
    return IntegerQueueSize( _queue ) == ( _queue.m_Size - 1 );
}

int IntegerQueueNextIndex ( const IntegerQueue & _queue, int _index )
{
    int index  = _index + 1;
    if ( index == _queue.m_Size )
        index = 0;
    return index;
}

void IntegerQueuePush ( IntegerQueue & _queue, int _value )
{
    assert( ! IntegerQueueIsFull( _queue ) );

    _queue.m_pData[ _queue.m_BackIndex ] = _value;
    _queue.m_BackIndex = IntegerQueueNextIndex( _queue, _queue.m_BackIndex );
}

void IntegerQueuePop ( IntegerQueue & _queue )
{
    assert( ! IntegerQueueIsEmpty( _queue ) );
    _queue.m_FrontIndex = IntegerQueueNextIndex( _queue, _queue.m_FrontIndex );
}

int IntegerQueueFront ( const IntegerQueue & _queue )
{
    assert( ! IntegerQueueIsEmpty( _queue ) );
    return _queue.m_pData[ _queue.m_FrontIndex ];
}
