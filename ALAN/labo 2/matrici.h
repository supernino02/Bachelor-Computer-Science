#include <iostream>
#include <iomanip>
#include <math.h>
#define DIM_VALUE 10

using namespace std;
typedef float tipo_valori;

struct matrice{
  string nome;
  unsigned int righe;
  unsigned int colonne;
  tipo_valori *valori;
};

typedef matrice sistema;
typedef matrice riga;
typedef matrice colonna;
typedef colonna vettore;

bool isVettore (matrice mat);
bool isSistema (matrice mat);
bool isRiga(riga r);
bool isColonna(colonna c);

bool dimensioni_uguali(matrice a,matrice b);
void controlloRiga (riga mat);
void controlloColonna (colonna mat);

matrice cambia_nome(matrice mat,string nome);

matrice crea_matrice(string nome,unsigned int righe, unsigned int colonne);
matrice crea_matrice(unsigned int righe, unsigned int colonne);
matrice crea_copia_matrice(matrice mat);

matrice identita(unsigned int dim);
matrice identita(string nome, unsigned int dim);

riga crea_riga_vuota(unsigned int colonne);
riga crea_riga_vuota(string nome,unsigned int colonne);
riga estrai_riga(matrice mat, unsigned int i);

colonna crea_colonna_vuota(string nome,unsigned int righe);
colonna crea_colonna_vuota(unsigned int righe);
colonna crea_colonna_vuota(string nome,unsigned int righe,tipo_valori val);
colonna estrai_colonna(matrice mat, unsigned int j);

matrice riempi_matrice_cin (matrice mat);
matrice riempi_matrice_array (matrice mat, vector<tipo_valori> vettore);
matrice inserisci_valore (matrice mat, unsigned int riga, unsigned int colonna, tipo_valori x);

matrice crea_sistema(string nome, matrice a, matrice b);
matrice copia_matrice_in(matrice dest, matrice sorg,unsigned int offset_riga,unsigned int offset_colonna);

matrice stampa_matrice (matrice mat);
matrice stampa_sistema (matrice mat);
matrice stampa_vettore (matrice mat);

matrice stampa_matrice (matrice mat,unsigned int n);
matrice stampa_sistema (matrice mat,unsigned int n);
matrice stampa_vettore (matrice mat,unsigned int n);

tipo_valori* ptr_at(matrice mat, unsigned int riga, unsigned int colonna);
tipo_valori at(matrice mat, unsigned int riga, unsigned int colonna);

matrice somma_matriciale(matrice a, matrice b);
matrice prodotto(matrice mat,tipo_valori val);
matrice prodotto(matrice a,matrice b);
matrice trasposta(matrice mat);
tipo_valori riga_x_colonna(riga a, colonna b);
tipo_valori riga_x_colonna(matrice mat, unsigned int i, unsigned int j);

matrice inverti_righe(matrice mat,unsigned int r1, unsigned int r2);
matrice moltiplica_riga_delta(matrice mat,unsigned int r1, tipo_valori delta);
matrice somma_delta_righe(matrice mat,riga r1, riga r2,tipo_valori delta);

matrice crea_triangolare(matrice sistema);
matrice crea_triangolare(string nome,matrice sistema);

matrice riduci_totalmente(matrice mat);
matrice riduci_totalmente(string nome,matrice mat);

matrice sostituzione_indietro(matrice sistema);
matrice sostituzione_indietro(string nome,matrice sistema);

matrice crea_inversa(matrice mat);

//altro
tipo_valori factorial (unsigned int n);
matrice crea_matrice_pascal(string nome,unsigned int n);
matrice crea_matrice_tridiagonal(string nome,unsigned int n);
tipo_valori normaInf (matrice mat);
matrice calcola_soluzioni(matrice A);
matrice calcola_soluzioni_preturbate(matrice A);
