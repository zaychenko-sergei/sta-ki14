#include "integer_stack.hpp"
#include "integer_list.hpp"


struct IntegerStack
{
    IntegerList m_List;
};


IntegerStack * IntegerStackCreate ()
{
    IntegerStack * pStack = new IntegerStack;
    IntegerListInit( pStack->m_List );
    return pStack;
}


void IntegerStackDestroy ( IntegerStack * _pStack )
{
    IntegerListDestroy( _pStack->m_List );
    delete _pStack;
}


void IntegerStackClear ( IntegerStack & _stack )
{
    IntegerListDestroy( _stack.m_List );
}


void IntegerStackPush ( IntegerStack & _stack, int _value )
{
    IntegerListPushBack( _stack.m_List, _value );
}


void IntegerStackPop ( IntegerStack & _stack )
{
    IntegerListPopBack( _stack.m_List );
}


int IntegerStackTop ( const IntegerStack & _stack )
{
    return _stack.m_List.m_pLast->m_value;
}


bool IntegerStackIsEmpty ( const IntegerStack & _stack )
{
    return IntegerListIsEmpty( _stack.m_List );
}
