#include <iostream>
#include <iomanip>
#include <string.h>
#include <cmath>
#include <vector>
#include "matrici.h"


// matrice inverti_colonne(matrice a,unsigned int c1, unsigned int c2);
// matrice moltiplica_colonna_delta(matrice a,riga r1, tipo_valori delta);
// matrice sottrai_delta_colonne(matrice a,unsigned int c1, unsigned int c2,tipo_valori delta);


bool isSistema (matrice mat) {
  return mat.nome.find("sistema") != std::string::npos;
}

bool isVettore(matrice mat) {
  return mat.colonne == 1;
}

bool isRiga(riga r) {
  return r.righe == 1;
}

void controlloRiga (riga mat) {
  if (isRiga(mat)) return;
  cerr << "la matrice \"" << mat.nome << "\" non è una riga , ha dimensioni  "<< mat.righe << " x " << mat.colonne << endl;
  exit(-1);
}

bool isColonna(colonna c) {
  return c.colonne == 1;
}

void controlloColonna (colonna mat) {
  if (isColonna(mat)) return;
  cerr << "la matrice \"" << mat.nome << "\" non è una colonna , ha dimensioni  "<< mat.righe << " x " << mat.colonne << endl;
  exit(-1);
}

bool dimensioni_uguali(matrice a,matrice b) {
  return a.righe == b.righe && a.colonne == b.colonne;
}

void controllo_dimensioni_uguali(matrice a,matrice b) {
  if (dimensioni_uguali(a,b)) return;
  cerr << "la matrice \"" << a.nome << "\" ha dimensioni  "<< a.righe << " x " << a.colonne << endl;
  cerr << "la matrice \"" << b.nome << "\" ha dimensioni  "<< b.righe << " x " << b.colonne << endl;
  exit(-1);
}


riga crea_riga_vuota(string nome,unsigned int colonne) {
  matrice mat;
  mat.nome = nome;
  mat.righe = 1;
  mat.colonne = colonne;
  mat.valori = new tipo_valori[colonne];
  for (size_t j = 1; j <= mat.colonne; j++)
    inserisci_valore(mat,1,j,0);
  return mat;
}

riga crea_riga_vuota(unsigned int colonne) {
  return crea_riga_vuota("",colonne);
}

riga estrai_riga(matrice mat, unsigned int i) {
  riga c = crea_riga_vuota(mat.colonne);
  for (size_t j = 1; j <= c.colonne; j++)
    inserisci_valore(c,1,j,at(mat,i,j));
  return c;
}

colonna estrai_colonna(matrice mat, unsigned int j) {
  colonna c = crea_colonna_vuota(mat.righe);
  for (size_t i = 1; i <= c.righe; i++)
    inserisci_valore(c,i,1,at(mat,i,j));
  return c;
}

colonna crea_colonna_vuota(string nome,unsigned int righe) {
  colonna mat;
  mat.nome = nome;
  mat.righe = righe;
  mat.colonne = 1;
  mat.valori = new tipo_valori[righe];
  for (size_t j = 1; j <= mat.righe; j++)
    inserisci_valore(mat,j,1,0);
  return mat;
}

colonna crea_colonna_vuota(unsigned int righe) {
  return crea_colonna_vuota("",righe);
}

colonna crea_colonna_vuota(string nome,unsigned int righe, tipo_valori val) {
  colonna mat = crea_colonna_vuota(nome,righe);
  for (size_t i = 1; i <= mat.righe; i++)
    inserisci_valore(mat,i,1,val);
  return mat;
}

matrice cambia_nome(matrice mat,string nome) {
  mat.nome = nome;
  return mat;
}

matrice crea_copia_matrice(matrice mat) {
  matrice ris = crea_matrice(mat.righe,mat.colonne);
  for (size_t i = 1; i <= mat.righe; i++)
    for (size_t j = 1; j <= mat.colonne; j++)
      inserisci_valore(ris,i,j,at(mat,i,j));
  return ris;
}

//restituisce una matrice vuota nxm
matrice crea_matrice(string nome,unsigned int righe, unsigned int colonne) {
  matrice mat;
  mat.nome = nome;
  mat.righe = righe;
  mat.colonne = colonne;
  mat.valori = new tipo_valori[righe*colonne];
  for (size_t i = 1; i <= mat.righe; i++)
    for (size_t j = 1; j <= mat.colonne; j++)
      inserisci_valore(mat,i,j,0);
  return mat;
}

