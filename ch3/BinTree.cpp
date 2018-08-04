// ��������� 

#include <iostream>
#include <stack>
using namespace std;

typedef struct STreeNode* pSTreeNode;
typedef int TreeKeyType;

struct STreeNode 
{
	TreeKeyType key;
	pSTreeNode pLeftChild;
	pSTreeNode pRightChild;

	STreeNode( TreeKeyType Value )
	{
		key = Value;
		pLeftChild = NULL;
		pRightChild = NULL;
	}
};

class CBinTree
{
private:
	
	// insert ��  search  ��������Ӧһ��˽�з������������һ��node���� 
	void Insert( pSTreeNode pNode, TreeKeyType Value );
	
	pSTreeNode Search( pSTreeNode pNode, TreeKeyType Value );
	
	void FreeMemory( pSTreeNode pNode );	//	�ͷ��ڴ�
	
public:
	CBinTree();
	~CBinTree();

	void Insert( TreeKeyType Value );
	

	pSTreeNode Search( TreeKeyType Value );
	
	
	void Delete( TreeKeyType Value );

	void Preorder( );		//	ǰ�����,�ǵݹ鷽�������ö�ջ��
	void Inorder( );		//	�������,�ǵݹ鷽�������ö�ջ��
	void Postorder( );		//	�������,�ǵݹ鷽�������ö�ջ��

	void PreorderRecursively( pSTreeNode pNode );	//	ǰ��������ݹ����
	void InorderRecursively( pSTreeNode pNode );	//	����������ݹ����
	void PostorderRecursively( pSTreeNode pNode );	//	����������ݹ����

	pSTreeNode GetMaxKey();		//	��ö����������Ԫ��ֵ���Ľڵ�
	pSTreeNode GetMinKey();		//	��ö����������Ԫ��ֵ��С�Ľڵ�


	
public:
	pSTreeNode pRoot;
};

CBinTree::CBinTree()
{
	pRoot = NULL;
}

CBinTree::~CBinTree()
{
	if ( pRoot == NULL )
		return;

	FreeMemory( pRoot );
}

void CBinTree::FreeMemory( pSTreeNode pNode )
{
	if ( pNode == NULL )
		return;

	if ( pNode->pLeftChild != NULL )
		FreeMemory( pNode->pLeftChild );

	if ( pNode->pRightChild != NULL )
		FreeMemory( pNode->pRightChild );

	delete pNode;
	pNode = NULL;
}

void CBinTree::Insert( TreeKeyType Value )
{
	if ( pRoot == NULL )
		pRoot = new STreeNode( Value );
	else
		Insert( pRoot, Value );
}

void CBinTree::Insert( pSTreeNode pNode, TreeKeyType Value )
{
	if ( pNode->key > Value )
	{
		if ( pNode->pLeftChild == NULL)
			pNode->pLeftChild = new STreeNode( Value );
		else
			Insert( pNode->pLeftChild, Value );
	}
	else
	{
		if ( pNode->pRightChild == NULL)
			pNode->pRightChild = new STreeNode( Value );
		else
			Insert( pNode->pRightChild, Value );
	}
}

pSTreeNode CBinTree::Search( TreeKeyType Value )
{
	return Search( pRoot, Value );
}

pSTreeNode CBinTree::Search( pSTreeNode pNode, TreeKeyType Value )
{
	if ( pNode == NULL )
		return NULL;

	if ( pNode->key == Value )
		return pNode;
	else
	{
		if ( pNode->key > Value )
			return Search( pNode->pLeftChild, Value );
		else
			return Search( pNode->pRightChild, Value );
	}
}

