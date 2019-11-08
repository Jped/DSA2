#include "heap.h"
#include <climits>
#include <cstring>
#include <iostream>
#include <sstream>


heap::heap(int capacity) { 
	// add one because we dont use index zero
	// and would like the cap to align with what user inputs
	heap::capacity = capacity + 1;
	// before we insert we increment by one
	heap::current_size = 0;
	heap::data.resize(heap::capacity);
	hashTable hash_map(capacity);
	heap::mapping = hash_map;
} 



int heap::insert(const std:: string &id, int key, void *pv){
	// add one to curr size, because we increment then insert
	if ((heap::current_size + 1) == heap::capacity)
		return 1;
	if (heap::mapping.contains(id))
		return 2;
	// create the node
	heapItem newItem;
	newItem.id = id;
	newItem.key = key;
	newItem.pv = pv;
	// move one and place it into the end
	heap::current_size++;
	heap::data[heap::current_size] = newItem;
	// add it to  the hashtable
	int hash_resp = heap::mapping.insert(id, pv=&heap::data[heap::current_size]);
	if (hash_resp != 0){
		std::stringstream error_string;
		error_string << "error while inserting into hash map error: " << hash_resp << " current_size " << heap::current_size << "\n"; 
		perror(error_string.str().c_str());
		return 2;
	}
	// percolate up
	heap::percolateUp(heap::current_size);
	return 0;
}


int heap::setKey(const std::string &id, int key){
	//check if the node exsists
	if (!heap::mapping.contains(id))
		return 1;
	// get the pointer value
	heapItem * item_pn = static_cast<heapItem *> (heap::mapping.getPointer(id));
	int old_key = item_pn->key;
	item_pn->key = key;
	int pos = heap::getPos(item_pn);
	// now we need to determine if we should percolate up or down...
	if (old_key > key)
		heap::percolateUp(pos);
	else if (old_key < key)
		heap::percolateDown(pos);
	return 0;	
}


int heap::deleteMin(std::string *p_id, int *p_key, void *pp_data) {
	if (heap::current_size == 0)
		return 1;
	//remove min element from the hashtable.
	int hash_resp = heap::mapping.remove(heap::data[1].id);
	if (!hash_resp){
		std::stringstream error_string;
		error_string << "error while removing " << heap::data[1].id << " from hash table " << hash_resp << "\n";
		perror(error_string.str().c_str());
		// will not return out as this is an error with the hash table and not the heap
	}
	if (p_id != nullptr){
		*p_id = heap::data[1].id;
	}if (p_key != nullptr){
		*p_key = heap::data[1].key;
	}if (pp_data != nullptr){
		pp_data = heap::data[1].pv;
	}
	//move last item into root
	heap::data[1] = heap::data[heap::current_size];
	heap::current_size--;
	//percolate down
	heap::percolateDown(1);
	return 0;
}


int heap::remove(const std::string &id, int *p_key, void *pp_data){
	if (!heap::mapping.contains(id))
		return 1;
	// save key value for node cause we are going to
	// replace it with INT_MIN
	int current_key;
	if (p_key){
		heapItem * item_pn = static_cast<heapItem *> (heap::mapping.getPointer(id));
		current_key = item_pn -> key;
	}
	// then make the item have the lowest possible value
	heap::setKey(id, INT_MIN);
	// then delete min
	heap::deleteMin(nullptr, p_key, pp_data);
	if (p_key)
		*p_key = current_key;
	return 0;

}

void heap::percolateUp(int pos_cur){
	// adapted from Data Structures and Algorithms by Mark Allen Weiss
	
	// first hold on to what is at pos cur
	heapItem item = heap::data[pos_cur];
	// then keep on moving the hole up as long as heapItem.key is less than the value
	for(;pos_cur>1 && item.key <= heap::data[pos_cur/2].key; pos_cur=pos_cur/2){
		// keep on moving the elements down
		heap::data[pos_cur] = heap::data[pos_cur/2];
		// update hash table
		if (heap::mapping.setPointer(heap::data[pos_cur].id, &heap::data[pos_cur]) != 0) {
			std::stringstream error_string;
			error_string << "error: percolate up set pointer failed" << heap::data[pos_cur].id <<"\n";	
			perror(error_string.str().c_str());
		}
	}
	heap::data[pos_cur] = item;
	heap::mapping.setPointer(item.id, &heap::data[pos_cur]);
}

void heap::percolateDown(int pos_cur){
	// adapted from Data Structures and Algorithms by Mark Allen Weiss
	
	// hold on to the current item
	heapItem item = heap::data[pos_cur];

	// now we are going to move in the reverse direction are percolate up to
	// find the proper place to put this element
	int pos_child;
	for(;pos_cur*2 <= heap::current_size; pos_cur=pos_child){
		pos_child = 2 * pos_cur;
		// pick the lower of the two children
		if (pos_child != heap::current_size && heap::data[pos_child+1].key < heap::data[pos_child].key){
			pos_child++;
		}
		// if the thing is less than what we are putting in move it up into the hole
		// if it isn't break and we'll place it into this spot below
		if (heap::data[pos_child].key < item.key) {
			heap::data[pos_cur] = heap::data[pos_child];
			//update the hash table
			if (heap::mapping.setPointer(heap::data[pos_cur].id, &heap::data[pos_cur]) != 0) {
				std::stringstream error_string;
				error_string << "error: percolate down set pointer failed" << heap::data[pos_cur].id <<"\n";
				perror(error_string.str().c_str());
			}
		} else
			break;
	}
	heap::data[pos_cur] = item;
	heap::mapping.setPointer(item.id, &heap::data[pos_cur]);
}


int heap::getPos(heapItem *pn){
	int pos = pn - &heap::data[0];
	return pos;
}


void heap::printElements() {
	std::cout << "current size of heap: " << heap::current_size << std::endl; 
	for (int i=1; i<heap::current_size; i++){
		std::cout <<i << " " << heap::data[i].id << ":" << heap::data[i].key << " ";
	}
	std::cout << "\n";
}

