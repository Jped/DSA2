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
		try{
			throw 0;
		} catch(int e){
			cout << "hash table size is too big"; 
		}
}	

hashTable::hashTable(int size){
		capacity = hashTable::getPrime(size);
		filled = 0;	
		data.resize(capacity);
}



int hashTable::hash(const string &key) {
	// adapted from Data Structures and Algorithm Analysis 3rd edition
	int val = 0;
	for (int i=0; i<key.length(); i++){
		val = 37 * val + key[i];
	}

	val %= capacity;
	if (val<0)
		val += capacity;
	return val;
}


int hashTable::insert(const string &key, void *pv) {
	int loc = findPos(key);
	// check if itm already exsists
	if (loc > -1)
		return 1; 
	if ((2*filled) > capacity) {
		bool resp = rehash();
		if (!resp)
			return 2;
	}
	// make the new hashitem
	hashItem itm;
       	itm.key = key;
	itm.isOccupied = true;
	itm.isDeleted = false;
	itm.pv = pv;
	int hash = hashTable::hash(key);
	while(data[hash].isOccupied) {
		hash++;	
		if (hash == hashTable::capacity)
			hash = 0;
	}
	data[hash] = itm;	
	hashTable::filled++;
	return 0;
}

int hashTable::findPos(const string &key) {
	int hash = hashTable::hash(key);
	if (data[hash].isOccupied) {
		hashItem itm = data[hash];
		while(itm.isOccupied && key!=itm.key){
			hash++;
			if (hash == hashTable::capacity)
				hash = 0;
			itm = data[hash];
		}
		if (key == itm.key) {
			return hash;
		}
	}
	return -1;
}

bool hashTable::rehash() {
	// change the capacity
	int oldCapacity = capacity;
	hashTable::capacity = getPrime(oldCapacity);
	vector<hashItem>oldData = data;
	hashTable::filled = 0;
	hashTable::data.clear();
	hashTable::data.resize(capacity);
	for (int i=0;i<oldCapacity;i++){
		hashItem itm = oldData[i];
		if (itm.isOccupied && !itm.isDeleted){
			int resp = insert(itm.key, itm.pv);
			itm = {};
		}
	}
	oldData.clear();
	return true;
}

bool hashTable::contains(const string &key) {
	int hash = findPos(key);
	if (		
			hash > -1 
			&& data[hash].isOccupied 
			&& !data[hash].isDeleted 
			&& data[hash].key == key
	   ) 
		return true;
	return false;
}

bool hashTable::remove(const string &key) {
	int hash = findPos(key);
	if (
		hash >-1
		&& data[hash].isOccupied
		&& data[hash].key == key
	   ) {
		data[hash].isDeleted = true;
		return true;
	}
	return false;	
}

