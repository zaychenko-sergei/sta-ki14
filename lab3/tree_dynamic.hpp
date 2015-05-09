#ifndef _TREE_DYNAMIC_HPP_
#define _TREE_DYNAMIC_HPP_

typedef char TreeNodeLabel;


struct TreeNode
{
    TreeNodeLabel m_label;
    TreeNode* m_pParent;
    TreeNode* m_pLeftMostChild;
    TreeNode* m_pRightSibling;
};


struct Tree
{
    TreeNode * m_pRoot;
};


Tree * TreeCreate ( TreeNodeLabel _rootLabel );

void TreeDestroy ( Tree * _pTree );


TreeNodeLabel TreeGetLabel ( const Tree & _tree, int _nodeIndex );

void TreeSetLabel ( Tree & _tree, int _nodeIndex, TreeNodeLabel _label );

TreeNode * TreeGetRootNode ( const Tree & _tree );

TreeNode * TreeInsertChild ( TreeNode * _pParentNode, char _newLabel );


typedef void ( * TreeNodeVisitFunction ) ( const TreeNode & _node );

void TreeDirectWalk ( const Tree & _t, TreeNodeVisitFunction _f );

void TreeReverseWalk ( const Tree & _t, TreeNodeVisitFunction _f );

void TreeSymmetricWalk ( const Tree & _t, TreeNodeVisitFunction _f );


#endif //  _TREE_DYNAMIC_HPP_