//restituisce una matrice vuota nxm
matrice crea_matrice(unsigned int righe, unsigned int colonne) {
  return crea_matrice("",righe,colonne);
}

matrice identita(unsigned int dim) {
  return identita("I",dim);
}

matrice identita(string nome,unsigned int dim) {
  matrice mat = crea_matrice(dim,dim);
  for (size_t j = 1; j <= dim; j++)
    inserisci_valore(mat,j,j,1);
  return mat;
}

matrice riempi_matrice_cin (matrice mat) {
  cout << "inserisci valori per la matrice \"" << mat.nome << "\" " << mat.righe << "x" << mat.colonne << endl;
  float val;
  for (size_t i = 1; i <= mat.righe; i++) {
    for (size_t j = 1; j <= mat.colonne; j++) {
      cin >> val;
      inserisci_valore(mat,i,j,val);
    }
  }
  return mat;
}

matrice riempi_matrice_array (matrice mat, vector<tipo_valori> vettore) {
  int k = 0;
  for (size_t i = 1; i <= mat.righe; i++)
    for (size_t j = 1; j <= mat.colonne; j++)
    inserisci_valore(mat,i,j,vettore.at(k++));
  return mat;
}

matrice crea_sistema(string nome, matrice a, matrice b) {
  matrice c = crea_matrice(nome,a.righe,a.colonne+b.colonne);
  copia_matrice_in(c,a,0,0);
  copia_matrice_in(c,b,0,a.colonne);
  return c;
}

//taglia fuori la matrice sorg se non ci sta
matrice copia_matrice_in(matrice dest, matrice sorg,unsigned int offset_riga, unsigned int offset_colonna) {
  for (size_t i = 1; i+offset_riga <= dest.righe && i <= sorg.righe; i++)
    for (size_t j = 1; j+offset_colonna <= dest.colonne  && j <= sorg.colonne; j++)
      inserisci_valore(dest,i+offset_riga,j+offset_colonna,at(sorg,i,j));
  return dest;
}

matrice estrazione(matrice mat,unsigned int righe, unsigned int colonne, unsigned int offset_righe,unsigned int offset_colonne) {
  if (mat.righe < righe + offset_righe || mat.colonne < colonne + offset_colonne) {
    cerr << "estrazione di" << righe << "x" << colonne << " con offset " << offset_righe << "x" << offset_colonne << "impossibile in una matrice " << mat.righe << "x" << mat.colonne << endl;
    exit(-1);
  }
  matrice risultato = crea_matrice(righe,colonne);
  for (unsigned int i = 1; i <= righe; i++) 
    for (unsigned int j = 1; j <= colonne; j++)
      inserisci_valore(risultato,i,j,at(mat,i+offset_righe,j+offset_colonne));
  return risultato;  
}

matrice inserisci_valore (matrice mat, unsigned int riga, unsigned int colonna, tipo_valori x) {
  *ptr_at(mat,riga,colonna) = x;
  return mat;
}

matrice stampa_matrice (matrice mat) {
  return stampa_matrice(mat,DIM_VALUE);
}

matrice stampa_matrice (matrice mat,unsigned int n) {
  if (isSistema(mat)) return stampa_sistema(mat,n);
  if (isVettore(mat)) return stampa_vettore(mat,n);

  cout << "stampa valori della matrice \"" << mat.nome << "\" " << mat.righe << "x" << mat.colonne << endl;
  for (size_t i = 1; i <= mat.righe; i++) {
    for (size_t j = 1; j <= mat.colonne; j++) {
      cout << setw(n) << setfill(' ') << at(mat,i,j);//ogni valore occupa 5 spazi
      cout << " ";
    }
    cout << endl;
  }
  cout << endl;
  return mat;
}

matrice stampa_sistema (matrice mat) {
  return stampa_sistema(mat,DIM_VALUE);
}

matrice stampa_sistema (matrice mat,unsigned int n) {
  cout << "stampa valori del sistema \"" << mat.nome << "\" " << mat.righe << "x" << mat.colonne << endl;
  for (size_t i = 1; i <= mat.righe; i++) {
    for (size_t j = 1; j <= mat.colonne; j++) {
      if (j == mat.colonne) cout << "|";
      cout << setw(n) << setfill(' ') << at(mat,i,j);//ogni valore occupa 5 spazi
      cout << " ";
    }
    cout << endl;
  }
  cout << endl;
  return mat;
}

