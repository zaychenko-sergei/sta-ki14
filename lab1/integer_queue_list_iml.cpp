#include "integer_queue.hpp"
#include "integer_list.hpp"

#include <cassert>


struct IntegerQueue
{
    IntegerList m_List;
};

IntegerQueue * IntegerQueueCreate ()
{
    IntegerQueue * pNewQueue = new IntegerQueue;
    IntegerListInit( pNewQueue->m_List );
    return pNewQueue;
}

void IntegerQueueDestroy ( IntegerQueue * _pQueue )
{
    IntegerListDestroy( _pQueue->m_List );
    delete _pQueue;
}

void IntegerQueueClear ( IntegerQueue & _queue )
{
    IntegerListDestroy( _queue.m_List );
}

bool IntegerQueueIsEmpty ( const IntegerQueue & _queue )
{
    return IntegerListIsEmpty( _queue.m_List );
}

bool IntegerQueueIsFull ( const IntegerQueue & _queue )
{
    return false;
}

void IntegerQueuePush ( IntegerQueue & _queue, int _value )
{
    IntegerListPushBack( _queue.m_List, _value );
}

void IntegerQueuePop ( IntegerQueue & _queue )
{
    assert( ! IntegerQueueIsEmpty( _queue ) );
    IntegerListPopFront( _queue.m_List );
}

int IntegerQueueFront ( const IntegerQueue & _queue )
{
    assert( ! IntegerQueueIsEmpty( _queue ) );
    return _queue.m_List.m_pFirst->m_value;
}
