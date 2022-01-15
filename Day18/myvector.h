template<typename T>
class MyVector {
private:
    T* mData; // this is the actual data (or array)
    int mSize; // Size is how much data.  Capacity is how much memory.
    int mCapacity; // not always same as mSize, usually much larger than mSize.
    T mUndefined;// Lots of STL functions say that doing something naughty gets "undefined behavior".
public:
    MyVector(): mData(nullptr), mSize(0), mCapacity(0){}

    MyVector(T* t, int sz){ // creates a vector of sz elements
        mSize = sz;
        mCapacity = sz * 2;
        mData = new T[sz];

        for(int i = 0; i < sz; i++){
            mData[i] = t[i];
        }
    }

    ~MyVector(){
        delete[] mData;
    }

    MyVector(const MyVector<T>& other){
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData = new T[other.mSize];
        
        for(int i = 0; i < other.mSize; i++){
            mData[i] = other.mData[i];
        }
    }    

    MyVector(MyVector<T>&& other){
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData = new T[other.mSize];
        
        for(int i = 0; i < other.mSize; i++){
            mData[i] = other.mData[i];
        }
        other.mSize = 0;
        other.mCapacity = 0;
        other.mData = nullptr;
    }

    MyVector& operator=(const MyVector<T>& other){
        if(this == &other){
        return *this;
        }

        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData = other.mData;

        return *this;
    }

    MyVector& operator=(MyVector<T>&& other){
        if(this == &other){
            return *this;
        }

        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData = other.mData;

        other.mSize = 0;
        other.mCapacity = 0;
        other.mData = nullptr;

        return *this;     
    }

    bool operator==(const MyVector<T>& other){
        if(mData == other.mData && mSize == other.mSize){
            return true;
        }
        else{
            return false;
            }
    }

    T& operator[](int offset){
        if(offset > mSize){ // ensures that input cannot be larger than mSize/size of array
            return mUndefined;
        }
        return mData[offset];
    }

    void push_back(const T& t){
        if(mSize >= mCapacity){
            reserve(mCapacity * 2); // reserves double the the size of mCapacity
        }
        mData[mSize] = t;
        mSize++;
    }

    void pop_back(){
        if(mSize >= 0){
            mSize--;
            mData[mSize] = mUndefined;
        }
    }

    T& at(int offset){
         if(offset > mSize){
            return mUndefined;
        }
        return mData[offset];
    }

    void clear(){
        mSize = 0;
        mCapacity = 0;
        delete[] mData;

        mData = new T[mSize];
    }
    int size() const{
        return mSize;
    }

    void reserve(int tCount){ // use an algorithm to increase capacity as required
        mCapacity = tCount; 
        
        // if mCapacity is 0, set to 1
        if(mCapacity == 0){
            mCapacity = 1;
            mData = new T[mCapacity];
            return;
        }

        T* tempData = new T[mCapacity];
        for(int i = 0; i < mSize; i++){
            tempData[i] = mData[i];
        }
        delete [] mData;
        mData = tempData;
    }
    
    int capacity() const{
        return mCapacity;
    }
    
    // iterator
    class iterator {
        friend MyVector;
        MyVector* myvec;
        int current; // offset 
    public:
        iterator(MyVector* myvec, int offset): myvec(myvec), current(offset) {}
        void operator++() {
            current++;
        }

        void operator--() {
            current--;
        }

        bool operator==(const iterator& other){
            if(myvec == other.myvec && current == other.current){
                return true;
            }
            else{
                return false;
            }
        }

        // I'm not sure if it's better to flip the true/false returns or
        // use != instead of ==
        bool operator!=(const iterator& other){
            if(myvec == other.myvec && current == other.current){
                return false;
            }
            else{
                return true;
            }
        }

        T& operator*(){
            return this->mData[current];
        }
    };

    iterator begin() const {
        return iterator(this, 0);}

    iterator end() const {
        return iterator(this, mSize);}
};