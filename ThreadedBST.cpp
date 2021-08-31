
#include "ThreadedBST.h"

void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode *curr = this->min();

	while (curr != NULL) {

		BSTNode *n = this->next(curr);

		delete curr;

		curr = n;

	}
}

void ThreadedBST::add(int key) {
	BSTNode *q = NULL;
	BSTNode *p = root;
	while (p != NULL)
	{
		q = p;
		if (key == p->key) return ; 
		if (key < p->key)
		{
			if (p->leftLinkType == CHILD)
			{
				p = p->left;
			}
			else 
			  break;
		}
			
		else if (key > p->key)
		{
			if (p->rightLinkType == CHILD)
			{
				p = p->right;
			}
			else
				break;
		}
	}

		BSTNode* z = new BSTNode(key);

		if (q == NULL)
		{
			root = z;

		}
		else if (key < q->key)
		{
 		
			z->right = q;
			z->left = q->left;
		    q->leftLinkType = CHILD;
			q->left = z;

		}
		else if(key>q->key)
		{
			z->right = q->right;
			z->left = q;
			q->rightLinkType = CHILD;
			q->right = z;
		}



} 
void ThreadedBST::remove(int key) {
	BSTNode* q = NULL;
	BSTNode* p = root;
	int ç;

	while (p != NULL)
	{
		
		if (key == p->key)
		{
			break;
		}
		q = p;
		if (key < p->key)
		{
			if (p->leftLinkType == CHILD)
			{
				p = p->left;
			}
			else
				break;
		}

		else if (key > p->key)
		{
			if (p->rightLinkType == CHILD)
			{
				p = p->right;
			}
			else
				break;
		}
	
	}
	
	BSTNode* real = p;


	if (p->leftLinkType == THREAD && p->rightLinkType == THREAD) //NOT CHILD ---------
	{
		ç = 0;
		if (q == NULL)
		{
			root = NULL;
		}

		else if (p == q->left)
		{
			q->leftLinkType = THREAD;
			q->left = p->left;
		}
		else
		{
			q->rightLinkType = THREAD;
			q->right = p->right;
		}

		delete(p);
	}

	else if(p->leftLinkType==CHILD && p->rightLinkType == THREAD || p->rightLinkType == CHILD&& p->leftLinkType == THREAD)
	{
		ç = 1;
		struct BSTNode* çocuk;
		if (p->leftLinkType == CHILD)
		{
			çocuk = p->left;
		}
		else
			çocuk = p->right;

		if (q == NULL)
		{
			root = çocuk;
		}
		else if (p == q->left)
		{
			q->left = çocuk;
		}
		else
		{
			q->right = çocuk;
		}


		BSTNode* x;
		BSTNode* y;

		//Sec
		if (p->rightLinkType == THREAD)
		{
			x = p->right;
		}
		else
		{
			p = p->right;
			while (p->leftLinkType == CHILD)
			{
				p = p->left;
			}
			x = p;
		}

		//pre
		if (p->leftLinkType == THREAD)
		{
			y = p->left;
		}
		else 
		{
			p = p->left;
			while (p->rightLinkType == CHILD)
			{
				p = p->right;
			}
			y = p;
		}



		// p sol subtree ise
		if (real->leftLinkType == CHILD)
		{
			y->right = x;
		}
		// p sað subtree ise
		else if (real->rightLinkType == CHILD)
		{
			x->right = y;
		}
		delete(real);

	}



	
	// 2 ÇOCUK 
	else if (p->leftLinkType==CHILD && p->rightLinkType==CHILD) {
		BSTNode* ps = p;
		BSTNode* s = p->right;

		while (s->leftLinkType==CHILD) {
		    ps = s;
			s = s->left ;
		} 


		p->key = s->key;


		if (s->leftLinkType == THREAD && s->rightLinkType == THREAD) //NOT CHILD --------
		{
			ç = 0;
			if (ps == NULL)
			{
				root = NULL;
			}

			else if (s == ps->left)
			{
				ps->leftLinkType = THREAD;
				ps->left = s->left;
			}
			else
			{
				ps->rightLinkType = THREAD;
				ps->right = s->right;
			}

			delete(s);
		}
	    





		else //ONE CHILD ------
		{
			ç = 1;
			struct BSTNode* çocuk;
			if (s->leftLinkType == CHILD)
			{
				çocuk = s->left;
			}
			else
				çocuk = s->right;

			if (ps == NULL)
			{
				root = çocuk;
			}
			else if (s == ps->left)
			{
				ps->left = çocuk;
			}
			else
			{
				ps->right = çocuk;
			}


			BSTNode* x;
			BSTNode* y;

			//Sec
			if (s->rightLinkType == THREAD)
			{
				x = s->right;
			}
			else
			{
				s = s->right;
				while (s->leftLinkType == CHILD)
				{
					s = s->left;
				}
				x = s;
			}

			//pre
			if (s->leftLinkType == THREAD)
			{
				y = s->left;
			}
			else
			{
				s = s->left;
				while (s->rightLinkType == CHILD)
				{
					s = s->right;
				}
				y = s;
			}



			// p sol subtree ise
			if (real->leftLinkType == CHILD)
			{
				y->right = x;
			}
			// p sað subtree ise
			else if (real->rightLinkType == CHILD)
			{
				x->right = y;
			}
			delete(real);
		}


	} 

} 

///-------------------------
BSTNode *ThreadedBST::find(int key) {
	
	BSTNode *poin = root;

	while (poin != NULL) {

		if (key == poin->key)
			return poin;
		else if (key < poin->key)
			poin = poin->left;
		else
			poin = poin->right;

	}

	return NULL;
} 


BSTNode* ThreadedBST::min() {
	if (root == NULL)
		return NULL;

	BSTNode *po = root;
	while (po->left != NULL)
		po = po->left;

	return po;
} 

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
	if (root == NULL)
		return NULL;

	BSTNode *poi = root;
	while (poi->right != NULL)
		poi = poi->right;

	return poi;
	
} 

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {


	if (node->leftLinkType == THREAD)
		return node->left;

	else {
		node = node->left;
		while (node->rightLinkType == CHILD)
			node = node->right;
		return node;
	}

	return NULL;

}

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {

	if (node->rightLinkType== THREAD)
		return node->right;

	else  {
		node = node->right;
		while (node->leftLinkType == CHILD)
			node = node->left;
		return node;
	}

	return NULL;

} 