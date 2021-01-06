#ifndef customvec123
#define customvec123
#include <iostream>
#include <string.h>

template <typename T>
class Vector
{
    public:
    Vector()	/* Konstruerar vektorn */
    {
        m_size = 0;
        m_capacity = 1;
        m_elements = new T[1];
    };
    ~Vector()	/* Förstör vektorn */ 
    {
        delete[ ] m_elements;
    };
    Vector(const Vector& vec)	/* Konstruerar vektorn som en kopia av ett annat vektorobjekt */
    {
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;
        m_elements = new T[m_size];  
        for (int i = 0; i < m_size; i++) 
        {
            m_elements[i] = vec.m_elements[i];
        }
    };
    Vector(Vector&& vec)	/* Konstruerar vektorn genom att ta över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    {
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;
        m_elements = vec.m_elements;
        vec.m_elements = new T[m_capacity];
        vec.m_size = 0;
    };
    Vector& operator=(const Vector& vec)	/* Vektorn blir en kopia av ett annat vektorobjekt */
    {
        if (vec == *this) return *this;
        delete[ ] m_elements;
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;
        m_elements = new T[m_capacity];  
        for (int i = 0; i < m_size; i++) 
        {
            m_elements[i] = vec.m_elements[i];
        }
        return *this;
    };
    Vector& operator=(Vector&& vec)	/* Vektorn tar över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    {
        if (vec == *this) return *this;
        delete[ ] m_elements;
        m_size = vec.m_size;
        m_capacity = vec.m_capacity;
        m_elements = vec.m_elements;
        vec.m_elements = new T[m_size];
        vec.m_size = 0;
        return *this;
    };
    bool operator==(const Vector& vec) const
    {
        if (vec.m_size != m_size) return false;
        if (vec.m_capacity != m_capacity) return false;
        if (vec.m_elements != m_elements) return false;
        return true;
    };
    int size() const	/* Returnerar antalet element i vektorn */ 
    {
        return m_size;
    };
    int capacity() const	/* Returnerar det totala antalet element som vektorn kan hantera i nuläget */
    {
        return m_capacity;
    };
    bool empty() const	/* Returnerar true om vektorn är tom */
    {
        return m_size == 0;
    };
    T& operator[](int index) const	/* Returnerar ett specifikt element på givet index */
    {
        if (index < 0 || index > m_size-1) throw "index out of range";
        return m_elements[index];
    };
    T& at(int index) const	/* Returnerar ett specifikt element på givet index */
    {
        if (index < 0 || index > m_size-1) throw "index out of range";
        return m_elements[index];
    };
    T& front() const	/* Returnerar första elementet */
    {
        if (m_size < 1) throw "Vector is empty";    
        return m_elements[0];
    };
    T& back() const	/* Returnerar sista elementet */
    {
        if (m_size < 1) throw "Vector is empty";
        return m_elements[m_size-1];
    };
    const T* data() const	/* Returnerar en konstantpekare till den underliggande arrayen */
    {
        return m_elements;
    };
    void clear()	/* Tömmer vektorn på element */
    {
        m_size = 0;
    };
    void insert(int index, const T& element)	/* Placerar ett nytt element på specifikt index */
    {
        if (index < 0 || index > m_size) return;/* throw "index out of range"; */ // TODO: check if you can insert at end
        if (m_capacity < m_size+1) allocate();
        for (int i = m_size; i > index; i--) /* shift elements right */
        {
            m_elements[i] = m_elements[i-1];
        }
        m_elements[index] = element;
        m_size++;
    };
    void erase(int index)	/* Tar bort ett element från specifikt index */
    {
        if (index < 0 || index > m_size-1) 
        {
            // throw "index out of range";
            return;
        }
        for (int i = 0; i < m_size - index - 1; i++) /* shift elements left */
        {
            m_elements[index+i] = m_elements[index+i+1];
        }
        --m_size;
    };
    void push_back(const T& element)	/* Placerar ett nytt element i slutet av vektorn */
    {
        insert(m_size, element);
    };
    void pop_back()	/* Tar bort det sista elementet i vektorn */
    {
        if (m_size > 0) m_size--;/* throw "cannot remove from empty vector"; */
        
    };
    void allocate() /* Allokerar plats för  mängd element */
    {
        int new_capacity = (int)(m_capacity * 2.0f);
        // std::cout << "old: " << m_size << " new " << new_size << "\n";
        T* temp = new T[new_capacity];
        // for (int i = 0; i < m_size; i++)
        // {
        //     temp[i] = m_elements[i];
        // }
        std::copy(m_elements, m_elements + m_capacity, temp);
        m_capacity = new_capacity;
        delete[ ] m_elements;
        m_elements = temp;
    };
    private:
    T* m_elements;	/* En rå pekare till den dynamiska arrayen som sparar alla element i arrayen. */
    int m_size;	/* Antalet element som finns i vektorn */
    int m_capacity;	/* Totala antalet element som vektorn kan hantera. */
};
    // template <typename T>
    // Vector<T>::Vector()	/* Konstruerar vektorn */
    // template <typename T>
    // Vector<T>::~Vector()	/* Förstör vektorn */ 
    // template <typename T>
    // Vector<T>::Vector(const Vector<T>& vec)	/* Konstruerar vektorn som en kopia av ett annat vektorobjekt */
    // template <typename T>
    // Vector<T>::Vector(Vector<T>&& vec)	/* Konstruerar vektorn genom att ta över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    // template <typename T> 
    // Vector<T>& Vector<T>::operator=(const Vector<T>& vec)	/* Vektorn blir en kopia av ett annat vektorobjekt */
    // template <typename T> 
    // Vector<T>& Vector<T>::operator=(Vector<T>&& vec)	/* Vektorn tar över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    // template <typename T> 
    // bool Vector<T>::operator==(const Vector<T>& vec) const
    // template <typename T> 
    // int Vector<T>::size() const	/* Returnerar antalet element i vektorn */ 
    // template <typename T> 
    // int Vector<T>::capacity() const	/* Returnerar det totala antalet element som vektorn kan hantera i nuläget */
    // template <typename T> 
    // bool Vector<T>::empty() const	/* Returnerar true om vektorn är tom */
    // template <typename T> 
    // T& Vector<T>::operator[](int index) const	/* Returnerar ett specifikt element på givet index */
    // template <typename T> 
    // T& Vector<T>::at(int index) const	/* Returnerar ett specifikt element på givet index */
    // template <typename T> 
    // T& Vector<T>::front() const	/* Returnerar första elementet */
    // template <typename T> 
    // T& Vector<T>::back() const	/* Returnerar sista elementet */
    // template <typename T> 
    // const T* Vector<T>::data() const	/* Returnerar en konstantpekare till den underliggande arrayen */
    // template <typename T> 
    // void Vector<T>::clear()	/* Tömmer vektorn på element */
    // template <typename T> 
    // void Vector<T>::insert(int index, const T& element)	/* Placerar ett nytt element på specifikt index */
    // template <typename T> 
    // void Vector<T>::erase(int index)	/* Tar bort ett element från specifikt index */
    // template <typename T> 
    // void Vector<T>::push_back(const T& element)	/* Placerar ett nytt element i slutet av vektorn */
    // template <typename T> 
    // void Vector<T>::pop_back()	/* Tar bort det sista elementet i vektorn */
    // template <typename T> 
    // void Vector<T>::allocate()
#endif
