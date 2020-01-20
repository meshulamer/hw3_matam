//
// Created by user on 07/01/2020.
//

#ifndef HW3_UNIQUEARRAYIMP_H
#define HW3_UNIQUEARRAYIMP_H


#define NO_FREE_INDEX -1

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :size(size) {
    array = new Element*[size];
    for(int i=0 ; i<size ; i++){
        array[i] = nullptr;
    }
}
template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other) : array(new Element*[other.size]), size(other.size) {
    for(int i=0 ; i < size; i++) {
        if(other.array[i] == nullptr) array[i] = nullptr;
        else {
            array[i] = new Element(*(other.array[i]));
        }
    }
}
template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
    for(int i=0; i<size; i++) {
        if(array[i] != nullptr) delete array[i];
        array[i] = nullptr;
    }
    delete[] array;
}
template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element) {
    int freeIndex = NO_FREE_INDEX;
    Compare compare;
    for(int currentindex = 0; currentindex < size; currentindex++) {
        if(array[currentindex] == nullptr && (freeIndex == NO_FREE_INDEX)) freeIndex = currentindex;
        else if(compare(*(array[currentindex]), element)) return currentindex;
    }
    if(freeIndex == NO_FREE_INDEX) throw UniqueArrayIsFullException();
    array[freeIndex] = new Element(element);
    return freeIndex;
}
template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element, unsigned int& index) const {
    Compare compare;
    for(int currentindex =0; currentindex < size; currentindex++) {
        if((array[currentindex] != nullptr) && (compare(*(array[currentindex]), element))) {
            index = currentindex;
            return true;
        }
    }
    return false;
}
template <class Element, class Compare>
const Element* UniqueArray<Element, Compare>:: operator[] (const Element& element) const {
    unsigned int index = 0;
    if(!getIndex(element, index)) return nullptr;
    return array[index];
}
template <class Element, class Compare>
Element* UniqueArray<Element,Compare>::operator[] (const unsigned int index) const{
    if(index < 0 || index >=size) return nullptr;
    else return array[index];
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element& element) {
    unsigned int index = 0;
    if(!getIndex(element, index)) return false;
    delete array[index];
    array[index] = nullptr;
    return true;
}
template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    int counter = 0;
    for(int i=0; i<size; i++) {
        if(array[i]!= nullptr) {
            counter++;
        }
    }
    return counter;
}
template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
    return size;
}

template <class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter(const Filter& f) const {
    UniqueArray newarray = UniqueArray(this->size);
    for(int currentindex = 0; currentindex < size ; currentindex++) {
        if((array[currentindex] != nullptr)&&(f(*(array[currentindex])))) {
            newarray.array[currentindex] = new Element(*(array[currentindex]));
        }
        else {
            newarray.array[currentindex] = nullptr;
        }
    }
    return newarray;
}

#endif //HW3_UNIQUEARRAYIMP_H
