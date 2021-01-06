#ifndef customvec123
#define customvec123
#include <iostream> //DEBUG
//#include <stdio.h>
#include <string.h>

template <class T> class Vector
{
public:
    //==================================================================================================//
    // VECTOR CONSTRUCTORS
    //---------------------

    Vector(int space = 1) // Konstruerar vektorn
    {
        //std::cout << "Constructed!" << std::endl;
        _size = 0;
        _capacity = space;
        _array = new T[_capacity];
    }
    ~Vector() // Förstör vektorn
    { 
        //std::cout << "Destroyed!" << std::endl;
        delete[ ] _array; 
    }

    Vector(const Vector& other) // Konstruerar vektorn som en kopia av ett annat vektorobjekt
    {
        _array = new T[other._capacity];
        _size = other._size;
        _capacity = other._capacity;
        for (int i = 0; i < _size; i++)
        {
            _array[i] = other._array[i];
        }

    }

    Vector(Vector&& other) // Konstruerar vektorn genom att ta över innehållet från ett annat vektorobjekt.
    {
        //std::cout << "Moved!" << std::endl;
        _size = other._size;
        _capacity = other._capacity;
        _array = other._array;
        
        other._size = 0;
         other._array = new T[other._capacity];
    } 

    //==================================================================================================//
    // VECTOR OPERATIONS
    //-------------------

    Vector& operator=(const Vector& other) // Vektorn blir en kopia av ett annat vektorobjekt
    {
        if(_array != other._array)
        {
            _size = other._size;
            _capacity = other._capacity;
            delete[ ] _array;
            _array = new T[_capacity];
            for (int i = 0; i < _size; i++)
            {
                _array[i] = other._array[i];
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) // Vektorn tar över innehållet från ett annat vektorobjekt
    {
        //std::cout << "operator=&&!" << std::endl;
        if(_array != other._array)
        {
            _size = other._size;
            _capacity = other._capacity;
            delete[ ] _array;
            _array = other._array;

            other._size = 0;
            // other._capacity = 1;
            other._array = new T[other._capacity];
        }
        return *this;
    }

    //==================================================================================================//
    // GET VECTOR INFORMATION
    //------------------------

    int size() const // Returnerar antalet element i vektorn
    { 
        //std::cout << "S:" << _size << std::endl;
        return _size; 
    } 
    int capacity() const // Returnerar det totala antalet element som vektorn kan hantera i nuläget
    { 
        //std::cout << "C:" << _capacity << std::endl;
        return _capacity; 
    } 
    bool empty() const // Returnerar true om vektorn är tom
    { 
        //std::cout << "Empty:" << (_size==0) << std::endl;
        return _size == 0; 
    } 

    //==================================================================================================//
    // GET VALUES
    //------------

    T& operator[](int index) const // Returnerar ett specifikt element på givet index
    { 
        if (empty()) {throw "The Vector har no assigned values!";}
        if (index < 0) {throw "The index is out of range!";}
        if (index >= _size) {throw "The index is out of range!";}
        //std::cout << "operator[" << index << "]" << std::endl;
        return _array[index];
    }

    T& at(int index) const // Returnerar ett specifikt element på givet index 
    { 
        if (empty()) {throw "The Vector har no assigned values!";}
        if (index < 0) {throw "The index is out of range!";}
        if (index >= _size) {throw "The index is out of range!";}
        //std::cout << "at[" << index << "]" << std::endl;
        return _array[index]; 
    }

    T& front() const // Returnerar första elementet
    { 
        if (empty()) {throw "The Vector har no assigned values!";}
        //std::cout << "front[0]" << _array[0] << std::endl;
        return _array[0]; 
    } 

    T& back() const // Returnerar sista elementet
    { 
        if (empty()) {throw "The Vector har no assigned values!";}
        //std::cout << "back[" << _size-1 << "]" << std::endl;
        return _array[_size-1]; 
    } 
    
    const T* data() const // Returnerar en konstantpekare till den underliggande arrayen
    { 
        //std::cout << "data:" << _array << std::endl;
        return _array; 
    } 

    //==================================================================================================//
    // MANIPULATE VALUES
    //-------------------

    void clear() // Tömmer vektorn på element
    {
        // delete[ ] _array;
        _size = 0;
        // _array = new T[_capacity];
    }
    void insert(int index, const T& value) // Placerar ett nytt element på specifikt index
    {
        //std::cout << "insert(" << index << ", " << value << ")" << std::endl;
        if (0 <= index && index <= _size)
        {
            if(size() >= capacity())
            {
                kuk();
            }
            for (int i = _size; i > index; i--)
            {
                _array[i] = _array[i-1];
            }
            _array[index] = value;
            ++_size;
        }        
    }
    void erase(int index) // Tar bort ett element från specifikt index
    {
        if (0 <= index && index <= _size)
        {
            // for (int i = index; i < _size; i++)
            // {
            //     _array[i] = _array[i+1];
            // }
                    for (int i = 0; i < _size - index - 1; i++) /* shift elements left */
        {
            // m_elements[index+i] = m_elements[index+i+1];
           _array[index+i] = _array[index+i+1];

        }
            // _array[_size] = 0;
            --_size;
        }
        
    }
    void push_back(const T& value) // Placerar ett nytt element i slutet av vektorn
    {
        //std::cout << "push_back[" << _size+1 << "]:" << value << std::endl;
        if(size() >= capacity())
        {
            kuk();
        }
        _array[_size] = value;
        ++_size;
    }
    void pop_back() // Tar bort det sista elementet i vektorn
    {
        if (!empty())
        {
            // _array[_size] = 0;
            --_size;
        }
        
    }

    void kuk()
    {
       const float capX = 2.0f; // Capacity Multiplier
       //std::cout << "Vector is filled!" << std::endl;
       int kuknisse = (int)(_capacity*capX);
       T* newArray = new T[kuknisse];
       std::copy(_array, _array + std::min(_capacity, kuknisse), newArray);
       _capacity = kuknisse;
       delete[ ] _array;
       _array = newArray;
       //std::cout << "New capacity: " << capacity() << std::endl;
    }

private:
    T* _array;
    int _capacity;
    int _size;
};
#endif