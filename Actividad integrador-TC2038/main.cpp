//Julian Lawrence Gil Soares
//Jose Andres Lozano Alanis
//A00832272
//A01284569
//11/11/2022
//Actividad Integradora 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

char text[1000];


//Algoritmo Longest Common Substring
//Complejidad O(m*n)
//Algoritmo para encontrar el substring más largo entre dos textos
string LCS(char* transmission1, char* transmission2) {
  int N = strlen(transmission1);
  int M = strlen(transmission2);
  int lcs[M + 1][N + 1];
 
    int longitud = 0;
 
    int fila, columna;

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= N; j++) {
            if (i == 0 || j == 0)
                lcs[i][j] = 0;
 
            else if (transmission1[i - 1] == transmission2[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                if (longitud < lcs[i][j]) {
                    longitud = lcs[i][j];
                    fila = i;
                    columna = j;
                }
            }
            else
                lcs[i][j] = 0;
        }
    }
 
 
    char* resultStr = (char*)malloc((longitud + 1) * sizeof(char));

    while (lcs[fila][columna] != 0) {
        resultStr[--longitud] = transmission1[fila - 1]; 
 
        fila--;
        columna--;
    }
  fila++;
  int final = strlen(resultStr) + fila;
  cout << fila << " "<< final <<endl;

  return "";
}


//Algoritmo KMP
//Complejidad O(n)
//Algoritmo para busqueda de patrones dentro de un texto
void compareHelper(char* mcode, int M, int* arr)
{
    int len = 0;
 
    arr[0] = 0;

    int i = 1;
    while (i < M) {
        if (mcode[i] == mcode[len]) {
            len++;
            arr[i] = len;
            i++;
        }
        else
        {

            if (len != 0) {
                len = arr[len - 1];
            }
            else
            {
                arr[i] = 0;
                i++;
            }
        }
    }
}

void compare(char *transmission, char *mcode)
{

  int lenMcode = strlen(mcode);
  int lenTrans = strlen(transmission);

  int arr[lenMcode];

  compareHelper(mcode, lenMcode, arr);

  int indexTrans = 0; 
  int indexMcode = 0; 
  int caracter;
  int comparation = 0;
  int ultimoCaracter;
  bool controlador;
  
  while ((lenTrans - indexTrans) >= (lenMcode - indexMcode))
  {
    if (mcode[indexMcode] == transmission[indexTrans])
    {
      indexMcode++;
      indexTrans++;
    }

    if (indexMcode == lenMcode)
    {
      comparation++;
      caracter = indexTrans-indexMcode+1;
      ultimoCaracter = caracter + lenMcode - 1;
      controlador = true;
      indexMcode = arr[indexMcode - 1];
    }


    else if (indexTrans < lenTrans && mcode[indexMcode] != transmission[indexTrans])
    {
      if (indexMcode != 0)
        indexMcode = arr[indexMcode - 1];
      else
        indexTrans = indexTrans + 1;
    }
  }
  if(comparation == 0)
  {
    controlador = false;
  }
  if(controlador == true)
  {
    cout << "true" << endl;
  }
  else
  {
    cout << "false" << endl;
  }
};


//funcion para leer los archivos con codigo malicioso (mcode1, mcode2, mcode3)
void checkV(char *transmission)
{
  char arr[1000];
  string archivo;
  for (int i = 1; i <= 3; i++)
  {
    archivo = "mcode" + to_string(i) + ".txt";
    ifstream ifs = ifstream(archivo, ios_base::in);
    if (ifs.is_open() == true)
    {
      char c;
      int i = 0;
      while (ifs.get(c))
      {
        arr[i] = c;
        i++;
      }

      ifs.close();
      arr[i] = '\0';
    }
    cout << "  " + archivo + ": ";
      
    compare(transmission, arr);

    cout << endl;
  }
};

//Algoritmo Manacher
//complejidad O(n)
//funcion para encontrar el palindrome mas largo dentro de un string

int min(int a, int b)
{
    int res = a;
    if(b < a)
        res = b;
    return res;
}
 
void palindrome()
{
    int lenText= strlen(text);
    lenText = 1 + (lenText * 2);
    int L[lenText];
    L[0] = 0;
    L[1] = 1;
    int C = 1, R = 2, i = 0;
    int currLeft;
    int len, half = 0;
    int last, diff, first = -1;

     
    for (i = 2; i < lenText; i++)
    {

        currLeft = 2*C-i;
        L[i] = 0;
        diff = R - i;
        if(diff > 0)
            L[i] = min(L[currLeft], diff);
 
        while ( ((i + L[i]) < lenText && (i - L[i]) > 0) &&
            ( ((i + L[i] + 1) % 2 == 0) ||
            (text[(i + L[i] + 1)/2] == text[(i - L[i] - 1)/2] )))
        {
            L[i]++;
        }
 
        if(L[i] > len)
        {
            len = L[i];
            half = i;
        }
 
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
    }
    first = (half - len)/2;
    last = first + len - 1;
    cout << first + 1 << " " << last + 1;
}

int main()
{
  char arr[1000];
  char arr2[1000];

  string firstTransmission;
  string secondTransmission;

  //lectura del primer archivo de texto
  ifstream ifs = ifstream("transmission1.txt", ios_base::in);
  
  if (ifs.is_open() == true)
  {
    char c;
    int i = 0;
    while (ifs.get(c))
    {
      arr[i] = c;
      i++;
    }
    string firstTransmission2;
    string tmp_string(arr);
    
    ostringstream ss;
    ss << ifs.rdbuf();
    firstTransmission = ss.str();

    ifs.close();
    arr[i] = '\0';
    firstTransmission = tmp_string;
  }
  
    
  cout << "Parte 1:" << endl;
  cout << "transmission1.txt: " << endl;
  
  
  checkV(arr);

  //lectura del segundo archivo de texto
  ifs = ifstream("transmission2.txt", ios_base::in);
  if (ifs.is_open() == true)
  {
    char c;
    int i = 0;
    while (ifs.get(c))
    {
      arr2[i] = c;
      i++;
    }
    string tmp_string(arr2);
    ostringstream ss;
    ss << ifs.rdbuf();
    secondTransmission = ss.str();

    ifs.close();
    arr2[i] = '\0';
    secondTransmission = tmp_string;
  }

  cout << "transmission2.txt: " << endl;
  checkV(arr2);

  cout << "Parte 2:" << endl;
  cout << "transmission1.txt: " << endl;
  strcpy(text, arr);
  palindrome();
  cout << "\ntransmission2.txt: " << endl;
  strcpy(text, arr2);
  palindrome();


  cout << endl <<"\nParte 3:" << endl;

  
  cout << LCS(arr, arr2);
}
