#ifndef _RBTREE_HPP_
#define _RBTREE_HPP_

////////////////////////////////////////////////////////////////////////


struct RBTree
{
    struct Node
    {
        int m_key;
        enum Color { RED, BLACK } m_color;

        Node * m_pParent;
        Node * m_pLeft;
        Node * m_pRight;
    };

    Node * m_pRoot;
};


///////////////////////////////////////////////////////////////////////


RBTree * RBTreeCreate ();


void RBTreeDestroy ( RBTree * _pTree );


void RBTreeInsertKey ( RBTree & _tree, int _key );


bool RBTreeHasKey ( const RBTree & _tree, int _key );


///////////////////////////////////////////////////////////////////////

#endif //  _RBTREE_HPP_
