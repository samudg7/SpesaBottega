#ifndef CONTAINER_H
#define CONTAINER_H


//template di un array dinamico
template <class T>                    //contenitore di tipo T
class Container{
private:
    T* dynamicArray;
    unsigned int size;
    unsigned int capacity;
    void reserve();                   //funzione che crea un nuovo array dinamico con una doppia capacità

public:
    //classe annidata
    class iterator{
        friend class Container<T>;    //dichiarazione di amicizia della classe Container
    private:
        T* ptr;
        iterator(T*);

    public:
        //operatori
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        T& operator* ();
        T* operator-> ();
        iterator& operator++();
        iterator& operator--();
        iterator& operator+(unsigned int);
        iterator& operator-(unsigned int);
    };

    //classe annidata
    class const_iterator{
        friend class Container<T>;     //dichiarazione di amicizia della classe Container
    private:
        const T* c_ptr;
        const_iterator(T*);

    public:
        //operatori
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
        const T& operator*() const;
        const T* operator->() const;
        const_iterator& operator++();
        const_iterator& operator--();
        const_iterator &operator+(unsigned int);
        const_iterator &operator-(unsigned int);
    };

    Container(unsigned int=3);                          //costruttore a 1 parametro
    Container(const T&, unsigned int=3);                //costruttore a 2 parametri
    Container(const Container<T>&);                     //costruttore di copia
    ~Container();                                       //distruttore

    //operatori
    Container<T>& operator=(const Container<T> &);
    T& operator[] (unsigned int);
    bool operator== (const Container<T>&) const;

    unsigned int getSize() const;
    unsigned int getCapacity() const;
    void clear();                                       //funzione che elimina un array dinamico e ne crea uno nuovo
    void push_back(const T&);                           //funzione che aggiunge in coda un elemento (utilizza reserve nel caso di capacity < size)
    void erase(unsigned int=0);                         //funzione che elimina un elemento in un dato indice
    void erase(T);                                      //funzione che elimina un elemento passato come parametro
    T& at(unsigned int);                                //funzione che ritorna un elemento data la posizione dell'indice

    //iteratori
    iterator begin() const;
    iterator end() const;

    //iteratori costanti
    const_iterator cbegin() const;
    const_iterator cend() const;
};





//compilazione per inclusione, implementazione

template <class T>
Container<T>::Container(unsigned int s) : dynamicArray(new T[s]), size(0), capacity(s) {}

template <class T>
Container<T>::Container(const T& c, unsigned int s): dynamicArray(new T[s]), size(0), capacity(s) {
    for(int i=0; i<capacity; ++i)
        dynamicArray[i]=c;
}

template <class T>
Container<T>::Container(const Container<T>& c): dynamicArray(new T[c.capacity]), size(c.size), capacity(c.capacity) {
    for(unsigned int i=0; i<size; ++i)
        dynamicArray[i]=c.dynamicArray[i];
}

template <class T>
Container<T>::~Container<T>() {
    if(dynamicArray)
        delete[] dynamicArray;
}

template <class T>
Container<T>& Container<T>::operator=(const Container<T>& c){
    if(this!= &c) {
        delete[] dynamicArray;
        size=c.size;
        capacity=c.capacity;
        dynamicArray=new T[capacity];
        for(unsigned int i=0; i<size; ++i)
            dynamicArray[i]=c.dynamicArray[i];
    }
    return *this;
}

template <class T>
T& Container<T>::operator[](unsigned int i){return dynamicArray[i];}

template <class T>
bool Container<T>::operator==(const Container<T>& c) const {
    bool t = (c.size == size && c.capacity == capacity);
    for (auto itx= cbegin(), ity= c.cbegin(); itx!=cend() && t; ++itx, ++ity) {
        if(*itx!=*ity)
            t=false;
    }
    return t;
}

template <class T>
unsigned int Container<T>::getSize() const {return size;}

template <class T>
unsigned int Container<T>::getCapacity()const {return capacity;}

template <class T>
void Container<T>::clear(){
    delete [] dynamicArray;
    dynamicArray=new T[3];
    size=0;
    capacity=3;
}

template <class T>
void Container<T>::reserve(){
    unsigned int doubleCapacity=capacity*2;
    T* doubleDynamicArray=new T[doubleCapacity];

    for(unsigned int i=0; i<size; ++i){
        doubleDynamicArray[i]= dynamicArray[i];
    }

    capacity=doubleCapacity;
    delete [] dynamicArray;
    dynamicArray=doubleDynamicArray;
}

template <class T>
void Container<T>::push_back(const T& c){
    if (!(capacity<size))
        reserve();

    dynamicArray[size++]=c;
}

template <class T>
void Container<T>::erase(unsigned int t){
    for(unsigned int i=t; i<size-1; ++i )
        dynamicArray[i]= dynamicArray[i+1];

    size--;
}

template <class T>
void Container<T>::erase(T c){
    unsigned int i=0;
    for(auto it=begin(); it!=end(); ++it, ++i){
        if((*it)==c){
            erase(i);
            return;
        }
    }
}

template <class T>
T& Container<T>::at(unsigned int i){return dynamicArray[i];}





//iteratori
template <class T>
typename Container<T>::iterator Container<T>::begin() const {return iterator(dynamicArray);}

template <class T>
typename Container<T>::iterator Container<T>::end() const {return iterator(dynamicArray+(size));}

template <class T>
typename Container<T>::const_iterator Container<T>::cbegin() const {return const_iterator(dynamicArray);}

template <class T>
typename Container<T>::const_iterator Container<T>::cend() const {return const_iterator(dynamicArray+(size));}

template <class T>
Container<T>::iterator::iterator(T* c) : ptr(c) {}

template <class T>
bool Container<T>::iterator::operator!=(const iterator& it) const {return ptr!=it.ptr;}

template <class T>
bool Container<T>::iterator::operator==(const iterator& it) const {return ptr==it.ptr;}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator++(){
    if(ptr)
        ptr++;
    return *this;
}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator--(){
    if(ptr)
        ptr--;
    return *this;
}

template <class T>
T& Container<T>::iterator::operator*() {return *ptr;}

template <class T>
T* Container<T>::iterator::operator->() {return ptr;}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator+(unsigned int i){
    if(ptr)
        ptr=ptr+i;
    return *this;
}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator-(unsigned int i){
    if(ptr)
        ptr=ptr-i;
    return *this;
}



//iteratori costanti
template <class T>
Container<T>::const_iterator::const_iterator(T* c) : c_ptr(c){}

template <class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& cit) const {return c_ptr!=cit.c_ptr;}

template <class T>
bool Container<T>::const_iterator::operator==(const const_iterator& cit) const {return c_ptr==cit.c_ptr;}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++() {
    if(c_ptr)
        c_ptr++;
    return *this;
}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--() {
    if(c_ptr)
        c_ptr--;
    return *this;
}

template <class T>
const T& Container<T>::const_iterator::operator*() const {return *c_ptr;}

template <class T>
const T* Container<T>::const_iterator::operator->() const {return c_ptr;}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator+(unsigned int i){
    if(c_ptr)
        c_ptr=c_ptr+i;
    return *this;
}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator-(unsigned int i){
    if(c_ptr)
        c_ptr=c_ptr-i;
    return *this;
}

#endif // CONTAINER_H
