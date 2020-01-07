//
// Created by user on 07/01/2020.
//

#ifndef HW3_UNIQUEARRAYIMP_H
#define HW3_UNIQUEARRAYIMP_H


#define NO_FREE_INDEX -1

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) : size(size), array(new Element*[size]) {
    for(int i=0 ; i<size ; i++){
        array[i] = nullptr;
    }
}
template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other) : array(new Element*[other.size]), size(other.size) {
    for(int i=0 ; i < size; i++) {
        if(other.array[i] == nullptr) array[i] = nullptr;
        array[i] = new Element(*(other.array[i]));
        *(array[i]) = *(other.array[i]);
    }
}
template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
    for(int i=0; i<size; i++) {
        delete array[i];
    }
}
template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element) {
    int freeIndex = NO_FREE_INDEX;
    for(int currentIndex = 0; currentIndex < size; currentIndex++) {
        if(array[currentIndex] == nullptr) freeIndex = currentIndex;
        else if(Compare(), *(array[currentIndex]) == element) return currentIndex;
    }
    if(freeIndex == NO_FREE_INDEX) throw UniqueArrayIsFullException();
    array[freeIndex] = new Element(element);
    return freeIndex;
}
template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element, unsigned int& index) const {
    for(int currentIndex =0; currentIndex < size; currentIndex++) {
        if(Compare(), *(array[currentIndex]) == element) {
            index = currentIndex;
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

#endif //HW3_UNIQUEARRAYIMP_H
