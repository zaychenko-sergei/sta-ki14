#include "hash_table.hpp"
#include <cassert>

struct HashTable
{
    struct Element
    {
        int m_key;
        int m_value;
        enum { NOT_OCCUPIED, OCCUPIED, DELETED } m_status;
    };

    int m_tableSize;
    int m_numOccupied;
    Element* m_pData;
};


HashTable* HashTableCreate ( int _initialSize )
{
    HashTable * pNewHT = new HashTable;
        
    pNewHT->m_tableSize = _initialSize;
    pNewHT->m_pData     = new HashTable::Element[ pNewHT->m_tableSize ];

    HashTableClear( * pNewHT );

    return pNewHT;
}


void HashTableDestroy ( HashTable* _pHT )
{
    delete[] _pHT->m_pData;
    delete _pHT;
}


void HashTableClear ( HashTable & _ht )
{
    _ht.m_numOccupied   = 0;
    for ( int i = 0; i < _ht.m_tableSize; i++ )
        _ht.m_pData[ i ].m_status = HashTable::Element::NOT_OCCUPIED;
}


int HashTableNumElements ( const HashTable & _ht )
{
    return _ht.m_numOccupied;
}


unsigned int HashCode ( int _key )
{
    unsigned int hashCode = _key;
    return hashCode;
}


bool HashTableTryInsertElement ( HashTable & _ht, int _bucketNr, int _key, int _value )
{
    if ( _ht.m_pData[ _bucketNr ].m_status != HashTable::Element::OCCUPIED )
    {
        _ht.m_pData[ _bucketNr ].m_status = HashTable::Element::OCCUPIED;
        _ht.m_pData[ _bucketNr ].m_key      = _key;
        _ht.m_pData[ _bucketNr ].m_value  = _value;
        _ht.m_numOccupied++;
        return true;
    }
    else if ( _ht.m_pData[ _bucketNr ].m_key == _key )
    {
        _ht.m_pData[ _bucketNr ].m_value = _value;
        return true;
    }
    else
        return false;
}


void HashTableDoubleSize ( HashTable & _ht )
{
    int oldSize = _ht.m_tableSize;
    _ht.m_tableSize <<= 1;

    HashTable::Element* oldData = _ht.m_pData;
    _ht.m_pData = new HashTable::Element[ _ht.m_tableSize ];
    for ( int i = 0; i < _ht.m_tableSize; i++ )
        _ht.m_pData[ i ].m_status = HashTable::Element::NOT_OCCUPIED;
    _ht.m_numOccupied = 0;

    for ( int i = 0; i < oldSize; i++ )
        if (  oldData[ i ].m_status == HashTable::Element::OCCUPIED  )
            HashTableInsert( _ht, oldData[ i ].m_key, oldData[ i ].m_value );

    delete[] oldData;
}


void HashTableInsert ( HashTable & _ht, int _key, int _value )
{
    if ( ( _ht.m_numOccupied << 1 ) >= _ht.m_tableSize )
        HashTableDoubleSize( _ht );

    unsigned int hashCode = HashCode( _key );
    int bucketNr = hashCode % _ht.m_tableSize;

    for ( int i = bucketNr; i < _ht.m_tableSize; i++ )
        if ( HashTableTryInsertElement( _ht, i, _key, _value ) )
            return;

    for ( int i = 0; i < bucketNr; i++ )
        if ( HashTableTryInsertElement( _ht, i, _key, _value ) )
            return;
}


int HashTableGet ( const HashTable & _ht, int _key )
{
    unsigned int hashCode = HashCode( _key );
    int bucketNr = hashCode % _ht.m_tableSize;

    for ( int i = bucketNr; i < _ht.m_tableSize; i++ )
        if ( _ht.m_pData[ i ].m_status == HashTable::Element::NOT_OCCUPIED )
            break;
        else if ( _ht.m_pData[ i ].m_status == HashTable::Element::OCCUPIED &&
                  _ht.m_pData[ i ].m_key == _key )
            return _ht.m_pData[ i ].m_value;

    for ( int i = 0; i < bucketNr; i++ )
        if ( _ht.m_pData[ i ].m_status == HashTable::Element::NOT_OCCUPIED )
            break;
        else if ( _ht.m_pData[ i ].m_status == HashTable::Element::OCCUPIED &&
                  _ht.m_pData[ i ].m_key == _key )
            return _ht.m_pData[ i ].m_value;

    return -1;
}


void HashTableRemoveKey ( HashTable & _ht, int _key )
{
    unsigned int hashCode = HashCode( _key );
    int bucketNr = hashCode % _ht.m_tableSize;

    for ( int i = bucketNr; i < _ht.m_tableSize; i++ )
        if ( _ht.m_pData[ i ].m_key == _key )
        {
            _ht.m_pData[ i ].m_status = HashTable::Element::DELETED;
            --_ht.m_numOccupied;
            return;
        }

    for ( int i = 0; i < bucketNr; i++ )
        if ( _ht.m_pData[ i ].m_key == _key )
        {
            _ht.m_pData[ i ].m_status = HashTable::Element::DELETED;
            --_ht.m_numOccupied;
            return;
        }

    assert( !"key not found" );
}

