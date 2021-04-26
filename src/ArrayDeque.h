#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <ostream>

template < class T >
class ArrayDeque
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using size_type = std::size_t;

private:
    pointer buffer;
    size_type capacite;
    size_type debut;
    size_type taille;

public:
    ArrayDeque(size_type _capacite = 0) : buffer(nullptr), capacite(_capacite), debut(0), taille(0)
    {
        if(capacite)
            buffer = reinterpret_cast<pointer> (
                    ::operator new(capacite * sizeof(value_type)));
    }

    // Completer cette classe générique pour qu'elle passe le codecheck

};

template <typename T> inline
std::ostream& operator<<(std::ostream& s,
                         const ArrayDeque<T>& v)
{
    s << "(" << v.size() << "/" << v.capacity() << ") : ";
    if(not v.empty())
        s << v.front() << " -> " << v.back() << " : ";
    s << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        s << v[i];
        if (i != v.size() - 1)
            s << ", ";
    }
    s << "]";
    return s;
}

#endif /* ArrayDeque_hpp */