void CBinTree::Delete( TreeKeyType Value )
{
	pSTreeNode pParentNode = pRoot;
	pSTreeNode pFindNode = pRoot;
	//	�ҵ�ValueԪ�ض�Ӧ�Ľڵ�
	while ( pFindNode != NULL )
	{
		if ( pFindNode->key == Value )
			break;

		pParentNode = pFindNode;
		if ( pFindNode->key > Value )
			pFindNode = pFindNode->pLeftChild;
		else
			pFindNode = pFindNode->pRightChild;
	}

	if ( pFindNode == NULL )
		return;


	//	����ValueԪ�صĸ��ڵ��ValueԪ�صĽڵ�
	if ( pFindNode->pLeftChild == NULL || pFindNode->pRightChild == NULL )
	{
		//	һ���ӽ��Ϊ�ջ��������ӽ�㶼Ϊ��
		pSTreeNode pTemp = NULL;
		if ( pFindNode->pLeftChild != NULL)
			pTemp = pFindNode->pLeftChild;
		else if ( pFindNode->pRightChild != NULL )
			pTemp = pFindNode->pRightChild;

		if ( pParentNode->pLeftChild == pFindNode )
			pParentNode->pLeftChild = pTemp;
		else
			pParentNode->pRightChild = pTemp;

		delete pFindNode;
		pFindNode = NULL;
	}
	else
	{
		//	�ҵ�ǰ���ڵ�
		pSTreeNode pTemp = pFindNode->pLeftChild;
		pSTreeNode pTempParent = pFindNode;

		while ( pTemp->pRightChild != NULL )
		{
			pTempParent = pTemp;
			pTemp = pTemp->pRightChild;	
		}

		pFindNode->key = pTemp->key;
		pTempParent->pRightChild = NULL;
		delete pTemp;
		pTemp = NULL;
	}
}

void CBinTree::Preorder(  )
{
	if ( pRoot == NULL )
	{
		cout << "������Ϊ�գ�" << endl;
		return;
	}

	stack<pSTreeNode> StackTree;
	pSTreeNode pNode = pRoot;
	while( pNode != NULL || !StackTree.empty())
	{
		while ( pNode != NULL )
		{
			cout << " " << pNode->key << " ";
			StackTree.push(pNode);
			pNode = pNode->pLeftChild;
		}
		
		pNode = StackTree.top();
		StackTree.pop();
		pNode = pNode->pRightChild;
	}

}

void CBinTree::Inorder( )
{
	if ( pRoot == NULL )
	{
		cout << "������Ϊ�գ�" << endl;
		return;
	}

	stack<pSTreeNode> StackTree;
	pSTreeNode pNode = pRoot;
	while ( pNode != NULL || !StackTree.empty() )
	{
		while ( pNode != NULL )
		{
			StackTree.push( pNode );
			pNode = pNode->pLeftChild;
		}

		pNode = StackTree.top();
		StackTree.pop();
		cout << " " << pNode->key << " ";
		pNode = pNode->pRightChild;
	}
}


//	��������visited��ʾ�Ƿ���ʹ��ø��ڵ㡣���ʹ��Ļ����������
void CBinTree::Postorder( )
{
	if ( pRoot == NULL )
	{
		cout << "������Ϊ�գ�" << endl;
		return;
	}

	stack< pair<pSTreeNode, bool>> StackTree;
	StackTree.push( make_pair( pRoot, false ));
	
	while ( !StackTree.empty() )
	{
		pSTreeNode pNode = StackTree.top().first;
		bool bVisited = StackTree.top().second;
		

		if (pNode == NULL)
		{
			StackTree.pop();
			continue;
		}

		if (bVisited)
		{
			cout << " " << pNode->key << " ";
			StackTree.pop();
		}
		else
		{
			StackTree.top().second = true;
			StackTree.push( make_pair( pNode->pRightChild, false));
			StackTree.push( make_pair( pNode->pLeftChild, false));
		}
	}
}

void CBinTree::PreorderRecursively( pSTreeNode pNode )
{
	if (pNode == NULL)
		return;

	cout << " " << pNode->key << " ";
	PreorderRecursively( pNode->pLeftChild );
	PreorderRecursively( pNode->pRightChild );
}

void CBinTree::InorderRecursively( pSTreeNode pNode )
{
	if (pNode == NULL)
		return;

	InorderRecursively( pNode->pLeftChild );
	cout << " " << pNode->key << " ";
	InorderRecursively( pNode->pRightChild );
}

