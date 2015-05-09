#ifndef _TREE_STATIC_HPP_
#define _TREE_STATIC_HPP_

////////////////////////////////////////////////////////////////////////


struct Tree;

Tree * TreeCreate ( int _nNodes );

void TreeDestroy ( Tree * _pTree );


typedef char TreeNodeLabel;

TreeNodeLabel TreeGetLabel ( const Tree & _tree, int _nodeIndex );

void TreeSetLabel ( Tree & _tree, int _nodeIndex, TreeNodeLabel _label );


int TreeGetRootIndex ( const Tree & _tree );

int TreeGetParentIndex ( const Tree & _tree, int _nodeIndex );

void TreeSetParentIndex ( Tree & _tree, int _nodeIndex, int _parentIndex );

int TreeGetLeftmostChildIndex( const Tree & _tree, int _nodeIndex );

int TreeGetRightSiblingIndex ( const Tree & _tree, int _nodeIndex );


typedef void ( * TreeNodeVisitFunction ) ( const Tree & _t, int _nodeIndex );

void TreeDirectWalk ( const Tree & _t, TreeNodeVisitFunction _f );

void TreeReverseWalk ( const Tree & _t, TreeNodeVisitFunction _f );

void TreeSymmetricWalk ( const Tree & _t, TreeNodeVisitFunction _f );


#endif //  _TREE_STATIC_HPP_
