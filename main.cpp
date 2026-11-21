#include <iostream>
#include <cstdlib>
#include "grafo.h"
#include "conjunto.h"
#include <queue>
#include <sstream>
#include <map>


using namespace std;

//Ejercicio 1
template <typename T>
T verticeMaxCoste(const Grafo<T, float>& G)
{
    float costeMax = 0;
    Conjunto<Vertice<T>> cv = G.vertices();
    Conjunto<Arista<T, float>> ca = G.aristas();

    T v, vMax;

    typedef map<T, float> Diccionario;
    typedef pair<T, float> Par;
    Diccionario d;

    for (int i = 0; i < G.numVertices(); i++) {
        v = cv.quitar().getObj();
        Par p(v, 0);
        d.insert(p);
    }

    while (!ca.esVacio()) {
        Arista<T, float> a = ca.quitar();
        typename Diccionario::iterator id = d.find(a.getOrigen());
        id->second += a.getEtiqueta();
    }

    for (typename Diccionario::iterator idic = d.begin(); idic != d.end(); idic++) {
        if (costeMax < idic->second) {
            costeMax = idic->second;
            vMax = idic->first;
        }
    }

    return vMax;
}


//Ejercicio 2
template <typename T, typename U>
void inaccesibles(const Grafo<T, U>& G)
{
    Conjunto<Vertice<T>> cv = G.vertices();
    Conjunto<Arista<T, U>> ca = G.aristas();
    T v;
    typedef map<T, bool> Diccionario;
    Diccionario d;

    while (!cv.esVacio()) {
        v = cv.quitar().getObj();
        d[v] = false;
    }

    while (!ca.esVacio()) {
        d[ca.quitar().getDestino()] = true;
    }

    for (typename Diccionario::iterator i = d.begin(); i != d.end(); i++) {
        if (i->second == false) {
            cout << " " << i->first;
        }
    }
}


// Ejercicio 3
template <typename T, typename U>
bool caminoEntreDos(const Grafo<T, U>& G, const T& vo, const T& vd)
{
    queue<T> c;
    Conjunto<Vertice<T>> cv = G.vertices(), adys;
    Conjunto<Arista<T, U>> ca = G.aristas();
    T v;
    typedef map<T, bool> Diccionario;
    Diccionario d;
    bool existe = false;

    while (!cv.esVacio()) {
        d[cv.quitar().getObj()] = false;
    }

    c.push(vo);
    while (!c.empty() && !existe) {
        adys = G.adyacentes(c.front());
        while(!adys.esVacio() && !existe) {
            v = adys.quitar().getObj();
            if (!d[v]) {
                if (v == vd) {
                    existe = true;
                }
                else {
                    c.push(v);
                }

                d[v] = true;
            }
        }
        c.pop();
    }

    return existe;
}


//Ejercicio 4
template <typename T>
void caminosAcotados(const Grafo<T, float>& G, const T& u, float maxCoste)
{
    stringstream ss;
    ss << u;

    caminosAcotados(G,u,maxCoste,0,ss.str());
}


template <typename T>
void caminosAcotados(const Grafo<T, float>& G, const T& u, float maxCoste, float coste, string s)
{
    Conjunto <Arista<T, float>> ca = G.aristas();
    stringstream ss;

    while (!ca.esVacio()) {
        Arista<T, float> a = ca.quitar();
        if (coste + a.getEtiqueta() <= maxCoste && a.getOrigen() == u) {
            ss << s << " - " << a.getDestino();
            cout << ss.str() << endl;

            caminosAcotados(G,a.getDestino(),maxCoste,coste+a.getEtiqueta(),ss.str());

            ss.str("");
        }
    }
}

//Ejercicio 5
template <typename T, typename U>
T outConectado(const Grafo<T, U>& G)
{
    Conjunto<Vertice<T>> cv = G.vertices();
    Conjunto<Arista<T, float>> ca = G.aristas();
    typedef map<T, int> Diccionario;
    Diccionario d;
    T v;

    while (!cv.esVacio()) {
        d[cv.quitar().getObj()] = false;
    }

    while (!ca.esVacio()) {
        Arista<T, U> a = ca.quitar();
        d[a.getDestino()]--;
        d[a.getOrigen()]++;
    }

    typename Diccionario::iterator i = d.begin();
    while (i !=d.end()) {
        if (i->second > 0) {
            return i->first;
        } else {
            i++;
        }
    }
}


