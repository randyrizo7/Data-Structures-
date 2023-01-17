//
// Created by Randy Rizo on 11/19/22.
//

#ifndef LAB6_HASHTABLE_H
#define LAB6_HASHTABLE_H

class HashTable {
public:
    HashTable(int capacity);
    ~HashTable();
    int put(int key, int value);
    int get(int key);
    bool contains(int key);
    int size();
    bool empty();
private:
    struct Bucket {
        int key;
        int value;
    };
    // Hashtable with Poiters from bucket
    Bucket** table;
    // Hashtable capacity
    int capacity;
    // size of table
    int tableSize;
    // Hashing function
    int hash(int);
};
/**
 * Create new hash table with size
 * @param size denotes hashtable max size
 */
HashTable::HashTable(int size) {
    this->table = new Bucket*[size];
    this->capacity = size;
    this->tableSize = 0;
}
/**
 * Get the value of a bucket from hash table with provided key
 * @param key user input key
 * @return value of the target bucket from hash table
 */
int HashTable::get(int key) {
    if (key <= 0) return -1;
    int increment = 0, index;
    do {
        index = hash(key + increment++);
        if (table[index] == nullptr) {
            return -1;
        }
    } while (table[index]->key != key); // collision -> rehashing
    return table[index]->value; // bucket with same key found
}


/**
 * Destruct delete hash from table
 */
HashTable::~HashTable() {
    // for loop to iterate table until capacity is met
    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr)
            delete table[i];
    }
    delete [] table;
}
/**
 * Determine if hashtable contains key
 * @param key search key
 * @return true if key exists or false if not
 */
bool HashTable::contains(int key) {
    return get(key) != -1;
}

/**
 * retrieve table index by hashing key
 * @param key input key
 * @return table index
 */
int HashTable::hash(int key) {
    return key % capacity;
}
/**
 * @return size of hash table
 */
int HashTable::size() {
    return tableSize;
}
/**
 * @return Empty status of hash table
 */
bool HashTable::empty() {
    return tableSize == 0;
}
/**
 * denote bucket with input key and value
 * @param key user input key
 * @param value user input value
 * @return index of new/update bucket or false(-1) if failed
 */
int HashTable::put(int key, int value) {
    // if table is at capacity return false
    if (tableSize == capacity) return -1;
    // if key is less than zero return false
    if (key <= 0) return -1;
    int counter = 0;
    int index;
    // do while
    // do:  loop to hash the keys and check table slot at hashed key index
    // creates new bucket in empty slots

    do {
        index = hash(key + counter++);
        if (table[index] == nullptr) {
            Bucket *bucket = new Bucket;
            bucket->key = key;
            bucket->value = value;
            table[index] = bucket;
            // increment table size.
            tableSize++;
            return index;
        }
    } while (table[index]->key != key);
    table[index]->value = value;
    return index;
}


#endif //LAB6_HASHTABLE_H
