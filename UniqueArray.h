#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

template <class Element, class Compare = std::equal_to<Element>>
/**
* @brief Generic Array that Holds pointers to elements, and allows management of objects
* held within.
* Each element can only be held once. The array Makes sure it doesnt hold duplicate objects by using
* the <Compare> added.
* @Parameters Element to hold, Class Compare - compares
*/
class UniqueArray {
private:
    Element **array; // array that holds pointers to elements
    const unsigned int size; // array maximum size, doesn't change during run time
public:
    /**
    * @brief Builds a UniqueArray object.
    * @Parameters Size of theUniqueArray.
    */
    explicit UniqueArray(unsigned int size);
    /**
    * @brief Copy Constructor for UniqueArray.
    * @Parameters other - a UniqueArray to copy.
    */
    UniqueArray(const UniqueArray& other);
    /**
    * @brief Destructor for UniqueArray.
    */
    ~UniqueArray();
    /**
    * @brief Operator = overloading for UniqueArray object.
    *
    */
    UniqueArray& operator=(const UniqueArray&) = delete;
    /**
    * @brief inserts a new Element to the Array.
    * @Parameters element to Add.
    * @Returns the element's index.
    *|In case the element exists in the array, returns its Index and will not insert it again.|
    */
    unsigned int insert(const Element& element);
    /**
    * @brief Receives an element,returns if it is in the array and inputs its index into a reference.
    * @Parameters Element& to an element, unsigned int& to write the index into.
    * @Returns true and writes its index into the reference if it is in the array,
    *returns false and otherwise and will not change index.
    */
    bool getIndex(const Element& element, unsigned int& index) const;
    /**
    * @brief operator [] overloading.
    * @Parameters Element& of an element.
    * @Returns Element* to the same element in the Array.
    */
    const Element* operator[] (const Element& element) const;
    /**
    * @brief Removes an Object from the array.
    * @Parameters Element& to remove.
    * @Returns true if successfully removed, false if the element is not in the array.
    */
    bool remove(const Element& element);
    /**
    * @brief Returns the total number of elements in the array.
    */
    unsigned int getCount() const;
    /**
    * @brief Returns the total size of the array (number of element pointers it can hold).
    */
    unsigned int getSize() const;
    /**
    * @brief Gets element from a specific index by using index iteration.
    * @Parameters unsigned int index.
    * @Returns the element in the index location, nullptr if the array index is empty
    */
    Element* getPointerByIndex(unsigned int index) const;
    /**
    * @brief operator () overloading for filter function.
    */
    class Filter {
    public:
        virtual bool operator() (const Element&) const = 0;
    };
    /**
    * @brief Creates a new UniqueArray, filtered by a f function that dictates if an element should
    * be in the filtered array or not.
    * @Parameters  class Filter, function f that receives an element and returns true if to add to new array, false
    * otherwise. (view class Filter)
    * @Returns Filtered UniqueArray
    */
    UniqueArray filter(const Filter& f) const;
    /**
    * @brief Exception that is thrown in case UniqueArray is full.
    */
    class UniqueArrayIsFullException{};
    
};




#include "UniqueArrayImp.h"


#endif //MTMPARKINGLOT_UNIQUEARRAY_H
