
#ifndef funciones_h
#define funciones_h

#include <iostream>


using namespace std;

class Funciones{
    public:
    int sumaIterativa (int n);
    int sumaRecursiva (int n);
    int sumaDirecta (int n);
};

 int Funciones :: sumaIterativa(int n){
    int acum=0;
    while (n<0){
        cout<<"N es un numero negativo,necesitas un numero postivo : ";
        cin >> n;
    }
	for (int i=1;i<=n;i++){
		acum+= i;
	}
	return acum;
}

int Funciones:: sumaRecursiva(int n){
    while (n<0){
        cout<<"N es un numero negativo,necesitas un numero postivo : ";
        cin >> n;
    }
    if (n<=1){
        return 1;
    }else {
        return n+(sumaRecursiva(n-1));
    }
}

int Funciones :: sumaDirecta(int n){
    int acum=0;
    while (n<0){
        cout<<"N es un numero negativo,necesitas un numero postivo : ";
        cin >> n;
    }
    acum=n*(n+1)/2;
    return acum;
}
#endif