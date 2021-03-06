#ifndef ARTURO_H_
#define ARTURO_H_

#include <iostream>
#include <cassert>
using namespace std;
/* 
 * IMPORTANTE!
 * Se puede asumir que el tipo T tiene constructor por copia y operator == y operator <<
 * No se puede asumir que el tipo T tenga operator =
 */
template<typename T>
class Arturo {

  public:

	/*
	 * Crea una mesa redonda nueva sin caballeros.
	 */	
	Arturo();

	/*
	 * Una vez copiados, ambos Arturos deben ser independientes, 
	 * es decir, cuando se borre uno no debe borrar la otra.
	 */	
	Arturo(const Arturo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~Arturo();

	/*
	* Arturo se sienta siempre primero.
	* 
	* PRE: La mesa esta vacía.
	* POST: Arturo está hablando y es el único en la mesa.
	*/
	void sentarArturo(const T& a);

	/*
	 * Agrega un nuevo caballero a la mesa. El nuevo caballero se sentará
	 * a la derecha de Arturo. No se pueden agregar caballeros repetidos.
	 *
	 * PRE: Arturo esta sentado en la mesa y el nuevo caballero c no está sentado aún
	 * POST: El caballero c se sienta a la derecha de Arturo.
	 */
	void incorporarCaballero(const T& c);
	
	/*
	 * Elimina de la mesa al caballero pasado por parámetro. En caso de borrar al 
	 * caballeroActual, pasará a ser el actual que esté sentado a su derecha.
	 * Si se expulsa al caballero interrumpido por Arturo, Arturo sigue hablando
	 * como si nunca hubiera interrumpido, es decir, el próximo es el de la
	 * derecha de Arturo y el anterior es el de la izquierda de Arturo.
	 *
	 * IMPORTANTE: Sólo se puede borrar a Arturo, si es el único sentado en la mesa.
	 * 
     * PRE: c puede ser Arturo sólo si la mesa tiene tamaño 1
     * POST: El caballero c no está más sentado en la mesa. 
	 */
	void expulsarCaballero(const T& c);
	
    /*
	 * Devuelve al caballero que está hablando en este momento.
	 *
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	const T& caballeroActual() const;
	
	/*
	 * Cambia el turno del caballero actual, al de su derecha. Si Arturo
	 * interrumpió, el turno pasa al de la derecha del interrumpido.
	 * El resultado no tiene interrumpido.
	 * 
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	void proximoCaballero();

	/*
	 * Cambia el turno del caballero actual, al de su izquierda. Si Arturo
	 * interrumpió, el turno pasa al de la izquierda del interrumpido. 
	 * Esta función puede ser llamada varias veces seguidas.
	 * El resultado no tiene interrumpido.
	 * 
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	void caballeroAnterior();

	/*
	* Arturo puede elegir que es su turno de hablar en cualquier momento e 
	* interrumpir al que está hablando. Arturo termina de hablar por interrupción
	* cuando se pasa al proximoCaballero() o al caballeroAnterior().
	*
	* PRE: Si Arturo está hablando, no se puede interumpir a sí mismo.
	*/
	void hablaArturo();

    /*
	 * Indica si Arturo está sentado en la mesa. 
	 */
	bool arturoPresente() const;
	
	/*
	* Arturo quiere separar un conflicto y por lo tanto cambia su posición y
	* se sienta a la derecha del caballero pasado como parámetro.
	* Tanto como el que está hablando como el interrumpido siguen siendo los mismos.
	* Ejemplos:
	*  cambiarDeLugar(c1) de la mesa: [Arturo(c0), c1, c2] deja la mesa: [Arturo(c0), c2, c1]
	*  cambiarDeLugar(c1) de la mesa: [c1, c2, Arturo(c0)] deja la mesa: [c1, Arturo(c0), c2]
	*  cambiarDeLugar(c2) de la mesa: [c1, c2, Arturo(c0), c3] deja la mesa: [c1, c2, Arturo(c0), c3]
	*
	* PRE: La mesa tiene al menos tamaño 3
	* POST: Arturo está sentado a la derecha de c
	*/
	void cambioDeLugar(const T& c);

	/*
	 * Dice si la mesa tiene o no caballeros sentados.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de caballeros en la mesa.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las mesas son iguales.
	 * Dos mesas son iguales cuando todos sus caballeros son iguales,
	 * están sentados en las mismas posiciones, y además tanto Arturo,
	 * como el que está hablando, como el interrumpido (si hubiera) son iguales.
	 */
	bool operator==(const Arturo<T>&) const;	
	
	/*
	 * Debe mostrar la mesa por el ostream os (y retornar el mismo).
	 * Mesa vacia: []
	 * Mesa con caballero c0 como Arturo: [ARTURO(c0)]
	 * Mesa con 2 caballeros (Arturo está hablando): [ARTURO(c0), c1]
	 * Mesa con 3 caballeros (Arturo está hablando): [ARTURO(c0), c1, c2]
	 * Mesa con 3 caballeros (c1 está hablando): [c1, c2, ARTURO(c0)]
	 * Mesa con 3 caballeros (c1 fue interrumpido): [ARTURO(c0),*c1,c2]
	 */
	ostream& mostrarArturo(ostream& os) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	Arturo<T>& operator=(const Arturo<T>& otra) {
		assert(false);
		return *this;
	}
	
	T& iesimo(int i);
	void eliminar(int i);
	
	struct Nodo {
		Nodo(const T& c) 
			: caballero(c), sig(NULL), ant(NULL), esArturo(false) {
		}
			 
		T caballero;
		Nodo* sig;
		Nodo* ant;
    bool esArturo;
	};
	
	int len;
	Nodo* prim;
	Nodo* fin;
};

template<class T>
ostream& operator<<(ostream& out, const Arturo<T>& a) {
	return a.mostrarArturo(out);
}

// Implementación a hacer por los alumnos.

template <typename T>
Arturo<T>::Arturo() 
	: len(0), prim(NULL), fin(NULL) {
}

template <typename T>
Arturo<T>::Arturo(const Arturo<T>& otra) 
	: len(0), prim(NULL), fin(NULL) {
	for (int i=0; i<otra.tamanio(); i++) {
		incorporarCaballero(otra.iesimo(i));
	}
}

template <typename T>
T& Arturo<T>::iesimo(int i) {
	assert( i < len );
	int idx = 0;
	Nodo* actual = prim;
	while( idx < i ) {
		idx++;
		actual = actual->sig;
	}
	return actual->dato;
}

template <typename T>
int Arturo<T>::tamanio() const {
	return len;
}

template <typename T>
Arturo<T>::~Arturo() {
	while( prim != NULL ) {
		eliminar(0);
	}
}


template <typename T>
void Arturo<T>::eliminar(int i) {
	assert( i < len );
	int idx = 0;
	Nodo* anterior = NULL;
	Nodo* actual = prim;
	while( idx < i ) {
		idx++;
		anterior = actual;
		actual = actual->sig;
	}

	if ( i==0 ) {
		prim = actual->sig;
	} else {
		anterior->sig = actual->sig;
	}

	len--;
	delete actual;
}

template <typename T>
void Arturo<T>::sentarArturo(const T& a) {
	ASSERT(len == 0);
	Nodo* nuevo = new Nodo(a);
	nuevo->ant = nuevo;
	nuevo->sig = nuevo;
	len++;
	prim = nuevo;
	fin = nuevo;
}

template <typename T>
bool Arturo<T>::arturoPresente() const {
  esta = false;
  Nodo* actual = prim;
  int i = 0;
  while (i < len && esta) {
    if (actual->esArturo) {
      esta = true;
    }
    else {
      actual == actual->sig;
    }
    i++;
  }
  return esta;
}


template <typename T>
void Arturo<T>::incorporarCaballero(const T& c) {
  ASSERT(this->arturoPresente());
//  ASSERT( c no es ningun caballero de this);
  len++;
  Nodo* nuevo = new Nodo(c);
        
}
#endif //ARTURO_H_