void CBinTree::PostorderRecursively( pSTreeNode pNode )
{
	if (pNode == NULL)
		return;

	PostorderRecursively( pNode->pLeftChild );
	PostorderRecursively( pNode->pRightChild );
	cout << " " << pNode->key << " ";
}

pSTreeNode CBinTree::GetMaxKey()
{
	if ( pRoot == NULL )
	{
		cout << "������Ϊ�գ�" << endl;
		return NULL;
	}

	pSTreeNode pNode = pRoot;
	while ( pNode->pRightChild != NULL )
		pNode = pNode->pRightChild;

	return pNode;
}

pSTreeNode CBinTree::GetMinKey()
{
	if ( pRoot == NULL )
	{
		cout << "������Ϊ�գ�" << endl;
		return NULL;
	}

	pSTreeNode pNode = pRoot;
	while ( pNode->pLeftChild != NULL )
		pNode = pNode->pLeftChild;

	return pNode;
}

int main()
{
	CBinTree* pBinTree = new CBinTree();
	if ( pBinTree == NULL )
		return 0;

	pBinTree->Insert( 15 );
	pBinTree->Insert( 3 );
	pBinTree->Insert( 20 );
	pBinTree->Insert( 8 );
	pBinTree->Insert( 10 );
	pBinTree->Insert( 18);
	pBinTree->Insert( 6 );
	pBinTree->Insert( 1);
	pBinTree->Insert( 26);

	pSTreeNode pRoot = pBinTree->pRoot;
	
	cout << " �ǵݹ�ǰ�����	��" ;
	pBinTree->Preorder();
	cout << endl;

	cout << " �ݹ�ǰ�����	��" ;
	pBinTree->PreorderRecursively( pRoot );
	cout << endl;

	cout << " �ǵݹ��������	��" ;
	pBinTree->Inorder();
	cout << endl;

	cout << " �ݹ��������	��" ;
	pBinTree->InorderRecursively( pRoot );
	cout << endl;

	cout << " �ǵݹ�������	��" ;
	pBinTree->Postorder();
	cout << endl;

	cout << " �ݹ��������	��";
	pBinTree->PostorderRecursively( pRoot );
	cout << endl;

	pSTreeNode pMaxNode = pBinTree->GetMaxKey();
	pSTreeNode pMinNode = pBinTree->GetMinKey();
	if ( pMaxNode != NULL )
		cout << " �ö�������������Ԫ���ǣ�" << pMaxNode->key << endl;

	if (pMinNode != NULL )
		cout << " �ö������������СԪ���ǣ�" << pMinNode->key << endl;

	TreeKeyType DeleteKey = 15;
	pSTreeNode pSearchNode = pBinTree->Search( DeleteKey );
	if ( pSearchNode != NULL )
		cout << " ��Ҫ��ѯ��Ԫ���ǣ�" << DeleteKey << ", ʵ�ʲ�ѯ����Ԫ���ǣ�" << pSearchNode->key << endl;
	else
		cout << " û�в�ѯ��Ԫ��" << DeleteKey << endl;
	pBinTree->Delete( DeleteKey );
	cout << " ɾ��Ԫ��" << DeleteKey << "֮��ĵݹ�ǰ�������";
	pBinTree->PreorderRecursively( pRoot );
	cout << endl;

	DeleteKey = 1;
	pBinTree->Delete( DeleteKey );
	cout << " ɾ��Ԫ��" << DeleteKey << "֮��ĵݹ�ǰ�������";
	pBinTree->PreorderRecursively( pRoot );
	cout << endl;

	DeleteKey = 8;
	pBinTree->Delete( DeleteKey );
	cout << " ɾ��Ԫ��" << DeleteKey << "֮��ĵݹ�ǰ�������";
	pBinTree->PreorderRecursively( pRoot );
	cout << endl;

	DeleteKey = 26;
	pBinTree->Delete( DeleteKey );
	cout << " ɾ��Ԫ��" << DeleteKey << "֮��ĵݹ�ǰ�������";
	pBinTree->PreorderRecursively( pRoot );
	cout << endl;

	delete pBinTree;
	pBinTree = NULL;
	system( "pause" );
	return 1;
}
