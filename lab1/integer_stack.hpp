#ifndef _INTEGER_STACK_HPP_
#define _INTEGER_STACK_HPP_

#include <iostream>

struct IntegerStack;

IntegerStack * IntegerStackCreate ();

IntegerStack * IntegerStackCreate ( int _fixedSize );

void IntegerStackDestroy ( IntegerStack * _pStack );

void IntegerStackClear ( IntegerStack & _stack );

bool IntegerStackIsEmpty ( const IntegerStack & _stack );

bool IntegerStackIsFull ( const IntegerStack & _stack );

void IntegerStackPush ( IntegerStack & _stack, int _value );

void IntegerStackPop ( IntegerStack & _stack );

int IntegerStackTop ( const IntegerStack & _stack );


#endif //  _INTEGER_STACK_HPP_