#include "diccionario.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  Diccionario<string, string> uno;                                                                                      // Crea un diccionario

  assert(uno.begin() == uno.end());                                                                                     // Comprobar iteradores para diccionario vacío

  fstream input_data("datos/data.txt", fstream::in);                                                                          
  input_data >> uno;                                                                                                    // Guarda los datos en el diccionario

  cout << "\n///////// Primera salida de diccionario 1 /////////" << endl;
  cout << uno << endl;
  
  Diccionario<string, string> dos(uno);                                                                                 // Crea un segundo diccionario
  
  uno.AddSignificado_Palabra("f. Dicho grave y sucinto que encierra doctrina o moralidad", "Sentencia");

  string keyfront = uno.getInfo_Asoc("Sentencia").front();  
  assert(keyfront == "f. Frase o dicho que implica un juicio,una enseñanza.");                                          // Ver si se ha recibido el input bien
  
  string keyend = uno.getInfo_Asoc("Sentencia").back();
  assert(keyend == "f. Dicho grave y sucinto que encierra doctrina o moralidad");                                       // Ver si se ha añadido bien

  cout << "\n///////// Segunda salida de diccionario 1 /////////" << endl;
  cout << uno << endl;
  
  assert(uno.getInfo_Asoc("Sentencia").front() == dos.getInfo_Asoc("Sentencia").front());                               // Si son distintos, explota
  assert(uno.getInfo_Asoc("Sentencia").back() != dos.getInfo_Asoc("Sentencia").back());                                 // Si son iguales, explota
  
  uno = uno;
  assert(uno.getInfo_Asoc("Sentencia").front() == "f. Frase o dicho que implica un juicio,una enseñanza.");             // Si son iguales, explota

// ---------------------- Probar funciones añadidas ------------------------- //
  cout << "\n///////// Prueba 1 /////////" << endl;
  uno.imprimirEntrada("Sentencia");
  
  Diccionario<string,string> prueba;
  prueba.InsertarClave("Prueba Insertar Clave");
  prueba.AddSignificado_Palabra("Esta acepción es sólo de prueba", "Prueba Insertar Clave");
  prueba.AddSignificado_Palabra("Me gustaría poner cosas graciosas pero estoy cansada", "Prueba Insertar Clave");

  uno.merge(prueba);
  
  cout << "\n///////// Combinación de diccionarios /////////" << endl;
  cout << uno << endl;
  
// ---------------------------------- Fin ----------------------------------- //
  
  Diccionario<string, string> tres;                                                                                     // Crea un nuevo diccionario
  assert(tres.cbegin() == tres.cend());                                                                                 // Comprobar iteradores para diccionario vacío
    
  uno = tres;                                                                                                           // Copia el diccionario vacio en el Diccionario uno
  assert(uno.begin() == uno.end());
  assert(dos.begin() != dos.end());

  cout << "OK" << endl;

  return 0;
}
