#include "tree_static.hpp"
#include <cassert>
#include <cstring>


struct Tree
{
    int m_nNodes;
    
    char * m_pNodeLabels;
    
    struct ChildIndexElement
    {
        int m_childIndex;
        ChildIndexElement * m_pNext;
    };

    ChildIndexElement ** m_pHeader;
};


Tree * TreeCreate ( int _nNodes )
{
    Tree * pTree = new Tree;
    pTree->m_nNodes = _nNodes;
    
    pTree->m_pNodeLabels = new char[ _nNodes ];
    memset( pTree->m_pNodeLabels, 0, _nNodes );

    pTree->m_pHeader = new Tree::ChildIndexElement * [ _nNodes ];
    memset( pTree->m_pHeader, 0, sizeof( Tree::ChildIndexElement * ) * _nNodes );

    return pTree;
}


void TreeDestroy ( Tree * _pTree )
{
    delete[] _pTree->m_pNodeLabels;

    for ( int i = 0; i < _pTree->m_nNodes; i++ )
    {
        Tree::ChildIndexElement * pCurrent = _pTree->m_pHeader[ i ];
        while ( pCurrent )
        {
            Tree::ChildIndexElement * pTemp = pCurrent->m_pNext;
            delete pCurrent;
            pCurrent = pTemp;
        }
    }

    delete[] _pTree->m_pHeader;
    delete _pTree;
}



int TreeGetRootIndex ( const Tree & )
{
    return 0;
}


TreeNodeLabel TreeGetLabel ( const Tree & _tree, int _nodeIndex )
{
    assert( _nodeIndex < _tree.m_nNodes );
    return _tree.m_pNodeLabels[ _nodeIndex ];
}

void TreeSetLabel ( Tree & _tree, int _nodeIndex, TreeNodeLabel _label )
{
    assert( _nodeIndex < _tree.m_nNodes );
    _tree.m_pNodeLabels[ _nodeIndex ] = _label;
}



int TreeGetLeftmostChildIndex ( const Tree & _tree, int _nodeIndex )
{
    assert( _nodeIndex < _tree.m_nNodes );

    Tree::ChildIndexElement * pCurrent = _tree.m_pHeader[ _nodeIndex ];
    return pCurrent ? pCurrent->m_childIndex : -1;
}


int TreeGetParentIndex ( const Tree & _tree, int _nodeIndex )
{
    assert( _nodeIndex < _tree.m_nNodes );

    for ( int i = 0; i < _nodeIndex; i++ )
    {
        Tree::ChildIndexElement * pCurrent = _tree.m_pHeader[ i ];
        while ( pCurrent )
        {
            if ( pCurrent->m_childIndex == _nodeIndex )
                return i;
            pCurrent = pCurrent->m_pNext;
        }
    }

    return -1;
}


int TreeGetRightSiblingIndex ( const Tree & _tree, int _nodeIndex )
{
    assert( _nodeIndex < _tree.m_nNodes );

    for ( int i = 0; i < _nodeIndex; i++ )
    {
        Tree::ChildIndexElement * pCurrent = _tree.m_pHeader[ i ];
        while ( pCurrent )
        {
            if ( pCurrent->m_childIndex == _nodeIndex )
            {
                Tree::ChildIndexElement * pNext = pCurrent->m_pNext;
                return pNext ? pNext->m_childIndex : -1;
            }
            pCurrent = pCurrent->m_pNext;
        }
    }

    return -1;
}


void TreeSetParentIndex ( Tree & _tree, int _nodeIndex, int _parentIndex )
{
    assert( _nodeIndex < _tree.m_nNodes );
    assert( _parentIndex < _nodeIndex );

    Tree::ChildIndexElement * pNewElement = new Tree::ChildIndexElement;
    pNewElement->m_childIndex = _nodeIndex;
    pNewElement->m_pNext = nullptr;

    Tree::ChildIndexElement * pCurrent = _tree.m_pHeader[ _parentIndex ];
    if ( ! pCurrent )
    {
        _tree.m_pHeader[ _parentIndex ] = pNewElement;
        return;
    }


    while ( pCurrent->m_pNext )
        pCurrent = pCurrent->m_pNext;

    pCurrent->m_pNext = pNewElement;
}



void TreeDirectWalk ( const Tree & _tree, int _nodeIndex, TreeNodeVisitFunction _f )
{
    ( *_f )( _tree, _nodeIndex );

    int childIndex = TreeGetLeftmostChildIndex( _tree, _nodeIndex );
    while ( childIndex != -1 )
    {
        TreeDirectWalk( _tree, childIndex, _f );
        childIndex = TreeGetRightSiblingIndex( _tree, childIndex );
    }
}


void TreeReverseWalk ( const Tree & _tree, int _nodeIndex, TreeNodeVisitFunction _f )
{
    int childIndex = TreeGetLeftmostChildIndex( _tree, _nodeIndex );
    while ( childIndex != -1 )
    {
        TreeReverseWalk( _tree, childIndex, _f );
        childIndex = TreeGetRightSiblingIndex( _tree, childIndex );
    }

    ( *_f )( _tree, _nodeIndex );
}


void TreeSymmetricWalk ( const Tree & _tree, int _nodeIndex, TreeNodeVisitFunction _f )
{
    int childIndex = TreeGetLeftmostChildIndex( _tree, _nodeIndex );
    if ( childIndex != -1 )
        TreeSymmetricWalk( _tree, childIndex, _f );

    ( *_f )( _tree, _nodeIndex );

    if ( childIndex == -1 )
        return;

    while ( true )
    {
        childIndex = TreeGetRightSiblingIndex( _tree, childIndex );
        if ( childIndex == -1 )
            break;

        TreeSymmetricWalk( _tree, childIndex, _f );
    }
}


void TreeDirectWalk ( const Tree & _tree, TreeNodeVisitFunction _f )
{
    TreeDirectWalk( _tree, TreeGetRootIndex( _tree ), _f );
}


void TreeReverseWalk ( const Tree & _tree, TreeNodeVisitFunction _f )
{
    TreeReverseWalk( _tree, TreeGetRootIndex( _tree ), _f );
}


void TreeSymmetricWalk ( const Tree & _tree, TreeNodeVisitFunction _f )
{
    TreeSymmetricWalk( _tree, TreeGetRootIndex( _tree ), _f );
}
