#include "hash_table.hpp"

#include <cassert>
#include <cstring>


struct HashTable
{
    struct Element
    {
        int m_key;
        int m_value;
        Element* m_pNext;
    };

    int m_tableSize;
    int m_numElements;
    Element** m_pData;
};


HashTable* HashTableCreate ( int _initialSize )
{
    HashTable * ht = new HashTable;

    ht->m_tableSize     = _initialSize;
    ht->m_numElements   = 0;
    ht->m_pData         = new HashTable::Element*[ ht->m_tableSize ];
    memset( ht->m_pData, 0, sizeof ( HashTable::Element* ) * ht->m_tableSize );

    return ht;
}


void HashTableDestroy ( HashTable* _pHT )
{
    HashTableClear( * _pHT );

    delete[] _pHT->m_pData;
    delete _pHT;
}


void HashTableClear ( HashTable & _ht )
{
    _ht.m_numElements   = 0;
    for ( int i = 0; i < _ht.m_tableSize; i++ )
    {
        HashTable::Element* element = _ht.m_pData[ i ];
        while ( element )
        {
            HashTable::Element* temp = element->m_pNext;
            delete element;
            element = temp;
        }

        _ht.m_pData[ i ] = nullptr;
    }
}


int HashTableNumElements ( const HashTable & _ht )
{
    return _ht.m_numElements;
}


unsigned int HashCode ( int _key )
{
    unsigned int hashCode = _key;
    return hashCode;
}


HashTable::Element* HashTableMakeElement ( int _key, int _value, HashTable::Element* _next )
{
    HashTable::Element* newElement = new HashTable::Element;
    newElement->m_key   = _key;
    newElement->m_value = _value;
    newElement->m_pNext = _next;
    return newElement;
}


void HashTableInsert ( HashTable & _ht, int _key, int _value )
{
    unsigned int hashCode = HashCode( _key );
    int bucketNr = hashCode % _ht.m_tableSize;

    HashTable::Element* element = _ht.m_pData[ bucketNr ];
    if ( !element )
    {
        _ht.m_pData[ bucketNr ] = HashTableMakeElement( _key, _value, nullptr );
        _ht.m_numElements++;
    }
    else
    {
        HashTable::Element* prevElement = nullptr;
        while ( element )
        {
            if ( element->m_key == _key )
            {
                element->m_value = _value;
                return;
            }
            else if ( element->m_key > _key )
            {
                HashTable::Element* newElement = HashTableMakeElement( _key, _value, element );
                if ( prevElement )
                    prevElement->m_pNext = newElement;
                else
                    _ht.m_pData[ bucketNr ] = newElement;
                _ht.m_numElements++;
                return;
            }
            else if ( !element->m_pNext )
            {
                _ht.m_numElements++;
                element->m_pNext = HashTableMakeElement( _key, _value, nullptr );
                return;
            }

            prevElement = element;
            element     = element->m_pNext;
        }
    }
}


int HashTableGet ( const HashTable & _ht, int _key )
{
    unsigned int hashCode = HashCode( _key );
    int bucketNr = hashCode % _ht.m_tableSize;

    const HashTable::Element* element = _ht.m_pData[ bucketNr ];
    while ( element )
    {
        if ( element->m_key == _key )
            return element->m_value;
        else if ( element->m_key > _key )
            break;

        element = element->m_pNext;
    }

    return -1;
}


void HashTableRemoveKey ( HashTable & _ht, int _key )
{
    unsigned int hashCode = HashCode( _key );
    int bucketNr = hashCode % _ht.m_tableSize;

    HashTable::Element* element     = _ht.m_pData[ bucketNr ];
    HashTable::Element* prevElement = nullptr;
    while ( element )
    {
        if ( element->m_key == _key )
        {
            if ( prevElement )
                prevElement->m_pNext = element->m_pNext;
            else
                _ht.m_pData[ bucketNr ] = element->m_pNext;
            
            delete element;
            _ht.m_numElements--;
            return;
        }
        else if ( element->m_key > _key )
            break;
        
        prevElement = element;
        element = element->m_pNext;
    }
}