//Ejercicio 6
template <typename T, typename U>
void recorrido_profundidad(const Grafo<T, U>& G, const T& v)
{
    Conjunto<Vertice<T>> cv = G.vertices();
    stringstream ss;
    typedef map<T, bool> Diccionario;
    Diccionario d;

    ss << v;

    while(!cv.esVacio()) {
        d[cv.quitar().getObj()] = false;
    }

    recorrido_profundidad(G, v, ss.str(), d);

    cout << ss.str();
}

template <typename T, typename U>
void recorrido_profundidad(const Grafo<T, U>& G, const T& v, string s, map<T, bool>& d)
{
    Conjunto<Arista<T,U>> ca = G.aristas();
    Conjunto<Vertice<T>> adys = G.adyacentes(v), cv = G.vertices();
    T va;
    stringstream ss;

    d[v] = true;

    while(!adys.esVacio()){
        va = adys.quitar().getObj();
        if(!d[va]){
            ss << s << " - " << va;
            s = ss.str();

            recorrido_profundidad(G,va,s,d);

            ss.str("");
        }
    }
}

//********************************************************************//
//Construir una funcion que permita ver por pantalla el camino entre dos vertices
template<typename T>
void verCamino(const Grafo<string, T>& G, string v1, string v2)
{
    typedef map<string, bool> Diccionario;
    Diccionario d;
    Conjunto<Vertice<string>> cv = G.vertices();
    string s;
}

//********************************************************************//
int main()
{
    Grafo<int, float> G(7);
    for (int i = 1; i <= 7; i++) G.insertarVertice(i);
    G.insertarArista(2, 1, 4);
    G.insertarArista(1, 3, 3);
    G.insertarArista(1, 4, 2);
    G.insertarArista(1, 6, 1);
    G.insertarArista(6, 4, 5);
    G.insertarArista(4, 7, 3);
    G.insertarArista(5, 1, 6);

    Grafo<string, float> H(7);
    H.insertarVertice("Huelva"); H.insertarVertice("Lepe"); H.insertarVertice("Niebla");
    H.insertarVertice("Mazagon"); H.insertarVertice("Almonte"); H.insertarVertice("Aljaraque");
    H.insertarVertice("Matalasca as");
    H.insertarArista("Lepe", "Huelva", 4);
    H.insertarArista("Huelva", "Niebla", 3);
    H.insertarArista("Huelva", "Mazagon", 2);
    H.insertarArista("Huelva", "Aljaraque", 1);
    H.insertarArista("Mazagon", "Almonte", 3);
    H.insertarArista("Mazagon", "Matalasca as", 4);
    H.insertarArista("Aljaraque", "Mazagon", 5);
    H.insertarArista("Almonte", "Huelva", 6);


    cout << " Vertice de maximo coste en G: " << verticeMaxCoste(G) << endl;
    cout << " Vertice de maximo coste en H: " << verticeMaxCoste(H) << endl;

    cout << endl << " Vertices inaccesibles en G: ";
    inaccesibles(G);

    cout << endl << " Camino entre Dos en H de Lepe a Almonte: ";
    cout << (caminoEntreDos(H, string("Lepe"), string("Almonte")) ? " SI " : " NO ") << endl;
    cout << endl << " Camino entre Dos en H de Aljaraque a Lepe: ";
    cout << (caminoEntreDos(H, string("Aljaraque"), string("Lepe")) ? " SI " : " NO ") << endl;

    cout << endl << " Caminos acotados en G a coste 9 desde el vertice 2:" << endl;
    caminosAcotados(G, 2, 9);

    cout << endl << endl << " Vertice outConectado en G: " << outConectado(G);
    cout << endl << " Vertice outConectado en H: " << outConectado(H);

    cout << endl << endl << " Recorrido en profundidad de H desde el vertice Huelva:  ";
    recorrido_profundidad(H, string("Huelva"));
    cout << endl << endl;


    system("PAUSE");
    return EXIT_SUCCESS;
}