matrice stampa_vettore (matrice mat) {
  return stampa_vettore(mat,DIM_VALUE);
}

matrice stampa_vettore (matrice mat,unsigned int n) {
  cout << "stampa del vettore \"" << mat.nome << "\" " << mat.righe << "x1" << endl;
  for (int i = 1; i <= mat.righe; i++) cout << setw(n) << setfill(' ') << at(mat,i,1) << endl;
  cout << endl;
  return mat;
}

//i valori partono da 1-1 fino a n-n
tipo_valori* ptr_at(matrice mat, unsigned int riga, unsigned int colonna) {
  if (riga > mat.righe || colonna > mat.colonne) {
    cerr << "valori out of bound per la matrice " << mat.nome << endl;
    cerr << "richiesto: " << riga << ", " << colonna << " in una matrice " << mat.righe << " x " << mat.colonne << endl;
    exit(-1);
  }
  return &(mat.valori[(riga-1)*mat.colonne+(colonna-1)]);
}

//i valori partono da 1-1 fino a n-n
tipo_valori at(matrice mat, unsigned int riga, unsigned int colonna) {
  return *(ptr_at(mat,riga,colonna));
}

//operazioni tra matrici
matrice somma_matriciale(matrice a, matrice b) {
  controllo_dimensioni_uguali(a,b);
  matrice c = crea_matrice(a.righe,a.colonne);
  for (size_t i = 1; i <= a.righe; i++)
    for (size_t j = 1; j <= a.colonne; j++)
      inserisci_valore(c,i,j,at(a,i,j)+at(b,i,j));
  return c;
}

matrice prodotto(matrice mat,tipo_valori val) {
  matrice c = crea_copia_matrice(mat);
  for (size_t i = 1; i <= c.righe; i++)
    for (size_t j = 1; j <= c.colonne; j++)
      inserisci_valore(c,i,j,at(mat,i,j)*val);
  return c;
}

matrice prodotto(matrice a,matrice b) {
  if (a.colonne != b.righe) {
    cerr << "impossibile moltiplicare le matrici \"" << a.nome << "\" e \"" << b.nome << "\"" << endl;
    cerr << "sono di dimensioni" << a.righe << " x " << a.colonne << "," << b.righe << "x" << b.colonne << endl;
    exit(-1);
  }
  matrice c = crea_matrice(a.righe,b.colonne);
  for (size_t i = 1; i <= c.righe; i++)
    for (size_t j = 1; j <= c.colonne; j++)
      inserisci_valore(c,i,j,riga_x_colonna(estrai_riga(a,i),estrai_colonna(b,j)));
  return c;
}

matrice trasposta(matrice mat) {
  matrice ris = crea_matrice(mat.colonne,mat.righe);
  for (size_t i = 1; i <= ris.righe; i++)
    for (size_t j = 1; j <= ris.colonne; j++)
      inserisci_valore(ris,i,j,at(mat,j,i)); 
  return ris;
}

tipo_valori riga_x_colonna(riga a, colonna b) {
  controlloRiga(a);
  controlloColonna(b);
  tipo_valori ris = 0;
  if (a.colonne != b.righe) {
    cerr << "la riga \"" << a.nome << "\" ha dimensioni "<< a.righe << " x " << a.colonne << endl;
    cerr << "la colonna \"" << b.nome << "\" ha dimensioni "<< b.righe << " x " << b.colonne << endl;
    exit(1);
  }
  for (size_t i = 1; i <= a.colonne; i++)
    ris += at(a,1,i)* at(b,i,1);
  return ris;
}

tipo_valori riga_x_colonna(matrice mat, unsigned int i, unsigned int j) {
  tipo_valori ris = 0;
  for (size_t k = 1; i <= mat.righe; k++)
    ris += at(mat,i,k)* at(mat,k,j);
  return ris;
}

//r1<->r2
matrice inverti_righe(matrice mat,unsigned int r1, unsigned int r2) {
  matrice ris = crea_copia_matrice(mat);
  copia_matrice_in(ris,estrai_riga(mat,r1),r2-1,0);
  copia_matrice_in(ris,estrai_riga(mat,r2),r1-1,0);
  return ris;
}

