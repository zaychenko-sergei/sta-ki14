#ifndef _INTEGER_MAP_HPP_
#define _INTEGER_MAP_HPP_

struct IntegerMap;

IntegerMap * IntegerMapCreate ();

void IntegerMapDestroy ( IntegerMap * _pMap );

void IntegerMapClear ( IntegerMap & _map );

bool IntegerMapIsEmpty ( const IntegerMap & _map );

bool IntegerMapHasKey ( const IntegerMap & _map, int _key );

int IntegerMapFindKeyPosition ( const IntegerMap & _map, int _key );

int IntegerMapGet ( const IntegerMap & _map, int _key );

void IntegerMapInsertKey ( IntegerMap & _map, int _key, int _value );

void IntegerMapRemoveKey ( IntegerMap & _map, int _key );
 

#endif //  _INTEGER_MAP_HPP_
