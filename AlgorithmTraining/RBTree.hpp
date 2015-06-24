#include <iterator>

typedef enum 
{
	RED = 0,
	BLACK = 1
} Color;

template <typename T>
class RBTree
{
	typedef struct _Node
	{
		Color color;
		T val;
		Node* pParent;
		Node* pLChild;
		Node* pRChild;

		_Node()
		{
			color = RED;
			val = 0;
			pParent = pLChild = pRChild = nullptr;
		}
		~_Node()
		{
			//TODO : delete recursively
		}
	} Node;

public:
private:
	Node* pRootNode;

};