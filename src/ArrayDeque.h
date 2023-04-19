#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <cstddef> // std::size_t
#include <ostream> // std::ostream
// Ajoutez si nécessaire d'autres inclusions de librairies

template < class T >
class ArrayDeque {
public:
   using value_type = T;
   using reference = T&;
   using const_reference = const T&;
   using pointer = T*;
   using size_type = std::size_t;

   ArrayDeque(size_type _capacite = 0) : debut(0),
                                         taille(0),
                                         capacite(_capacite),
                                         buffer(nullptr) {
      if (capacite)
         buffer = reinterpret_cast<pointer> (
                 ::operator new(capacite * sizeof(value_type)));
   }

   // Placez ici les méthodes publiques nécessaires pour passer le codecheck

private:
   pointer buffer;
   size_type capacite;
   size_type debut;
   size_type taille;

   // Placez ici les méthodes privées qui permettent de rendre votre code plus clair
};

template <typename T> inline
std::ostream& operator<<(std::ostream& s,
                         const ArrayDeque<T>& v) {
   s << "(" << v.size() << "/" << v.capacity() << ") : ";
   if (not v.empty())
      s << v.front() << " -> " << v.back() << " : ";
   s << "[";
   for (int i = 0; i < v.size(); ++i) {
      s << v[i];
      if (i != v.size() - 1)
         s << ", ";
   }
   s << "]";
   return s;
}

#endif /* ArrayDeque_hpp */
