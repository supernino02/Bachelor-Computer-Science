#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef long double use;

void print(vector <int> A,use x1, const vector <use>&X){
    cout << "x = " << x1 << "; exp(" << x1 << ") = "<< exp(x1) << "\n\n";
    for (size_t i = 0; i < A.size(); i++) {
      cout << "\t" <<A[i] << " -> " << X[i] << endl;
    }
    cout << endl;
}

//ESERCIZIO 1
void esercizio1(int d0, int d1){
    double a,b,c;
    for(int i=0; i<=6; i++){
        a=(d0+1) * pow(10, i);
        b=(d1+1) * pow(10, 20);
        c=-b;
        cout << "i = " << i << endl << "\t(a+b)+c: " << (a+b)+c << endl << "\ta+(b+c): " << a+(b+c) << "\n";
    }
}

//ESERCIZIO 2-a
use binomiale(int j, use x){
    use ris = 1;
    for (int i = 1 ; i <= j; i++)
       ris *= x/(i);
    return ris;
}

vector <use> taylor(use x, const vector <int>&A){
    //io ho una f(x) = e^x
    //implemtare polinomio di taylor (sommatoria di x^n/n!)
    vector <use> V;
    for(int j=0; j<A.size(); j++){
        int grado=A.at(j);
        use tot = 0; //anche se polinomio di taylor partendo da grado 0 è sempre 1
        for(int i=0; i<=grado; i++)
           tot += binomiale(i, x);
        V.push_back(tot);
    }
    return V;
}

//ESERCIZIO 2-b
vector <use> reciproco(vector <use>&A){
    vector <use> V = A;
    for(int i=0; i<V.size(); i++)
        V.at(i) = 1/(V.at(i));
    return V;
}

//ESERCIZIO 3
template <typename T> T precisioneMacchina(T ans, int &iterator){
    for(long long i=0; true; i++){
        ans = pow(2, -i);
        if(!(1+ans>1)){
            iterator=i;
            break;
        }
    }
    return ans;
}

int main(){

    //ESERCIZIO 1
    //matricola primo componente Derqui Andrea 5229435
    cout << "\n\tESERCIZIO 1\n\n";
    int d0=5,d1=3;
    esercizio1(d0, d1);

    //ESERCIZIO 2-a
    cout << "\n\tESERCIZIO 2 algoritmo 1. f(x)=e^x\n\n";
    use x1 = 0.5;
    use x2 = 30;
    use x1n = -x1;
    use x2n = -x2;
    vector <int> A={3, 10, 50, 100, 150};

    vector <use> r1 = taylor(x1,A);
    vector <use> r2 = taylor(x2,A);
    vector <use> r1n = taylor(x1n,A);
    vector <use> r2n = taylor(x2n,A);

    print(A,x1, r1);
    print(A,x2, r2);
    print(A,x1n, r1n);
    print(A,x2n, r2n);

        //PER VALORI "LONTANI" DA ZERO I RISULTATI TENDONO AD "ESPLODERE"
        //PER QUELLI VICINI OTTENIAMO UN' APPROSIMAZIONE FEDELE AL CONTROLLO CON LA FUNZIONE DI LIBRERIA exp()

    //ESERCIZIO 2-b
    cout << "\n\tESERCIZIO 2 algoritmo 2. Nota che f(-x) = 1/f(x)\n\n";
        // se f(-x)=1/(f(x)) allora
        //f(-x) è congruente circa a 1/Taylor(x) di in base al n-grado
        //sostanzialmente invece di calcolare Taylor per -0.5 e -30,
        //calcolo taylor di +0.5 e +30 e ne applico il reciproco ovvero 1/y.
        //NOTARE CHE QUESTA APPROSSIMAZIONE è MIGLIORE DELL' ESPONENZIALE VERO

    vector <use> r1es2 = reciproco(r1);
    vector <use> r2es2 = reciproco(r2);
    print(A,x1n, r1es2);
    print(A,x2n, r2es2);
    cout << "\n\tESERCIZIO 3. Precisione di macchina\n\n";
    int iterator;
    float epsfloat = precisioneMacchina(epsfloat ,iterator);
    cout << "Singola precisione: " << epsfloat << ". Il valore d corrisponde a " << iterator << ".\n";
    double epsdouble = precisioneMacchina(epsdouble ,iterator);
    cout << "Doppia precisione: " << epsdouble << ". Il valore d corrisponde a " << iterator << ".\n";
/*  curiosità sul long double
    long double epsdouble1 = precisioneMacchina(epsdouble1 ,iterator);
    cout << "Precisione long double: " << epsdouble1  << ". Il valore d corrisponde a " << iterator << "\n";
*/
}
