/* 
 * File:   diccionario.h
 * Author: Esther
 *
 * Created on 2 de diciembre de 2020, 19:34
 */

#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

// --------------------------- Creación del Stuct --------------------------- //

template <typename T, typename U>
struct data {
    T clave;
    list<U> info_asoci;
};

template <typename T, typename U>
bool operator<(const data<T, U>& d1, const data <T, U>& d2) {
    if (d1.clave < d2.clave)
        return true;
    return false;
}

// -------------------------- DECLARACIÓN DEL TDA --------------------------- //


template <typename T, typename U>
class Diccionario {
private:
    list<data<T, U> > datos;

    void Copiar(const Diccionario<T, U>& Dicc) {
        datos.assign(Dicc.datos.begin(), Dicc.datos.end());
    }

    void Borrar() {
        this->datos.erase(datos.begin(), datos.end());
    }

public:
    typedef typename list<data<T,U>>::iterator iterator;
    typedef typename list<data<T,U>>::const_iterator const_iterator;

    /**
     * @brief Inicializa la lista de datos del diccionario
     */
    Diccionario() : datos(list<data<T, U> >()) {
        
    }

    /**
     * @brief Constructor de copia.
     * @param Dicc El diccionario a copiar.
     */
    Diccionario(const Diccionario& Dicc) {
        Copiar(Dicc);
    }

    /**
     * @brief Destructor de la clase
     */
    ~Diccionario() {
        Borrar();
    }

    /**
     * @brief Operador de copia
     * @param Dicc El diccionario a copiar.
     * @return El diccionario modificado tras la copia.
     */
    Diccionario<T, U>& operator=(const Diccionario<T, U>& Dicc) {
        if (this != &Dicc) {
            Borrar();
            Copiar(Dicc);
        }
        return *this;
    }

    /**
     * @brief Consulta si la clave está en el Diccionario. Si no lo está, devuelve la posición en la que debería estar. Si está, devuelve su posición en el Diccionario.
     * @param p La clave a buscar.
     * @param it_out El iterador de salida
     * @return @retval true si se ha encontrado la clave @retval false si no.
     */
    bool Esta_Clave(const T& p, iterator& it_out) {

        if (size() > 0) {                                                       // Si hay datos
            iterator it;                            // Declaramos el iterador                

            for (it = datos.begin(); it != datos.end(); it++) {                 // Mientras haya elementos por recorrer
                if (p == (*it).clave) {                                         // Si lo encontramos
                    it_out = it;                                                // Guardamos la posición en la que está la clave
                    return true;
                } else if ((*it).clave > p) {                                   // Como está ordenado, nos hemos pasado
                    it_out = it;                                                // Donde debería estar la clave
                    return false;
                }
            }

        } else {
            it_out = datos.end();
            return false;
        }
    }

    /**
     * @brief Añade una clave y su información al Diccionario (en orden)
     * @param clave La clave a insertar
     * @param info Una lista de información a añadir
     */
    void Insertar(const T& clave, const list<U>& info) {
        iterator it;
        if (!Esta_Clave(clave, it)) {
            data<T, U> p;
            p.clave = clave;
            p.info_asoci = info;
            datos.insert(it, p);
        }

        datos.sort();                                                           // Para ordenar el diccionario
    }

    /**
     * @brief Añade un significado a la clave dada.
     * @param s La información que se quiere añadir.
     * @param p La clave a la que le añadiremos la información.
     */
    void AddSignificado_Palabra(const U& s, const T& p) {
        iterator it;
        if (Esta_Clave(p, it)) { // Si está la clave
            (*it).info_asoci.insert((*it).info_asoci.end(), s);
        }
    }
    
    /**
     * @biref Consultor de la información asociada de una clave dada.
     * @param p Una clave.
     * @return Si existe la clave, la información asociada de la misma. Si no, devuelve una lista vacía.
     */
    list<U> getInfo_Asoc(const T& p) {
        iterator it;
        if (!Esta_Clave(p, it)) {
            return list<U>();
        } else {
            return (*it).info_asoci;
        }
    }

    /**
     * @brief Consultor del tamaño del diccionario
     * @return El tamaño del diccionario
     */
    inline int size()const {
        return datos.size();
    }

// ------------------------- FUNCIONES AUXILIARES --------------------------- //

    /*Operator >>. El formato de la entrada es:
         numero de claves en la primera linea
         clave-iésima retorno de carro
         numero de informaciones asociadas en la siguiente linea
         y en cada linea obviamente la informacion asociada
     */
    