//r1 -> r1*delta
matrice moltiplica_riga_delta(matrice mat, unsigned int r1, tipo_valori delta) {
  matrice ris = crea_copia_matrice(mat);
  return copia_matrice_in(ris,prodotto(estrai_riga(mat,r1),delta),r1-1,0);
}

//r1 -> r1-delta*r2
matrice somma_delta_righe(matrice mat,unsigned int r1, unsigned int r2, tipo_valori delta) {
  matrice ris = crea_copia_matrice(mat);
  //stampa_sistema(estrai_riga(mat,r1));
  //stampa_sistema(prodotto(estrai_riga(mat,r2),delta));
  //cout << endl;
  return copia_matrice_in(ris,somma_matriciale(estrai_riga(mat,r1),prodotto(estrai_riga(mat,r2),delta)),r1-1,0);
}

matrice crea_triangolare(matrice sistema) {
  return crea_triangolare(sistema.nome,sistema);
}

matrice crea_triangolare(string nome,matrice sistema) {  //se non è quadrata non è detto funzioni
  for (size_t j = 1; j < sistema.righe; j++) {
    //mette al primo posto il pivot piu grande
    unsigned int i_riga = j;
    tipo_valori pivot = at(sistema,j,j);
    for (size_t i = j+1; i <= sistema.righe; i++)
      if (at(sistema,i,j) > pivot) {
        i_riga = i;
        pivot = at(sistema,i,j);
      }
    // ho trovato il pivot maggiore,scambio le righe
    if (pivot == 0) {
      cerr << "la matrice non ha soluzioni" << endl;
      exit(-1);
    }
    sistema = inverti_righe(sistema,j,i_riga);

    //lavoro sui pivot
    for (size_t i = j+1; i <= sistema.righe; i++) {
      if (at(sistema,i,j) == 0) continue;//non devo fare nulla è gia a zero
      sistema = somma_delta_righe(sistema,i,j,-at(sistema,i,j)/pivot);
      //cout << i << " " << j << " " << pivot << endl;
    }
  }
  sistema.nome = nome;  
  return sistema;
}

matrice riduci_totalmente(matrice mat) {
  return riduci_totalmente("",mat);
}

matrice riduci_totalmente(string nome, matrice mat) {
  //normalizzo i pivot
  matrice ridotta = crea_copia_matrice(mat);
  for (size_t i = 1; i <= ridotta.righe; i++) ridotta = moltiplica_riga_delta(ridotta,i,1/at(ridotta,i,i));
  //rotto
  for (unsigned int j = 1; j <= ridotta.righe; j++) 
    for (unsigned int i = 1; i < j; i++)
      if (at(ridotta,i,j)) ridotta = somma_delta_righe(ridotta,i,j,-at(ridotta,i,j));
  return ridotta;  
}

matrice sostituzione_indietro(matrice sistema) {
  return sostituzione_indietro("",sistema);
}

matrice sostituzione_indietro(string nome,matrice sistema) {
  vettore x_calcolata = crea_colonna_vuota(sistema.righe);
  for (size_t i = x_calcolata.righe; i >= 1; i--) {
    tipo_valori sommatoria = 0;
    for (size_t j = i; j <= sistema.righe; j++)  {
      sommatoria += at(sistema,i,j)*at(x_calcolata,j,1);
    }
    tipo_valori valore = (at(sistema,i,sistema.colonne)-sommatoria)/at(sistema,i,i);
    inserisci_valore(x_calcolata,i,1,valore);
  }
  x_calcolata.nome = nome;
  return x_calcolata;
}

matrice crea_inversa(matrice mat) {
  matrice accosta = crea_sistema("A | INV",mat,identita("INV",mat.righe));
  matrice ridotta = crea_triangolare(accosta);//arrivo alla ridotta
  matrice tot = riduci_totalmente(ridotta);//trovo I | A-1  
  return estrazione(tot,tot.righe,tot.colonne/2,0,tot.colonne/2);//estraggo
}

//altro

//esercizio 1 punto b
tipo_valori factorial (unsigned int n) {
  return n ? n*factorial(n-1) : 1;
}

matrice crea_matrice_pascal(string nome,unsigned int n) {
  matrice p = crea_matrice(nome,n, n);
  for (int i=1; i<=n; i++)
    for (int j=1; j<=n; j++)
      inserisci_valore (p, i, j, factorial(i+j-2)/(factorial(i-1)*factorial(j-1)));
  return p;
}

