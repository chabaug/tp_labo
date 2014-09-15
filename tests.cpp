// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "mini_test.h"
#include "arturo.h"


template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }

/*
 * Crea una mesa de int vacia y no agrega elementos
 
void check_crear_mesa_vacia() {
  Arturo<int> mesa;

  ASSERT_EQ(mesa.esVacia(), true);

  ASSERT_EQ(mesa.tamanio(), 0);
}
*/

/*
 * Crea un Arturo de Arturos.

void check_arturo_de_arturo(){
	Arturo<string> mesa1;
	Arturo<string> mesa2;		
	
	Arturo< Arturo<string> > dobleMesa;
	
	dobleMesa.sentarArturo(mesa1);

	mesa2.sentarArturo("ARTURO");

	dobleMesa.incorporarCaballero(mesa2);

	ASSERT(dobleMesa.caballeroActual() == mesa1);
}

*/


int main() {
//  RUN_TEST(check_crear_mesa_vacia);
//  RUN_TEST(check_arturo_de_arturo); 
	Arturo<string> mesa1;
	cout << mesa1.tamanio() << endl;
	mesa1.sentarArturo("Arturo");
	cout << mesa1.tamanio() << endl;
  return 0;
}

