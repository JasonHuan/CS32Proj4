// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
private:
    double m_maxLoadFactor;
    struct Node{
        Node(KeyType Key, ValueType Value){
            m_key = Key;
            m_value = Value;
        }
        
        ~Node(){ //either i'm a genius or i'm an idiot
            if(m_next != nullptr)
                delete m_next;
        }
        
        KeyType m_key;
        ValueType m_value;
        Node* m_next;
    };
    Node* m_array;
    int m_count;
    double m_capacity;
};
