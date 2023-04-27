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

   size_type i_physique(size_type i_logique) const {
      return (debut + i_logique + capacite) % capacite;
   }

   reference operator[](size_type i) {
//      return buffer[i_physique(i)];
      return *(buffer + i_physique(i));
   }

   value_type operator[](size_type i) const {
//      return buffer[i_physique(i)];
      return *(buffer + i_physique(i));
   }

   void push_front(value_type i) {
      size_type temp = capacite -1;
     /* if(debut){
//         --debut;
         temp = debut - 1;
      }
      else{
//         debut = capacite - 1;
         temp = capacite - 1;
      }*/
     //size_type temp = debut - 1;
//      size_type temp = i_physique(debut);
      new((void*)(&buffer[temp])) value_type{i};
      debut = temp;
      ++taille;
   }

   void push_back(value_type i) {
      new((void*)(&buffer[taille])) value_type{i};
      ++taille;
   }

   void pop_front() {

      /*
       * méthode supprimer_au_début()
          si taille == 0, alerter
         détruire data[0]
         début ← i_physique(1)

       */



      delete (pointer)buffer[0];
      ++debut;


   }

   void pop_back() {

      /*si taille == 0
      alerter tableau vide
      détruire data[taille - 1]
      taille ← taille - 1*/

      if(taille != 0){


         delete (pointer)buffer[taille-1];
         --taille;
      }

   }

   reference front() const {
      return buffer[debut];
   }

   reference back() const {
//      cout << "back " << buffer[debut + taille -1] << endl;
//      cout << "debut : " << debut << "  taille  :" << taille << endl;
      return buffer[taille - 1];
   }

   void swap(ArrayDeque& other) {

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