    // Este es el operador que yo había hecho para el diccionario, pero es muy difícil no especializarlo para strings
    /*template <typename sT, typename sU>
    friend istream& operator>>(istream& is, Diccionario<sT, sU>& Dicc) {
        int numClaves = 0,
                numInfos = 0;

        typename list<data<sT, sU> >::iterator it;
        sT clave;
        list<sU> info;
        sU entrada;

        is >> numClaves;

        while (numClaves != 0) {
            is >> clave >> numInfos;

            while (numInfos != 0) {
                is >> entrada; // Obtenemos una entrada
                info.push_back(entrada); // Insertamos la entrada en la lista de información
                numInfos--;
            }

            Dicc.Insertar(clave, info); // Insertamos la clave y su info en el Diccionario
            numClaves--;
        }

        return is;
    }*/
    
    /**
     * @brief Operador de entrada
     * @param is Input stream
     * @param D El diccionario
     * @return is Input stream
     */
    template <typename sT, typename sU>
    friend istream &operator>>(istream &is, Diccionario<sT, sU> &D) {        
        int np;
        is >> np;
        is.ignore(); // quitamos \n

        Diccionario<sT, sU> Daux;
        for (int i = 0; i < np; ++i) {
          T clave;

          getline(is, clave);

          int ns;
          is >> ns;
          is.ignore(); // quitamos \n

          list<U> laux;
          for (int j = 0; j < ns; ++j) {
            sU s;
            getline(is, s);

            laux.insert(laux.end(), s);
          }

          Daux.Insertar(clave, laux);
        }

        D = Daux;

        return is;
    }
    
    /**
     * @brief Operador de salida
     * @param is Output stream
     * @param D El diccionario
     * @return is Output stream
     */
    template <typename sT, typename sU>
    friend ostream &operator<<(ostream &out, const Diccionario<sT, sU> &d) {
        const_iterator i; 
        
        for (i = d.cbegin(); i != d.cend(); ++i) {
          out << (*i).clave << ":\n";

          for (typename list<sU>::const_iterator j = (*i).info_asoci.begin(); j != (*i).info_asoci.end(); ++j)
            out << '\t' << *j << '\n';

          out << endl;
        }

        return out;
    }

    /*Operator<<. Obsérvese el uso de 2 tipos diferentes de iteradores. Uno sobre
    listas de listas y otro sobre listas
     */
    /*template <typename sT, typename sU>
    friend ostream& operator<<(ostream& os, const Diccionario<sT, sU>& Dicc) {
        typename list<data<sT, sU> >::iterator it;

        for (it = Dicc.datos.begin(); it < Dicc.size(); it++) {
            os << Dicc.imprimirEntrada((*it).clave);
        }

        return os;
    }*/


// -------------------------- FUNCIONES AÑADIDAS ---------------------------- //
    
    /**
     * @brief Método que imprime por la salida estándar una clave del diccionario y su info asociada
     * @param clave La clave que se quiere obtener
     */
    void imprimirEntrada(const T& clave) {
        iterator it;
        typename list<U>::iterator i;

        if (Esta_Clave(clave, it)) {

            list<U> info = (*it).info_asoci;                                    // Obtenemos la lista de la información asociada y la copiamos
            cout << (*it).clave << endl;
            for(i = info.begin(); i != info.end(); i++){
                cout <<"\t" << *i << endl;
            }
        }
    }

    /**
     * @brief Método que permite fusionar dos diccionarios
     * @param d El diccionario con el que se fusiona
     */
    void merge(Diccionario<T, U> &d){
        iterator it;
        for(it = d.begin(); it != d.end(); it++){
            Insertar((*it).clave, (*it).info_asoci);
        }
    }

    /**
     * @brief Método para insertar una nueva clave en el diccionario (sin info asociada)
     * @param clave La clave a insertar
     */
    void InsertarClave(const T& clave) {
        iterator it;
        if (!Esta_Clave(clave, it)) {
            data<T, U> p;
            p.clave = clave;
            p.info_asoci = list<U>();
            datos.insert(it, p);
        }

        datos.sort();                                                           // Para ordenar el diccionario
    }
    
    /**
     * @brief Iterador constante
     * @return Iterador constante al inicio de datos
     */
    const_iterator cbegin() const {
        return datos.cbegin();
    }

    /**
     * @brief Iterador constante
     * @return Iterador constante al final de datos
     */
    const_iterator cend() const {
        return datos.cend();
    }

    /**
     * @brief Iterador 
     * @return Iterador al inicio de datos
     */
    iterator begin() {
        return datos.begin();
    }
    
    /**
     * @brief Iterador 
     * @return Iterador al final de datos
     */
    iterator end() {
        return datos.end();
    }
};


#endif




