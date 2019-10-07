#include "heap.h"
#include <climits>
#include <cstring>
#include <iostream>

heap::heap(int capacity) { 
	heap::capacity = capacity;
	// zero is kept empty, so size starts at 1
	heap::current_size = 1;
	heap::data.resize(capacity);
	hashTable hash_map(capacity);
	heap::mapping = hash_map;
} 



int heap::insert(const std:: string &id, int key, void *pv){
	if (heap::current_size >= heap::capacity)
		return 1;
	if (heap::mapping.contains(id))
		return 2;
	
	// create the node
	heapItem newItem;
	newItem.id = id;
	newItem.key = key;
	newItem.pv = pv;
	// place it into the end
	heap::data[heap::current_size] = newItem;
	// add it to  the hashtable
	heap::mapping.insert(id, pv=&heap::data[current_size]);
	// perclate up
	heap::percolateUp(heap::current_size);
	heap::current_size++;
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
	// if current size is 1, the heap is empty
	if (heap::current_size <= 1)
		return 1;
	//remove min element from the hashtable.
	heap::mapping.remove(heap::data[1].id);
	if (p_id != nullptr){
		*p_id = heap::data[1].id;
	}if (p_key != nullptr){
		*p_key = heap::data[1].key;
	}if (pp_data != nullptr){
		pp_data = heap::data[1].pv;
	}
	//move last item into root
	heap::data[1] = heap::data[current_size-1];
	current_size--;
	
	//percolate down
	heap::percolateDown(1);

	return 0;
}


int heap::remove(const std::string &id, int *p_key, void *pp_data){
	if (!heap::mapping.contains(id))
		return 1;
	// save key value for node
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
		heap::mapping.setPointer(heap::data[pos_cur].id, &heap::data[pos_cur]);
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
			heap::mapping.setPointer(heap::data[pos_cur].id, &heap::data[pos_cur]);
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