//esercizio 1 punto c
matrice crea_matrice_tridiagonal(string nome,unsigned int n) {
  matrice t = crea_matrice(nome,n, n);
  tipo_valori tmp;
  for (int i=1; i<=n; i++) 
    for (int j=1; j<=n; j++) {
      if (i == j) tmp = 2;
      else if (abs(i-j)==1) tmp=-1;
      else tmp = 0;
      inserisci_valore (t, i, j, tmp);
    }
 return t;
}

tipo_valori normaInf (matrice mat) {
  tipo_valori max_val = 0;
  for (size_t i = 1; i <= mat.righe; i++) {
    tipo_valori somma = 0;
    for (size_t j = 1; j <= mat.colonne; j++) 
      somma+= abs(at(mat,i,j));
    max_val = max(max_val,somma);
  }
  return max_val;
}


matrice calcola_soluzioni(matrice A) {
  cout << "-------------------------------------------------------------------------------" << endl;
  matrice x_attesa = crea_colonna_vuota("X_attesa",A.colonne,1);
  vettore B = prodotto(A,x_attesa);
  B.nome = "b";
  sistema sistema = crea_sistema("Ab",A,B);
  //stampa_sistema(sistema);
  matrice tc = crea_triangolare("tc",sistema);
  //stampa_sistema(tc);
  matrice x_calcolata = sostituzione_indietro("x calcolato",tc);
  return x_calcolata;  
}

matrice calcola_soluzioni_perturbate(matrice A) {
  cout << "-------------------------------------------------------------------------------" << endl;
  matrice x_attesa = crea_colonna_vuota("X_attesa",A.colonne,1);
  matrice B = prodotto(A,x_attesa);
  B.nome = "b";
  //creo b
  tipo_valori norma = normaInf(B);
  stampa_matrice(B);
  cout << "norma b: " << norma << endl;
  matrice B_sigma = crea_colonna_vuota(B.righe);
  for (size_t i = 1; i <= B_sigma.righe; i++)
    inserisci_valore(B_sigma,i,1,norma*0.01*pow(-1,i));
  B_sigma.nome = "B sigma";
  stampa_matrice(B_sigma);
  //aggiorno b come b+sigma
  matrice B_perturbato = somma_matriciale(B,B_sigma);
  B_perturbato.nome = "B perturbato";
  stampa_matrice(B_perturbato);

  sistema sistema = crea_sistema("Ab",A,B_perturbato);
  matrice tc = crea_triangolare("tc",sistema);
  //stampa_sistema(tc);

  matrice x_calcolata = sostituzione_indietro("x perturbato calcolato",tc);
  // stampa_matrice(x_calcolata);
  // cout << endl;
  return x_calcolata;
}

int main() {
  std::cout << std::setprecision(4) << std::fixed;
  matrice matrici[4] = {
    riempi_matrice_array(crea_matrice("A1",4,4),vector<tipo_valori>{3,1,-1,0,0,7,-3,0,0,-3,9,-2,0,0,4,-10}),
    riempi_matrice_array(crea_matrice("A2",4,4),vector<tipo_valori>{2,4,-2,0,1,3,0,1,3,-1,1,2,0,-1,2,1}),
    crea_matrice_pascal("pascal",10),
    crea_matrice_tridiagonal("tridiangonal",52)
  };

  int n = 0;
  while (true) {
    do
    {
      cerr << "numero matrice {1,2,3,4}: " << endl;
      cin >> n;
    } while (n < 1 || n > 4);
    cout << "*******************************************************************************" << endl;
    matrice mat = matrici[n-1];
    stampa_matrice(mat);
    cout << "norma:" << normaInf(mat) << endl;

    matrice inversa = crea_inversa(mat);
    inversa.nome = "inversa";
    //stampa_matrice(inversa);
    //stampa_matrice(prodotto(mat,inversa));
    cout << "norma inversa:" << normaInf(inversa) << endl;

    cout << "condizionamento: " << normaInf(mat)*normaInf(inversa) << endl;

    stampa_matrice (calcola_soluzioni(mat));
    stampa_matrice (calcola_soluzioni_perturbate(mat));
    cout << "*******************************************************************************" << endl;
  }
}
