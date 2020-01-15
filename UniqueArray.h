#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

template <class Element, class Compare = std::equal_to<Element>>
class UniqueArray {
private:
    Element **array; // array that holds pointers to elements
    const unsigned int size; // array maximun size, doesn't change during run time
public:

    UniqueArray(unsigned int size);
    UniqueArray(const UniqueArray& other);
    ~UniqueArray();
    UniqueArray& operator=(const UniqueArray&) = delete;
    unsigned int insert(const Element& element);
    bool getIndex(const Element& element, unsigned int& index) const;
    const Element* operator[] (const Element& element) const;
    bool remove(const Element& element);
    unsigned int getCount() const;
    unsigned int getSize() const;

    class Filter {
    public:
        virtual bool operator() (const Element&) const = 0;
    };

    class ForEach {
    public:
        virtual void operator() (Element&, const) const =0;
    };

    UniqueArray filter(const Filter& f) const;
    UniqueArray forEach(const ForEach& f) const;
    class UniqueArrayIsFullException{};
    
};




#include "UniqueArrayImp.h"


#endif //MTMPARKINGLOT_UNIQUEARRAY_H
