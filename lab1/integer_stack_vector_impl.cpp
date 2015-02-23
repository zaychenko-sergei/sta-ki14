#include "integer_stack.hpp"
#include "integer_vector.hpp"


struct IntegerStack
{
    IntegerVector m_Vector;
};


IntegerStack * IntegerStackCreate ()
{
    IntegerStack * pStack = new IntegerStack;
    IntegerVectorInit( pStack->m_Vector );
    return pStack;
}


void IntegerStackDestroy ( IntegerStack * _pStack )
{
    IntegerVectorDestroy( _pStack->m_Vector );
    delete _pStack;
}


void IntegerStackClear ( IntegerStack & _stack )
{
    _stack.m_Vector.m_nUsed = 0;
}


void IntegerStackPush ( IntegerStack & _stack, int _value )
{
    IntegerVectorPushBack( _stack.m_Vector, _value );
}


void IntegerStackPop ( IntegerStack & _stack )
{
    IntegerVectorPopBack( _stack.m_Vector );
}


int IntegerStackTop ( const IntegerStack & _stack )
{
    return _stack.m_Vector.m_pData[_stack.m_Vector.m_nUsed - 1 ];
}


bool IntegerStackIsEmpty ( const IntegerStack & _stack )
{
    return ! _stack.m_Vector.m_nUsed;
}
