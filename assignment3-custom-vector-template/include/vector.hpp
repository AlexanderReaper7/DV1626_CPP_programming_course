template <typename T>
class Vector
{
    public:
    Vector()	/* Konstruerar vektorn */
    {

    }
    ~Vector()	/* Förstör vektorn */ 
    {

    }
    Vector(const Vector&)	/* Konstruerar vektorn som en kopia av ett annat vektorobjekt */
    {
        
    }
    Vector(Vector&&)	/* Konstruerar vektorn genom att ta över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    {

    }
    Vector& operator=(const Vector&)	/* Vektorn blir en kopia av ett annat vektorobjekt */
    {


    }
    Vector& operator=(Vector&&)	/* Vektorn tar över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    {

    }
    int size() const	/* Returnerar antalet element i vektorn */ 
    {

    }
    int capacity() const	/* Returnerar det totala antalet element som vektorn kan hantera i nuläget */
    {

    }
    bool empty() const	/* Returnerar true om vektorn är tom */
    {

    }
    T& operator[](int) const	/* Returnerar ett specifikt element på givet index */
    {

    }
    T& at(int) const	/* Returnerar ett specifikt element på givet index */
    {

    }
    T& front() const	/* Returnerar första elementet */
    {

    }
    T& back() const	/* Returnerar sista elementet */
    {

    }
    const T* data() const	/* Returnerar en konstantpekare till den underliggande arrayen */
    {

    }
    void clear()	/* Tömmer vektorn på element */
    {

    }
    void insert(int, const T&)	/* Placerar ett nytt element på specifikt index */
    {

    }
    void erase(int)	/* Tar bort ett element från specifikt index */
    {

    }
    void push_back(const T&)	/* Placerar ett nytt element i slutet av vektorn */
    {

    }
    void pop_back()	/* Tar bort det sista elementet i vektorn */
    {

    }
    private:

};
    template <typename T>
    Vector<T>::Vector()	/* Konstruerar vektorn */
    {

    }
    template <typename T>
    Vector<T>::~Vector()	/* Förstör vektorn */ 
    {

    }
    template <typename T>
    Vector<T>::Vector(const Vector&)	/* Konstruerar vektorn som en kopia av ett annat vektorobjekt */
    {
        
    }
    template <typename T>
    Vector<T>::Vector(Vector&&)	/* Konstruerar vektorn genom att ta över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    {

    }
    template <typename T> 
    Vector<T>& Vector<T>::operator=(const Vector& vec)	/* Vektorn blir en kopia av ett annat vektorobjekt */
    {


    }
    template <typename T> 
    Vector<T>& Vector<T>::operator=(Vector&& vec)	/* Vektorn tar över innehållet från ett annat vektorobjekt. Det andra vektorobjektet förväntas vara tom efter denna denna funktion. */
    {

    }
    template <typename T> 
    int Vector<T>::size() const	/* Returnerar antalet element i vektorn */ 
    {

    }
    template <typename T> 
    int Vector<T>::capacity() const	/* Returnerar det totala antalet element som vektorn kan hantera i nuläget */
    {

    }
    template <typename T> 
    bool Vector<T>::empty() const	/* Returnerar true om vektorn är tom */
    {

    }
    template <typename T> 
    T& Vector<T>::operator[](int) const	/* Returnerar ett specifikt element på givet index */
    {

    }
    template <typename T> 
    T& Vector<T>::at(int) const	/* Returnerar ett specifikt element på givet index */
    {

    }
    template <typename T> 
    T& Vector<T>::front() const	/* Returnerar första elementet */
    {

    }
    template <typename T> 
    T& Vector<T>::back() const	/* Returnerar sista elementet */
    {

    }
    template <typename T> 
    const T* Vector<T>::data() const	/* Returnerar en konstantpekare till den underliggande arrayen */
    {

    }
    template <typename T> 
    void Vector<T>::clear()	/* Tömmer vektorn på element */
    {

    }
    template <typename T> 
    void Vector<T>::insert(int, const T&)	/* Placerar ett nytt element på specifikt index */
    {

    }
    template <typename T> 
    void Vector<T>::erase(int)	/* Tar bort ett element från specifikt index */
    {

    }
    template <typename T> 
    void Vector<T>::push_back(const T&)	/* Placerar ett nytt element i slutet av vektorn */
    {

    }
    template <typename T> 
    void Vector<T>::pop_back()	/* Tar bort det sista elementet i vektorn */
    {

    }
