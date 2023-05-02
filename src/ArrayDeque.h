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

   explicit ArrayDeque(size_type _capacite = 0) : debut(0),
                                         taille(0),
                                         capacite(_capacite),
                                         buffer(nullptr) {
      if (capacite)
         buffer = reinterpret_cast<pointer> (
                 ::operator new(capacite * sizeof(value_type)));
   }

   // Placez ici les méthodes publiques nécessaires pour passer le codecheck

   /**
   * @name            : ArrayDeque
   *
   * @but             : Constructeur par copie
   *
   * @param other     : L'objet à copier
   * @return          : Un objet de type ArrayDeque
   * @throws          : NIL
   */
   ArrayDeque(const ArrayDeque& other) : ArrayDeque(other.capacite){
      for (; taille < other.taille; ++taille) {
         new(buffer + taille) value_type(other[taille]);
      }
   }


   /**
     * @name            : operator[]
     *
     * @but             : opérateur pour accéder à un élément du buffer
     *
     * @param i         : emplacement de l'élément
     * @return          : référence sur l'élément
     * @throws          : NIL
     */
   reference operator[](size_type i) {
      return buffer[i_physique(i)];
   }


   /**
     * @name            : operator[]
     *
     * @but             : opérateur pour accéder à un élément du buffer
     *
     * @param i         : emplacement de l'élément
     * @return          : une référence constante sur l'élément
     * @throws          : NIL
     */
   const_reference operator[](size_type i) const {
      return buffer[i_physique(i)];
   }


   /**
     * @name            : operator=
     *
     * @but             : opérateur d'affectation
     *
     * @param other     : buffer à affecter
     * @return          : référence sur le buffer à retourner
     * @throws          : NIL
     */
   ArrayDeque& operator=(const ArrayDeque& other){
      //Si une affectation sur lui même est faite, il retourne lui même sans faire les opérations
      if (this == &other) {
         return *this;
      }

      ArrayDeque temp(other);
      swap(temp);
      return *this;
   }


   /**
     * @name            : push_front
     *
     * @but             : ajoute un élément au début du buffer
     *
     * @param i         : élément à ajouter
     * @return          : void
     * @throws          : NIL
     */
   void push_front(value_type i) {

      if(capacite <= taille){
         changer_capacite();
      }

      debut = i_physique(-1);
      new(buffer + debut) value_type(i);
      ++taille;
   }


   /**
     * @name            : push_back
     *
     * @but             : ajoute un élément à la fin du buffer
     *
     * @param i         : élément à ajouter
     * @return          : void
     * @throws          : NIL
     */
   void push_back(value_type i) {

      if(capacite <= taille){
         changer_capacite();
      }

      new(buffer + i_physique(taille)) value_type (i);
      ++taille;
   }


    /**
     * @name            : pop_front
     *
     * @but             : supprimer le premier élément
     *
     * @return          : void
     * @throws          : NIL
     */
   void pop_front() {
      std::destroy_at(&buffer[i_physique(0)]);
      ++debut;
      --taille;
   }


   /**
     * @name            : pop_back
     *
     * @but             : supprimer le dernier élément
     *
     * @return          : void
     * @throws          : NIL
     */
   void pop_back() {
      if(taille != 0){
         std::destroy_at(&buffer[i_physique(taille - 1)]);
         --taille;
      }
   }


   /**
     * @name            : front
     *
     * @but             : retourne le premier élément
     *
     * @return          : rertourne une référence sur le premier élément
     * @throws          : NIL
     */
   reference front() const {
      return buffer[i_physique(0)];
   }


   /**
  * @name            : back
  *
  * @but             : retourne le dernier élément
  *
  * @return          : rertourne une référence sur le dernier élément
  * @throws          : NIL
  */
   reference back() const {
      return buffer[i_physique(taille - 1)];
   }


   /**
     * @name            : swap
     *
     * @but             : échanger deux buffers
     *
     * @param other     : buffer avec lequel échanger
     * @return          : void
     * @throws          : NIL
     */
   void swap(ArrayDeque& other) {
      std::swap(capacite,other.capacite);
      std::swap(taille,other.taille);
      std::swap(buffer,other.buffer);
      std::swap(debut,other.debut);
   }


   /**
   * @name            : empty
   *
   * @but             : fonction servant à indiquer si le buffer est vide
   *
   * @return          : bool
   * @throws          : NIL
   */
   bool empty() const {
      return !taille;
   }


   /**
   * @name            : size
   *
   * @but             : fonction servant à indiquer la taille du buffer
   *
   * @return          : size_t
   * @throws          : NIL
   */
   size_type size() const noexcept {
      return taille;
   }


   /**
   * @name            : capacity
   *
   * @but             : fonction servant à indiquer si la capacitee du buffer
   *
   * @return          : size_t
   * @throws          : NIL
   */
   size_type capacity() const noexcept {
      return capacite;
   }


   /**
   * @name            : shrink_to_fit
   *
   * @but             : fonction servant à redimmensionner la taille par rapport à la capicitee
   *
   * @return          : void
   * @throws          : NIL
   */
   void shrink_to_fit() {
      changer_capacite(true);
   }


   /**
   * @name            :  ~ArrayDeque
   *
   * @but             : déstructeur de l'objet ArrayDeque
   *
   * @return          : void
   * @throws          : NIL
   */
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
   size_type capacite{};
   size_type debut{};
   size_type taille{};


   // Placez ici les méthodes privées qui permettent de rendre votre code plus claiar

   /**
     * @name            : changer_capacite
     *
     * @but             : agrandir ou rétrécir la capacité du buffer
     *
     * @param shrink    : booléen qui définit si on rétréci
     * @return          : void
     * @throws          : NIL
     */
   void changer_capacite(bool shrink = false) {
      size_type nouvelleCapacite;
      //Si on veut diminuer la capacite
      if (shrink) {
         nouvelleCapacite = taille;
      }
      //Si on veut augmenter la capacite
      else {
         nouvelleCapacite = capacite == 0 ? 1 : capacite * 2;
      }
      ArrayDeque<value_type> tmp(nouvelleCapacite);
      for (size_type i = 0; i < taille; ++i) {
         new(tmp.buffer + i) value_type(std::move(buffer[i_physique(i)]));
         ++tmp.taille;
      }

      std::swap(buffer, tmp.buffer);
      std::swap(capacite, tmp.capacite);
      std::swap(debut, tmp.debut);
   }


   /**
  * @name            : i_physique
  *
  * @but             : fonction servant à récupérer l'emplacement physique d'un élément dans le buffer
  *
  * @param i_logique : indice logique de l'élément dans le buffer
  * @return          : size_t
  * @throws          : NIL
  */
   size_type i_physique(size_type i_logique) const {
      //Retourne l'emplacement physique d'un élément
      return (debut + i_logique + capacite) % capacite;
   }

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

#endif //ArrayDeque_h