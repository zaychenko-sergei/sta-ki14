#ifndef _HASH_TABLE_HPP_
#define _HASH_TABLE_HPP_


struct HashTable;

HashTable* HashTableCreate ( int _initialSize = 100 );

void HashTableDestroy ( HashTable* _pHT );

void HashTableClear ( HashTable & _ht );

int HashTableNumElements ( const HashTable & _ht );

void HashTableInsert ( HashTable & _ht, int _key, int _value );

int HashTableGet ( const HashTable & _ht, int _key );

void HashTableRemoveKey ( HashTable & _ht, int _key );


#endif //  _HASH_TABLE_HPP_

