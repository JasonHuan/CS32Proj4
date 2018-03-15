//
//  MyHash.cpp
//  Project4
//
//  Created by Jason Huan on 3/15/18.
//  Copyright © 2018 Jason. All rights reserved.
//

#include "MyHash.h"

template<typename KeyType>
unsigned int hash(const KeyType& k);

template<typename KeyType, typename ValueType>
MyHash<KeyType,ValueType>::MyHash(double maxLoadFactor){
    m_array = new Node*[100];
    m_capacity = 100;
    if(maxLoadFactor <= 0){
        m_maxLoadFactor = 0.5;
    } else if (maxLoadFactor > 2){
        m_maxLoadFactor = 2;
    } else {
        m_maxLoadFactor = maxLoadFactor;
    }
    
    for(int i = 0; i < 100; i++){
        m_array[i] = nullptr;
    }
}

template<typename KeyType, typename ValueType>
MyHash<KeyType,ValueType>::~MyHash(){
    delete [] m_array;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType,ValueType>::reset(){
    delete [] m_array;
    m_array = new Node*[100];
    m_capacity = 100;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType,ValueType>::associate(const KeyType& key, const ValueType& value){
    int h = hash(key);
    
    Node* ptr = m_array[h]; //get bucket index
    Node* trailer = nullptr;
    if(ptr != nullptr){
        do{ //while bucket isn't empty
            trailer = ptr;
            if(ptr->m_key != key){ //if key doesn't match, move on
                ptr = ptr->m_next;
            } else { //else, replace key and return (so it won't add anything else)
                ptr->m_value = value;
                return;
            }
        }while(ptr != nullptr);
    }
    
    //at this point, the key doesn't exist in the map
    //AND, ptr refers to a nullptr at the end of the bucket
    
    if( (1 + m_count)/m_capacity > m_maxLoadFactor){ //if adding new key would exceed max load factor, resize
        Node* oldArray = m_array; //keep a pointer of the array
        m_array = new Node[m_capacity*2];
        
        Node* rptr;
        for(int i = 0; i < m_capacity; i++){ //go through all of the buckets
            rptr = *(oldArray+i);
            while(rptr != nullptr){ //while bucket isn't empty
                associate(rptr->m_key, rptr->m_value); //reassociate key-value pair
            }
        }
     
        delete oldArray; //clean up old array
        m_capacity *= 2; //put this down here so that you don't go through the size of the new array, only the old one
    }
    
    //now, add the new key and update
    ptr = new Node(key, value);
    trailer->m_next = ptr;
    m_count++;
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType,ValueType>::getNumItems() const{
    return m_count;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType,ValueType>::getLoadFactor() const{
    return (m_count/m_capacity);
}

// for a map that can't be modified, return a pointer to const ValueType
template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType,ValueType>::find(const KeyType& key) const{
    
}
