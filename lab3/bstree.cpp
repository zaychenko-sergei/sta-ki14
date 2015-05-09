////////////////////////////////////////////////////////////////////////

#include "bstree.hpp"

#include <cassert>

////////////////////////////////////////////////////////////////////////


BSTree * BSTreeCreate ()
{
    BSTree * pTree = new BSTree;
    pTree->m_pRoot = nullptr;
    return pTree;
}


////////////////////////////////////////////////////////////////////////


void BSTreeDestroy ( BSTree::Node * _pNode )
{
    if ( ! _pNode )
        return;

    BSTreeDestroy( _pNode->m_pLeft );
    BSTreeDestroy( _pNode->m_pRight );
    delete _pNode;
}


////////////////////////////////////////////////////////////////////////


void BSTreeDestroy ( BSTree * _pTree )
{
    BSTreeDestroy( _pTree->m_pRoot );
}


////////////////////////////////////////////////////////////////////////


BSTree::Node * BSTreeCreateNode ( int _key )
{
    BSTree::Node * pNewNode = new BSTree::Node;
    pNewNode->m_key = _key;
    pNewNode->m_pLeft = pNewNode->m_pRight = pNewNode->m_pParent = nullptr;
    return pNewNode;
}


////////////////////////////////////////////////////////////////////////


void BSTreeInsertKey ( BSTree & _tree, int _key )
{
    BSTree::Node * pCurrent = _tree.m_pRoot;
    if ( ! pCurrent )
    {
        _tree.m_pRoot = BSTreeCreateNode( _key );
        return;
    }

    while ( pCurrent )
    {
        if ( pCurrent->m_key == _key )
            return;

        else if ( _key < pCurrent->m_key )
        {
            if ( pCurrent->m_pLeft )
                pCurrent = pCurrent->m_pLeft;

            else
            {
                BSTree::Node * pNewNode = BSTreeCreateNode( _key );
                pNewNode->m_pParent = pCurrent;
                pCurrent->m_pLeft = pNewNode;
                return;
            }
        }

        else
        {
            if ( pCurrent->m_pRight )
                pCurrent = pCurrent->m_pRight;

            else
            {
                BSTree::Node * pNewNode = BSTreeCreateNode( _key );
                pNewNode->m_pParent = pCurrent;
                pCurrent->m_pRight = pNewNode;
                return;
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////


BSTree::Node * BSTreeFindKeyNode ( const BSTree & _tree, int _key )
{
    BSTree::Node * pCurrent = _tree.m_pRoot;
    while ( pCurrent )
    {
        if ( _key == pCurrent->m_key )
            return pCurrent;

        else if ( _key < pCurrent->m_key )
            pCurrent = pCurrent->m_pLeft;

        else
            pCurrent = pCurrent->m_pRight;
    }

    return nullptr;
}


////////////////////////////////////////////////////////////////////////


bool BSTreeHasKey ( const BSTree & _tree, int _key )
{
    return BSTreeFindKeyNode( _tree, _key ) != nullptr;
}


////////////////////////////////////////////////////////////////////////


BSTree::Node * BSTreeMinimumNode ( BSTree::Node * _pNode )
{
    assert( _pNode );

    BSTree::Node * pCurrent = _pNode;
    while ( pCurrent && pCurrent->m_pLeft )
        pCurrent = pCurrent->m_pLeft;

    return pCurrent;
}


////////////////////////////////////////////////////////////////////////


int BSTreeMinimum ( const BSTree & _tree )
{
    BSTree::Node * pMinimumNode = BSTreeMinimumNode( _tree.m_pRoot );
    return pMinimumNode->m_key;
}


////////////////////////////////////////////////////////////////////////


int BSTreeMaximum ( const BSTree & _tree )
{
    assert( _tree.m_pRoot );

    const BSTree::Node * pCurrent = _tree.m_pRoot;
    while ( pCurrent && pCurrent->m_pRight )
        pCurrent = pCurrent->m_pRight;

    return pCurrent->m_key;
}


////////////////////////////////////////////////////////////////////////


void BSTreeSymmetricWalk ( const BSTree::Node * _pNode, BSTreeWalkFunction _f )
{
    if ( ! _pNode )
        return;

    BSTreeSymmetricWalk( _pNode->m_pLeft, _f );
    ( * _f )( * _pNode );
    BSTreeSymmetricWalk( _pNode->m_pRight, _f );
}


////////////////////////////////////////////////////////////////////////


void BSTreeSymmetricWalk ( const BSTree & _tree, BSTreeWalkFunction _f )
{
    BSTreeSymmetricWalk( _tree.m_pRoot, _f );
}


////////////////////////////////////////////////////////////////////////


void BSTreeTransplant ( BSTree & _tree, BSTree::Node * _pNode, BSTree::Node * _pOtherNode )
{
    if ( ! _pNode->m_pParent )
    {
        assert( _pNode == _tree.m_pRoot );
        _tree.m_pRoot = _pOtherNode;
    }

    else if ( _pNode->m_pParent->m_pLeft == _pNode )
        _pNode->m_pParent->m_pLeft = _pOtherNode;

    else if ( _pNode->m_pParent->m_pRight == _pNode )
        _pNode->m_pParent->m_pRight = _pOtherNode;

    else
        assert( 0 );

    if ( _pOtherNode )
        _pOtherNode->m_pParent = _pNode->m_pParent;
}


////////////////////////////////////////////////////////////////////////


void BSTreeDeleteKey ( BSTree & _tree, int _key )
{
    BSTree::Node * pNode = BSTreeFindKeyNode( _tree, _key );
    if ( ! pNode )
        return;

    if ( ! pNode->m_pLeft )
        BSTreeTransplant( _tree, pNode, pNode->m_pRight );

    else if ( ! pNode->m_pRight )
        BSTreeTransplant( _tree, pNode, pNode->m_pLeft );

    else
    {
        BSTree::Node * pNextNode = BSTreeMinimumNode( pNode->m_pRight );
        if ( pNextNode->m_pParent != pNode )
        {
            BSTreeTransplant( _tree, pNextNode, pNextNode->m_pRight );
            pNextNode->m_pRight = pNode->m_pRight;
            pNextNode->m_pRight->m_pParent = pNextNode;
        }

        BSTreeTransplant( _tree, pNode, pNextNode );
        pNextNode->m_pLeft = pNode->m_pLeft;
        pNextNode->m_pLeft->m_pParent = pNextNode;
    }

    delete pNode;
}


////////////////////////////////////////////////////////////////////////
