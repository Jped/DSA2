#include "hash.h"
#include <string> 
#include <vector>

class heap {
	public: 
		

		// The constructor to create the heap
		heap(int capacity);


		// The insert function
		// 	Returns: 
		// 		0 on success
		// 		1 if the heap is already filled to capacity
		// 		2 if a node with the given id already exsists (but there is still space)
		int insert(const std:: string &id, int key, void *pv = nullptr);

		// The setKey function, set the key of specified to node to the specified value
		// 	Returns:
		// 		0 on success
		// 		1 if a node with the given id does not exsist
		int setKey(const std::string &id, int key);

		// The deleteMin function, delete the data associated with the smallest key and then
		// 	delete that node from the binary heap
		//	If pId is supplied (i.e., it is not nullptr), write to that address
	  	// 	the id of the node being deleted. If pKey is supplied, write to
  		// 	that address the key of the node being deleted. If ppData is
  		// 	supplied, write to that address the associated void pointer.
		// 	Returns: 
		// 		0 on success
		// 		1 if the heap is empty
		int deleteMin(std::string *p_id = nullptr, int *p_key = nullptr, void *pp_data = nullptr);
		
		// The remove function, delete the node with the specified id from the binary heap
		// 	If pKey is supplied, write to that address the key of the node
  		// 	being deleted. If ppData is supplied, write to that address the
  		// 	associated void pointer.
		// 	Returns:
		// 		0 on a success
		// 		1 if the node with the given id does not exsist
		int remove(const std::string &id, int *p_key = nullptr, void *pp_data = nullptr);
		
	private:
		class heapItem { 
			public:
				std::string id {""};
				int key {0};
				void *pv {nullptr};
				heapItem() = default;
		};
		
		int capacity;
		int current_size;
		std::vector<heapItem> data;
		hashTable mapping;	
		void percolateUp(int pos_cur);
		void percolateDown(int pos_cur);
		int getPos(heapItem *pn);	
		void printElements();
};
