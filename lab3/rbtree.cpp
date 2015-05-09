////////////////////////////////////////////////////////////////////////

#include "rbtree.hpp"

#include <cassert>

////////////////////////////////////////////////////////////////////////


RBTree * RBTreeCreate ()
{
    RBTree * pTree = new RBTree;
    pTree->m_pRoot = nullptr;
    return pTree;
}


////////////////////////////////////////////////////////////////////////


void RBTreeDestroy ( RBTree::Node * _pNode )
{
    if ( ! _pNode )
        return;

    RBTreeDestroy( _pNode->m_pLeft );
    RBTreeDestroy( _pNode->m_pRight );
    delete _pNode;
}


////////////////////////////////////////////////////////////////////////


void RBTreeDestroy ( RBTree * _pTree )
{
    RBTreeDestroy( _pTree->m_pRoot );
}


////////////////////////////////////////////////////////////////////////


RBTree::Node * RBTreeCreateNode ( int _key )
{
    RBTree::Node * pNewNode = new RBTree::Node;
    pNewNode->m_key   = _key;
    pNewNode->m_color = RBTree::Node::RED;

    pNewNode->m_pLeft = pNewNode->m_pRight = pNewNode->m_pParent = nullptr;
    return pNewNode;
}


////////////////////////////////////////////////////////////////////////


RBTree::Node * RBTreeInsertBase ( RBTree & _tree, int _key )
{
    RBTree::Node * pCurrent = _tree.m_pRoot;
    if ( ! pCurrent )
    {
        _tree.m_pRoot = RBTreeCreateNode( _key );
        return _tree.m_pRoot;
    }

    while ( pCurrent )
    {
        if ( pCurrent->m_key == _key )
            return nullptr;

        else if ( _key < pCurrent->m_key )
        {
            if ( pCurrent->m_pLeft )
                pCurrent = pCurrent->m_pLeft;

            else
            {
                RBTree::Node * pNewNode = RBTreeCreateNode( _key );
                pNewNode->m_pParent = pCurrent;
                pCurrent->m_pLeft = pNewNode;
                return pNewNode;
            }
        }

        else
        {
            if ( pCurrent->m_pRight )
                pCurrent = pCurrent->m_pRight;

            else
            {
                RBTree::Node * pNewNode = RBTreeCreateNode( _key );
                pNewNode->m_pParent = pCurrent;
                pCurrent->m_pRight = pNewNode;
                return pNewNode;
            }
        }
    }

    assert( 0 );
    return nullptr;
}


////////////////////////////////////////////////////////////////////////


RBTree::Node::Color RBTreeColorOf ( const RBTree::Node * _pNode )
{
    return ( _pNode ) ? _pNode->m_color : RBTree::Node::BLACK;
}


////////////////////////////////////////////////////////////////////////


void RBTreeLeftRotate ( RBTree & _tree, RBTree::Node * _l )
{
    RBTree::Node* r = _l->m_pRight;
    if ( ! r )
        return;

    _l->m_pRight = r->m_pLeft;
    if ( _l->m_pRight )
        _l->m_pRight->m_pParent = _l;

    r->m_pParent = _l->m_pParent;
    if ( ! r->m_pParent )
        _tree.m_pRoot = r;
    else if ( _l == _l->m_pParent->m_pLeft )
        _l->m_pParent->m_pLeft = r;
    else if ( _l == _l->m_pParent->m_pRight )
        _l->m_pParent->m_pRight = r;
    else
        assert( 0 );

    r->m_pLeft    = _l;
    _l->m_pParent = r;
}


////////////////////////////////////////////////////////////////////////


void RBTreeRightRotate ( RBTree & _tree, RBTree::Node * _r )
{
    RBTree::Node* l = _r->m_pLeft;
    if ( ! l )
        return;

    _r->m_pLeft = l->m_pRight;
    if ( _r->m_pLeft )
        _r->m_pLeft->m_pParent = _r;

    l->m_pParent = _r->m_pParent;
    if ( ! l->m_pParent )
        _tree.m_pRoot = l;
    else if ( _r == _r->m_pParent->m_pLeft )
        _r->m_pParent->m_pLeft = l;
    else if ( _r == _r->m_pParent->m_pRight )
        _r->m_pParent->m_pRight = l;
    else
        assert( 0 );

    l->m_pRight = _r;
    _r->m_pParent = l;
}



////////////////////////////////////////////////////////////////////////


void RBTreeInsertKey ( RBTree & _tree, int _key )
{
    RBTree::Node * x = RBTreeInsertBase( _tree, _key );
    if ( ! x )
        return;
    
    RBTree::Node * p;
    while ( x && ( p = x->m_pParent ) && RBTreeColorOf( p ) == RBTree::Node::RED )
    {
        RBTree::Node* pp = p->m_pParent;
        if ( p == pp->m_pLeft )
        {
            RBTree::Node* y = pp->m_pRight;
            if ( RBTreeColorOf( y ) == RBTree::Node::RED )
            {
                p->m_color = RBTree::Node::BLACK;
                y->m_color = RBTree::Node::BLACK;
                pp->m_color = RBTree::Node::RED;
                x = pp;
            }
            else
            {
                if ( x == p->m_pRight )
                {
                    x = p;
                    RBTreeLeftRotate( _tree, x );
                }

                p = x->m_pParent;
                pp = p->m_pParent;

                p->m_color = RBTree::Node::BLACK;
                if ( pp )
                {
                    pp->m_color = RBTree::Node::RED;
                    RBTreeRightRotate( _tree, pp );
                }
            }
        }
        else
        {
            RBTree::Node* y = pp->m_pLeft;
            if ( RBTreeColorOf( y ) == RBTree::Node::RED )
            {
                p->m_color  = RBTree::Node::BLACK;
                y->m_color  = RBTree::Node::BLACK;
                pp->m_color = RBTree::Node::RED;
                x = pp;
            }
            else
            {
                if ( x == p->m_pLeft )
                {
                    x = p;
                    RBTreeRightRotate( _tree, x );
                }

                p = x->m_pParent;
                pp = p->m_pParent;

                p->m_color = RBTree::Node::BLACK;
                if ( pp )
                {
                    pp->m_color = RBTree::Node::RED;
                    RBTreeLeftRotate( _tree, pp );
                }
            }
        }
    }

    _tree.m_pRoot->m_color = RBTree::Node::BLACK;
}


////////////////////////////////////////////////////////////////////////


RBTree::Node * RBTreeFindKeyNode ( const RBTree & _tree, int _key )
{
    RBTree::Node * pCurrent = _tree.m_pRoot;
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


bool RBTreeHasKey ( const RBTree & _tree, int _key )
{
    return RBTreeFindKeyNode( _tree, _key ) != nullptr;
}


////////////////////////////////////////////////////////////////////////
