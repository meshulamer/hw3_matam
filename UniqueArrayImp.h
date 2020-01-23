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
    for(int i = 0; i < size; i++) {
        if(array[i] == nullptr && (freeIndex == NO_FREE_INDEX)) freeIndex = i;
        else if(array[i] == nullptr) continue;
        else if(compare(*(array[i]), element)) return i; //Returns the index of the Element that was requested
    }
    if(freeIndex == NO_FREE_INDEX) throw UniqueArrayIsFullException();
    array[freeIndex] = new Element(element);
    return freeIndex;
}
template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element, unsigned int& index) const {
    Compare compare;
    for(int current_index =0; current_index < size; current_index++) {
        if (array[current_index] != nullptr) {
            if (compare(*(array[current_index]), element)) {
                index = current_index;
                return true;
            }
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
Element* UniqueArray<Element,Compare>::getPointerByIndex(unsigned int index) const{
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
    UniqueArray new_array = UniqueArray(this->size);
    for(int current_index = 0; current_index < size ; current_index++) {
        if((array[current_index] != nullptr)&&(f(*(array[current_index])))) {
            new_array.array[current_index] = new Element(*(array[current_index]));
        }
        else {
            new_array.array[current_index] = nullptr;
        }
    }
    return new_array;
}

#endif //HW3_UNIQUEARRAYIMP_H
