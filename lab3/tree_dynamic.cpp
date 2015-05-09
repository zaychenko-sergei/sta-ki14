
#include "tree_dynamic.hpp"


TreeNode * TreeCreateNode ( TreeNodeLabel _label )
{
    TreeNode * pNode = new TreeNode;
    pNode->m_label   = _label;
    pNode->m_pParent = pNode->m_pLeftMostChild = pNode->m_pRightSibling = nullptr;
    return pNode;
}

Tree * TreeCreate ( char _rootLabel )
{
    Tree * pTree = new Tree;
    pTree->m_pRoot = TreeCreateNode ( _rootLabel );
    return pTree;
};


TreeNode * TreeInsertChild ( TreeNode * _pParentNode, char _newLabel )
{
    TreeNode * pNewNode = TreeCreateNode( _newLabel );

    pNewNode->m_pParent = _pParentNode;
        
    if ( ! _pParentNode->m_pLeftMostChild )
        _pParentNode->m_pLeftMostChild = pNewNode;

    else
    {
        TreeNode * pTemp = _pParentNode->m_pLeftMostChild;
        while ( pTemp->m_pRightSibling )
            pTemp = pTemp->m_pRightSibling;

        pTemp->m_pRightSibling = pNewNode;
    }

    return pNewNode;
};


void TreeNodeDestroy ( TreeNode * _pNode )
{
    TreeNode * pCurrent = _pNode->m_pLeftMostChild;
    while ( pCurrent )
    {
        TreeNode * pNext = pCurrent->m_pRightSibling;
        TreeNodeDestroy( pCurrent );
        pCurrent = pNext;
    }

    delete _pNode;
}

void TreeDestroy ( Tree * _pTree )
{
    TreeNodeDestroy( _pTree->m_pRoot );
    delete _pTree;
}


void TreeDirectWalk ( const TreeNode * _pNode, TreeNodeVisitFunction _f )
{
    ( * _f )( * _pNode );

    TreeNode * pChild = _pNode->m_pLeftMostChild;
    while ( pChild )
    {
        TreeDirectWalk( pChild, _f );
        pChild = pChild->m_pRightSibling;
    }
}


void TreeReverseWalk ( const TreeNode * _pNode, TreeNodeVisitFunction _f )
{
    TreeNode * pChild = _pNode->m_pLeftMostChild;
    while ( pChild )
    {
        TreeReverseWalk( pChild, _f );
        pChild = pChild->m_pRightSibling;
    }

    ( * _f )( * _pNode );
}


void TreeSymmetricWalk ( const TreeNode * _pNode, TreeNodeVisitFunction _f )
{
    if ( _pNode->m_pLeftMostChild )
        TreeSymmetricWalk( _pNode->m_pLeftMostChild, _f );

    ( * _f )( * _pNode );

    TreeNode * pChild = _pNode->m_pLeftMostChild;
    if ( ! pChild )
        return;

    while ( true )
    {
        pChild = pChild->m_pRightSibling;
        if ( ! pChild )
            break;

        TreeSymmetricWalk( pChild, _f );
    }
}


void TreeDirectWalk ( const Tree & _t, TreeNodeVisitFunction _f )
{
    TreeDirectWalk( _t.m_pRoot, _f );
}

void TreeReverseWalk ( const Tree & _t, TreeNodeVisitFunction _f )
{
    TreeReverseWalk( _t.m_pRoot, _f );
}

void TreeSymmetricWalk ( const Tree & _t, TreeNodeVisitFunction _f )
{
    TreeSymmetricWalk( _t.m_pRoot, _f );
}
