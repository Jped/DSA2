#include "hash.h"
#include <iostream>
using namespace std;

unsigned int hashTable::getPrime(int size) {
		// list of primes
		unsigned int primes[9] = {40009, 80329, 160001, 320009, 640007, 1280023, 2400001, 4500007, 9003607};
		for (int i=0; i<9; i++){
			if (primes[i] > size) {
				return primes[i];
			}
		}
		return 0;	
}	

hashTable::hashTable(int size){
		hashTable::capacity = hashTable::getPrime(size);
		hashTable::filled = 0;	
		data.resize(hashTable::capacity);
}



unsigned int hashTable::hash(const string &key) {
	// adapted from Data Structures and Algorithm Analysis 3rd edition
	unsigned int val = 0;
	for (int i=0; i<key.length(); i++){
		val = 37 * val + key[i];
	}
	val %= hashTable::capacity;
	if (val < 0)
		val += hashTable::capacity;
	return val;
}


int hashTable::insert(const string &key, void *pv) {
	bool contain = hashTable::contains(key);
	// check if itm already exsists
	if (contain)
		return 1; 
	if ((2 * hashTable::filled) > hashTable::capacity) {
		bool resp = hashTable::rehash();
		if (!resp)
			return 2;
	}
	// make the new hashitem
	hashItem itm;
       	itm.key = key;
	itm.isOccupied = true;
	itm.isDeleted = false;
	itm.pv = pv;
	unsigned int hash = hashTable::hash(key);
	hash = hashTable::linearProbe(key, hash);
	data[hash] = itm;	
	hashTable::filled++;
	return 0;
}

int hashTable::findPos(const string &key) {
	unsigned int hash = hashTable::hash(key);
	if (data[hash].isOccupied) {
		hash = hashTable::linearProbe(key, hash);	
		if (key == hashTable::data[hash].key) {
			return hash;
		}
	}
	return -1;
}

unsigned int hashTable::linearProbe(const string &key, unsigned int hash) {
	while(hashTable::data[hash].isOccupied && key!=hashTable::data[hash].key){
		hash++;
		hash = hash % hashTable::capacity;
	}
	return hash;
}

bool hashTable::rehash() {
	// change the capacity
	int oldCapacity = hashTable::capacity;
	hashTable::capacity = getPrime(oldCapacity);
	vector<hashItem>oldData = hashTable::data;
	hashTable::filled = 0;
	hashTable::data.clear();
	hashTable::data.resize(hashTable::capacity);
	for (int i=0; i<oldCapacity; i++){
		if (oldData[i].isOccupied && !oldData[i].isDeleted){
			insert(oldData[i].key, oldData[i].pv);
			oldData[i] = {};
		}
	}
	oldData.clear();
	return true;
}

bool hashTable::contains(const string &key) {
	int hash = hashTable::findPos(key);
	if (		
			hash > -1 
			&& hashTable::data[hash].isOccupied 
			&& !hashTable::data[hash].isDeleted 
			&& hashTable::data[hash].key == key
	   ) 
		return true;
	return false;
}

bool hashTable::remove(const string &key) {
	int hash = hashTable::findPos(key);
	if (
		hash >-1
		&& hashTable::data[hash].isOccupied
		&& hashTable::data[hash].key == key
	   ) {
		hashTable::data[hash].isDeleted = true;
		return true;
	}
	return false;	
}


int hashTable::setPointer(const std::string &key, void *pv){
	int hash = hashTable::findPos(key); 
	if (hash == -1)
		return 1;
	hashTable::data[hash].pv = pv;
	return 0;
}


void * hashTable::getPointer(const std::string &key, bool *b){
	int hash = hashTable::findPos(key);
	if (hash == -1){
		if(b)
			*b = false;
		return nullptr;
	}

	if(b)
		*b = true;
	return hashTable::data[hash].pv;
}
