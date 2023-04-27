#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <cstddef> // std::size_t
#include <ostream> // std::ostream
// Ajoutez si nécessaire d'autres inclusions de librairies
#include <memory>

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

   size_type i_physique(size_type i_logique) const {
      return (debut + i_logique + capacite) % capacite;
   }

   reference operator[](size_type i) {
      return buffer[i_physique(i)];
   }

   const_reference operator[](size_type i) const {
      return buffer[i_physique(i)];
   }

   ArrayDeque& operator=(const ArrayDeque& other) {
      capacite = other.capacite;

      for (; taille < other.taille; ++taille) {
         new(buffer + taille) value_type(other[taille]);
      }
   }

   ArrayDeque(const ArrayDeque& other) : ArrayDeque(other.capacite){
      for (; taille < other.taille; ++taille) {
         new(buffer + taille) value_type(other[taille]);
      }
   }

   void push_front(value_type i) {
      debut = i_physique(-1);
      new(buffer + debut) value_type(i);
      ++taille;
   }

   void push_back(value_type i) {
      new(buffer + i_physique(taille)) value_type (i);
      ++taille;
   }

   void pop_front() {
      std::destroy_at(&buffer[i_physique(0)]);
      ++debut;
      --taille;
   }

   void pop_back() {
      if(taille != 0){
         std::destroy_at(&buffer[i_physique(taille - 1)]);
         --taille;
      }
   }

   reference front() const {
      return buffer[debut];
   }

   reference back() const {
      return buffer[i_physique(taille - 1)];
   }

   reference  back() {
      return *(buffer + i_physique(taille - 1));
   }

   void swap(ArrayDeque& other) {
      std::swap(capacite,other.capacite);
      std::swap(taille,other.taille);
      std::swap(buffer,other.buffer);
      std::swap(debut,other.debut);
   }

   bool empty() const {
      return !taille;
   }

   size_type size() const noexcept {
      return taille;
   }
   size_type capacity() const noexcept {
      return capacite;
   }

   void shrink_to_fit() {

   }

   ~ArrayDeque() {
      for (size_type i = 0; i < taille; ++i) {
         std::destroy_at(&buffer[i_physique(i)]);
      }
      if (buffer) {
         ::operator delete(buffer);
      }
   }


private:
   pointer buffer;
   size_type capacite;
   size_type debut;
   size_type taille;


   // Placez ici les méthodes privées qui permettent de rendre votre code plus claiar





};
/*
template <typename T> inline
std::ostream& operator<<(std::ostream& s,
                         const ArrayDeque<T>& v) {
   s << "(" << v.size() << "/" << v.capacity() << ") : ";
   if (not v.empty())
      s << v.front() << " -> " << v.back() << " : ";
   s << "[";
   for (int i = 0; i < v.size(); ++i) {
      s << *(v + i);
      if (i != v.size() - 1)
         s << ", ";
   }
   s << "]";
   return s;
}*/

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
