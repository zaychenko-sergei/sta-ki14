#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

////////////////////////////////////////////////////////////////////////


struct BSTree
{
    struct Node
    {
        int m_key;

        Node * m_pParent;
        Node * m_pLeft;
        Node * m_pRight;
    };

    Node * m_pRoot;
};


///////////////////////////////////////////////////////////////////////


BSTree * BSTreeCreate ();


void BSTreeDestroy ( BSTree * _pTree );


void BSTreeInsertKey ( BSTree & _tree, int _key );


bool BSTreeHasKey ( const BSTree & _tree, int _key );


int BSTreeMinimum ( const BSTree & _tree );


int BSTreeMaximum ( const BSTree & _tree );


typedef void ( * BSTreeWalkFunction ) ( const BSTree::Node & _node );
void BSTreeSymmetricWalk ( const BSTree & _tree, BSTreeWalkFunction _f );


void BSTreeDeleteKey ( BSTree & _tree, int _key );


///////////////////////////////////////////////////////////////////////

#endif //  _BSTREE_HPP_
