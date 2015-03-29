#include "integer_map.hpp"
#include "integer_vector.hpp"

#include <cassert>


struct IntegerMap
{
    IntegerVector m_keys;
    IntegerVector m_values;
};



IntegerMap * IntegerMapCreate ()
{
    IntegerMap * pMap = new IntegerMap;
    IntegerVectorInit( pMap->m_keys );
    IntegerVectorInit( pMap->m_values );
    return pMap;
}


void IntegerMapDestroy ( IntegerMap * _pMap )
{
    IntegerVectorDestroy( _pMap->m_keys );
    IntegerVectorDestroy( _pMap->m_values );
    delete _pMap;
}


void IntegerMapClear ( IntegerMap & _map )
{
    IntegerVectorClear( _map.m_keys );
    IntegerVectorClear( _map.m_values );
}


bool IntegerMapIsEmpty ( const IntegerMap & _map )
{
    return IntegerVectorIsEmpty( _map.m_keys );
}


int IntegerMapFindKeyPosition ( const IntegerMap & _map, int _key )
{
    for ( int i = 0; i < _map.m_keys.m_nUsed; i++ )
        if ( _map.m_keys.m_pData[ i ] == _key )
            return i;

    return -1;
}


int IntegerMapGet ( const IntegerMap & _map, int _key )
{
    int keyPosition = IntegerMapFindKeyPosition( _map, _key );
	if ( keyPosition != -1 )
	    return _map.m_values.m_pData[ keyPosition ];
	else
	    return -1;
}

bool IntegerMapHasKey ( const IntegerMap & _map, int _key )
{
    return IntegerMapFindKeyPosition( _map, _key ) != -1;
}


void IntegerMapInsertKey ( IntegerMap & _map, int _key, int _value )
{
    int position = IntegerMapFindKeyPosition( _map, _key );
    if ( position == - 1 )
    {
        IntegerVectorPushBack( _map.m_keys, _key );
        IntegerVectorPushBack( _map.m_values, _value );
    }
    else
        _map.m_values.m_pData[ position ] = _value;
}



void IntegerMapRemoveKey ( IntegerMap & _map, int _key )
{
    int position = IntegerMapFindKeyPosition( _map, _key );
    assert( position != -1 );

    IntegerVectorDeleteAt( _map.m_keys, position );
    IntegerVectorDeleteAt( _map.m_values, position );
}