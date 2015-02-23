#include "integer_stack.hpp"
#include <cassert>

struct IntegerStack
{
    int * m_pData;
    int * m_pTop;
    int m_Size;
};


IntegerStack * IntegerStackCreate ( int _fixedSize )
{
    IntegerStack * pStack = new IntegerStack;
    
    pStack->m_pData = new int[ _fixedSize ];
    pStack->m_pTop  = pStack->m_pData;
    pStack->m_Size  = _fixedSize;

    return pStack;
}


void IntegerStackDestroy ( IntegerStack * _pStack )
{
    delete[] _pStack->m_pData;
    delete _pStack;
}


void IntegerStackClear ( IntegerStack & _stack )
{
    _stack.m_pTop  = _stack.m_pData;
}


void IntegerStackPush ( IntegerStack & _stack, int _value )
{
    assert( ! IntegerStackIsFull( _stack ) );
    * _stack.m_pTop = _value;
    ++ _stack.m_pTop;
}


void IntegerStackPop ( IntegerStack & _stack )
{
    assert( ! IntegerStackIsEmpty( _stack ) );
    -- _stack.m_pTop;
}


int IntegerStackTop ( const IntegerStack & _stack )
{
    assert( ! IntegerStackIsEmpty( _stack ) );
    return * ( _stack.m_pTop - 1 );
}


bool IntegerStackIsEmpty ( const IntegerStack & _stack )
{
    return _stack.m_pData == _stack.m_pTop;
}


bool IntegerStackIsFull ( const IntegerStack & _stack )
{
    return ( _stack.m_pTop - _stack.m_pData ) == _stack.m_Size;
}