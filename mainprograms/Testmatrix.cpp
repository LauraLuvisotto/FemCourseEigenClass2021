
///\cond
#include <iostream>
#include <math.h>
///\endcond
#include "DataTypes.h"
#include "tmalha.h"
#include "TVec.h"

#ifdef WIN32
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

using std::cout;
using std::endl;
using std::cin;

/// verifica se o vetor funciona e eh robusto
void TesMatrixXd();
int TestSolve_LUl();

int main ()
{
    int res;
    
    res = TestSolve_LUl();

  
  return 0;
}

int ConstructorWrongArg()
{
  cout <<__PRETTY_FUNCTION__<<endl;
  int certo = 0;
  cout << "Teste 1: contrutor inicializado com parametros negativos" <<endl;
  try {
    MatrixXd a(-1,-1);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

int ElementOutOfScope()
{
  cout <<__PRETTY_FUNCTION__<<endl;
  int certo = 0;
  MatrixXd vec(5,5);
  
  cout <<"Teste 1: selecao de elementos negativos e fora do escopo." <<endl;
  try {
    vec(-1,2);
    vec(4,5);
  } catch (...) {
    certo = 1;
  }
  
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

int CopyConstructor()
{
  cout<<__PRETTY_FUNCTION__<<endl;
  cout<<"Teste 1: inicializacao basica de construtor de copia"<<endl;
  int certo = 1;
  try {
    MatrixXd a(1000,10);
    MatrixXd b(a);
    
  } catch (...){
    std::cout << "Teste 1: Errado!\n";
    certo = 0;
  }
  if (certo == 1) {
    std::cout << "Teste 1: Ok.\n";
    certo = 1;
  }
  std::cout << "---------------//----------------\n";
  return certo;
}

int EqualOperator()
{
  cout<<__PRETTY_FUNCTION__<<endl;
  cout<<"Teste 1: Teste  de funcionamento operador igual"<<endl;
  int certo = 0;
  try {
    MatrixXd a(1000,1);
    MatrixXd b;
    b = a;
    
  } catch (...) {
    std::cout << "Teste 1: Errado!\n";
    certo = 0;
  }
  if (certo == 0) {
    std::cout << "Teste 1: Ok\n";
    certo = 1;
  }
  std::cout << "---------------//----------------\n";
  return certo;
}

int NullSizeMatrix()
{
  cout<<__PRETTY_FUNCTION__<<endl;
  cout<<"Teste 1: matriz de tamanho zero, atribuicao com operador igual e construtor de copia"<<endl;
  int certo = 1;
  try {
    MatrixXd a(0,0);
    MatrixXd b;
    MatrixXd c(a);
    b = a;
    
  } catch (...) {
    std::cout << "Teste 1: Errado!\n";
    certo = 0;
  }
  if (certo == 1) {
    std::cout << "Teste 1: Ok\n";
  }
  std::cout << "---------------//----------------\n";
  return certo;
}

///Recebe o valor val e aloca o mesmo na posicao i j da matriz;
int TestPutVal ()
{
  cout<<__PRETTY_FUNCTION__<<endl;
  int certo = 1;
  MatrixXd Teste (3,3);
  Teste.PutVal(1, 2, 5.);
  
  cout<<"Teste 1: verificação se PutVal e GetVal."<<endl;
  if (Teste .GetVal(1, 2) != 5.) {
    certo = 0;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  certo = 0;
  cout<<"Teste 2: PutVal linha fora do escopo."<<endl;
  try {
    Teste .PutVal(3, 2,9.);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  certo = 0;
  cout<<"Teste 3: PutVal linha negativa."<<endl;
  try {
    Teste .PutVal(-1, 2,9.);
  } catch (std::bad_exception){
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  certo = 0;
  cout<<"Teste 4: PutVal coluna inexistente."<<endl;
  try {
    Teste .PutVal(1, 3,9.);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  
  certo = 0;
  cout<<"Teste 5: PutVal coluna negativa."<<endl;
  try {
    Teste .PutVal(1, -1,9.);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 5: Ok."<<endl;}
  else cout <<"Teste 5: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Retorna um valor double da matriz pertencenet a posicao i j da matriz;
///Recebe o valor val e aloca o mesmo na posicao i j da matriz;
int TestGetVal ()
{
  int certo = 1;
  MatrixXd Teste (3,3);
  Teste .PutVal(1, 2, 5.);
  
  certo = 0;
  cout<<"Teste 1: GetVal linha fora do escopo."<<endl;
  try {
    Teste .GetVal(3, 2);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  cout<<"Teste 2: GetVal linha negativa."<<endl;
  certo = 0;
  try {
    Teste .GetVal(-1, 2);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  certo = 0;
  cout<<"Teste 3: GetVal coluna fora do escopo."<<endl;
  try {
    Teste .GetVal(1, 3);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  certo = 0;
  cout<<"Teste 4: GetVal negativa."<<endl;
  try {
    Teste .GetVal(1, -1);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Retorna o numero de linhas que a matriz possui;
int TestRows(void)
{
  cout <<__PRETTY_FUNCTION__<<endl;
  MatrixXd Teste (132,4);
  int certo = 1;
  cout<<"Teste 1: Verificacao de retorno."<<endl;
  if (Teste .Rows() != 132) {
    certo = 0;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Retorna o numero de colunas que a matriz possui;
int TestCols(void)
{
  MatrixXd Teste (3,87);
  int certo = 1;
  
  cout<<"Teste 1: Verificacao de retorno."<<endl;
  if (Teste .Cols() != 87) {
    certo = 0;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
  
}

///Edita o tamanho da matriz para um novo numero de row`s e col`s;
int TestResize()
{
  //CONTRUCAO DE UMA MATRIZ RANDOM
  MatrixXd a(5,10);
  for (int i=0; i<a.Rows(); i++) {
    for (int j=0; j<a.Cols(); j++) {
      a(i,j) = rand();
    }
  }
  int certo = 1;
  
  cout<<"Teste 1: truncamento e expancao, de 5x10 -> 20x5" <<endl;
  MatrixXd b(a);
  b.Resize(20, 5);
  for (int i=0; i<b.Rows(); i++) {
    for (int j=0; j<b.Cols(); j++) {
      if (i<a.Rows() && j<a.Cols() && a(i,j) != b(i,j)) {
        certo = 0;
      }
      else if ((i>= a.Rows() || j>=a.Cols()) && b(i,j) != 0.)
      {
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Transpoe a matriz;
int TestTranspose()
{
  cout<<__PRETTY_FUNCTION__<<endl;
  int certo = 0;
  MatrixXd a;
  cout <<"Teste 1: Transposicao de uma matriz vazia."<<endl;
  try {
    a.Transpose();
  } catch (std::bad_exception) {
    certo=1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  //criacao de uma matriz aleatoria;
  a.Resize(10,15);
  for (int i=0; i<a.Rows(); i++) {
    for (int j=0; j<a.Cols(); j++) {
      a(i,j) = rand();
    }
  }
  //copia da matriz a para b;
  MatrixXd b(a);
  //transposicao da matriz b;
  b.Transpose();
  
  cout<<"Teste 2: verificacao de resultado da funcao"<<endl;
  certo=1;
  for (int i=0; i<a.Rows(); i++) {
    for (int j=0; j<a.Cols(); j++) {
      if (a(i,j) != b(j,i)) {
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Retorna um vetor do tamanho do numero de colunas da matriz referente a linha row;
int TestGetRow()
{
  
  cout <<__PRETTY_FUNCTION__ << endl;
  int certo = 0;
  MatrixXd a;
  VecDouble vec;
  
  cout<<"Teste 1: Verificação de GetRow em uma matriz vazia" <<endl;
  try
  {
    vec = a.GetRow(1);
  } catch (std::bad_exception) {
    certo=1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  //Definicao de a como REAL e aleatoria;
  a.Resize(10,15);
  for (int i=0; i<a.Rows(); i++) {
    for (int j=0; j<a.Cols(); j++) {
      a(i,j) = rand();
    }
  }
  
  cout<<"Teste 2: GetRow de uma linha negativa"<<endl;
  certo = 0;
  try {
    vec = a.GetRow(-3);
  } catch(std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  cout<<"Teste 3: GetRow de uma linha inexistente"<<endl;
  certo = 0;
  try {
    vec = a.GetRow(13);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  certo = 1;
  cout<<"Teste 4: verificacao do vetor extraido por GetRow"<<endl;
  for (int i=0; i<a.Rows(); i++) {
    vec = a.GetRow(i);
    //Teste  de se todas os vetores obtidos por GetRow correspondem realmente a linha da matriz.
    for (int j=0; j<a.Cols(); j++) {
      if(vec[j] != a(i,j)){
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Retorna um vetor do tamanho do numero de linhas da matriz referente a coluna col;
//VectorXd GetCol(int col) const;

int TestGetCol()
{
  cout <<__PRETTY_FUNCTION__ << endl;
  
  MatrixXd a;
  VecDouble vec;
  int certo=0;
  
  cout<<"Teste 1: Verificação de GetRow em uma matriz vazia" <<endl;
  try {
    vec = a.GetRow(1);
  } catch (std::bad_exception) {
    certo=1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  //definicao de uma matroz random;
  a.Resize(3,6);
  for (int i=0; i<a.Rows(); i++) {
    for (int j=0; j<a.Cols(); j++) {
      a(i,j) = rand();
    }
  }
  
  cout<<"Teste 2: Funcao GetCol de uma coluna negativa." <<endl;
  certo = 0;
  try {
    vec = a.GetCol(-3);
  } catch(std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  cout<<"Teste 3: Funcao GetCol de uma coluna inexistente." <<endl;
  certo = 0;
  try {
    vec = a.GetCol(13);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  cout<<"Teste 4: Verificacao do funcionamento da funcao." <<endl;
  certo=1;
  for (int j=0; j<a.Cols(); j++) {
    vec = a.GetCol(j);
    //Teste  de se todas os vetores obtidos por GetCol correspondem realmente a coluna da matriz.
    for (int i=0; i<a.Rows(); i++) {
      if(vec[i] != a(i,j)){
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Decompoe e resolve o sistema
//void Solve_LU(MatrixXd &rhs); // why here?
int TestSolve_LUl()
{
    cout <<__PRETTY_FUNCTION__ << endl;
    
    MatrixXd a,b;
    VectorXd vec;
    int certo=0;
    
    cout<<"Teste 1: Verificação de resolução de sistema, matriz vazia" <<endl;
    try {
        a.Solve_LU(b);
    } catch (std::bad_exception) {
        certo=1;
    }
    if(certo==1){cout<<"Teste 1: Ok."<<endl;}
    else cout <<"Teste 1: Errado."<<endl;
    
    
    cout<<"Teste 2: Verificação do escopo das matrizes do sistema" <<endl;
    
    //Definicao de a como REAL e aleatoria;
    a.Resize(10,15);
    for (int i=0; i<a.Rows(); i++) {
        for (int j=0; j<a.Cols(); j++) {
            a(i,j) = rand();
        }
    }
    b.Resize(7, 5);
    for (int i=0; i<b.Rows(); i++) {
        for (int j=0; j<b.Cols(); j++) {
            b(i,j) = rand();
        }
    }
    

    try {
        a.Solve_LU(b);
    } catch (std::bad_exception) {
        certo=1;
    }
    if(certo==1){cout<<"Teste 2: Ok."<<endl;}
    else cout <<"Teste 2: Errado."<<endl;
    
    

    
    cout<<"Teste 3: Verificação da funcionalidade do Solve_LU" <<endl;
    
    //definicao de uma matriz não singular e uma matriz cópia;
    
    MatrixXd c(4,4,0.0);
    TVecNum<double> sumrow(c.Rows());
    for (int i=0; i<c.Rows(); i++) {
        for (int j=0; j<c.Cols(); j++) {
            c(i,j) = rand();
            if (i!=j) {
                sumrow[i]+=c(i,j);
            }
        }
        c(i,i)=sumrow[i]+1;
    }
    
    //c.Print();
    
    MatrixXd ccp;
    ccp=c;
    c.Solve_LU(ccp);
    
    for (int i=0; i<ccp.Rows(); i++) {
            
        if (fabs(ccp.GetVal(i, i) - 1) > 1.e-9 ) {
                    certo=0;
            }
            
        for(int j=0; j<ccp.Cols();j++){
                
        if (i!=j) {
            if (fabs(ccp.GetVal(i, j) - 0) > 1.e-9 ) {
                    certo=0;
                }
            }
                
        }
        
    }
    
    //ccp.Print();
    
    //definicao de uma matriz não singular e um vetor cujos elemntos são a soma de cada linha da matriz;
    
    MatrixXd d(3,3,0.0),e(3,1,0.0);
    
    TVecNum<double> sumrowd(d.Rows()),sumrowe(d.Rows());
    for (int i=0; i<d.Rows(); i++) {
        for (int j=0; j<d.Cols(); j++) {
            d(i,j) = rand();
            if (i!=j) {
                sumrowd[i]+=d(i,j);
            }
            
        }
        d(i,i)=sumrowd[i]+1;
        e.PutVal(i, 0, 2*sumrowd[i]+1);
        
    }
    
    d.Solve_LU(e);
   
    
    for (int i=0; i<e.Rows(); i++) {
        
        if (fabs(e.GetVal(i, 0) - 1) > 1.e-9 ) {
            certo=0;
        }
        
    }
    //e.Print();
    
    if(certo==1){cout<<"Teste 3: Ok."<<endl;}
    else cout <<"Teste 3: Errado."<<endl;
    
  
    std::cout << "---------------//----------------\n";
    return certo;
}




///Chama o valor existente na posicao i,j da matriz, sendo possivel, retornar o valor existente nesta posicao ou atribuir um valor double a esta posicao;
//double &operator ()(int i, int j);
int TestSelectOperator()
{
  cout<<__PRETTY_FUNCTION__<<endl;
  
  int certo = 1;
  MatrixXd a(10,15,9);
  
  cout<<"Teste 1: verificacao de funcionalidade do operador"<<endl;
  double Teste  = -78;
  a.PutVal(1, 14, -78.);
  if (Teste  != a(1, 14)) {
    certo = 0;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  //matriz vazia;
  MatrixXd b;
  
  cout<<"Teste 2: acesso de posicao negativa na matriz"<<endl;
  certo = 0;
  try {
    Teste  = a(-1,-1);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  cout<<"Teste 3: acesso de posicao inexistente na matriz"<<endl;
  certo=0;
  try {
    Teste  = a(23,32);
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  cout<<"Teste 4: acesso a uma posicao de uma matriz vazia"<<endl;
  certo=0;
  try {
    Teste  = b(1,1);
  } catch (std::bad_exception) {
    certo=1;
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Soma os elementos de duas matrizes de mesmo tamanho, retornando uma matriz com este valor;
//MatrixXd operator +(MatrixXd &fator);

int TestPlusOperator ()
{
  cout <<__PRETTY_FUNCTION__<<endl;
  int  certo = 1;
  MatrixXd fat1, fat2, Result;
  
  cout<<"Teste 1:soma de matrizes vazias"<<endl;
  certo=0;
  try {
    Result = fat1 + fat2;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  //criacao de uma matriz 4x4 aleatoria;
  fat1.Resize(4, 4);
  for (int i=0; i<fat1.Rows(); i++) {
    for (int j=0; j<fat1.Cols(); j++) {
      fat1(i,j) = rand();
    }
  }
  
  cout<<"Teste 2: Somatoria de matriz vazia com matriz real" <<endl;
  certo=0;
  try {
    Result = fat1 + fat2;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  //criaca de uma matriz 4x8 aleatoria;
  fat2.Resize(4, 8);
  for (int i=0; i<fat2.Rows(); i++) {
    for (int j=0; j<fat2.Cols(); j++) {
      fat2(i,j) = rand();
    }
  }
  
  cout<<"Teste 3: somatoria de matrizes reais com tamanho diferentes" <<endl;
  try {
    Result = fat1 + fat2;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  //resize da matriz fat2 para 4x4
  fat2.Resize(4, 4);
  
  cout<<"Teste 4: congruencia do operador de soma"<<endl;
  Result = fat2+fat1;
  for (int i=0; i<Result.Rows(); i++) {
    for (int j=0; j<Result.Cols(); j++) {
      //Teste  de congruencia de valores.
      if(Result(i,j) != fat1(i,j)+fat2(i,j))
      {
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Subtrai os elementos de duas matrizes de mesmo tamanho, retornando uma matriz com este valor;
//MatrixXd operator -(MatrixXd &fator);
int TestMinusOperator ()
{
  cout <<__PRETTY_FUNCTION__<<endl;
  int  certo = 1;
  MatrixXd fat1, fat2, Result;
  
  cout<<"Teste 1: subtracao de matrizes vazias."<<endl;
  certo=0;
  try {
    Result = fat1 - fat2;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  //matriz aleatoria 4x4
  fat1.Resize(4, 4);
  for (int i=0; i<fat1.Rows(); i++) {
    for (int j=0; j<fat1.Cols(); j++) {
      fat1(i,j) = rand();
    }
  }
  
  cout<<"Teste 2: subtracao de matriz vazia com matriz real."<<endl;
  certo=0;
  try {
    Result = fat1 - fat2;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  //atribuicao de valores a matriz fat2.
  fat2.Resize(4, 8);
  for (int i=0; i<fat2.Rows(); i++) {
    for (int j=0; j<fat2.Cols(); j++) {
      fat2(i,j) = rand();
    }
  }
  
  cout<<"Teste 3: subtracao de matrizes de tamanho diferente"<<endl;
  certo=0;
  try {
    Result = fat1 - fat2;
  } catch (std::bad_exception) {
    certo=1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  cout<<"Teste 4: verificacao de congruencia de valores da subtracao"<<endl;
  fat2.Resize(4, 4);
  Result = fat2-fat1;
  for (int i=0; i<Result.Rows(); i++) {
    for (int j=0; j<Result.Cols(); j++) {
      if(Result(i,j) != fat2(i,j)-fat1(i,j))
      {
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Multiplica todos os elementos de uma matriz por um double m;
//MatrixXd &operator *(double m);
int TestScalarOperator ()
{
  cout <<__PRETTY_FUNCTION__<<endl;
  int certo = 0;
  double esc = 2.;
  MatrixXd a;
  
  cout <<"Teste 1: escalar multiplicado por matriz vazia."<<endl;
  try {
    a = a*esc;
  } catch (std::bad_exception) {
    certo = 1;
    cout <<"Teste  1: Ok." <<endl;
  }
  if (certo == 0) {cout<<"Teste  1: Errado."<<endl; }
  
  a.Resize(2, 3);
  for (int i=0; i<a.Rows(); i++) {
    for (int j=0; j<a.Cols(); j++) {
      a(i,j) = 2;
    }
  }
  
  MatrixXd b;
  b = a*esc;
  
  cout <<"Teste 2: congruencia de valores."<<endl;
  for (int i=0; i<a.Rows(); i++) {
    for (int j=0; j<a.Cols(); j++) {
      if(b(i,j)!= esc*a.GetVal(i,j))
      {
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  if(certo==0){cout<<"Teste 2: Errado."<<endl;}
  std::cout << "---------------//----------------\n";
  return certo;
}

///Multiplica duas matrizes respeitando as regras da algebra linear;
//MatrixXd operator *(MatrixXd &fator);
int TesMatrixXdOperator ()
{
  cout <<__PRETTY_FUNCTION__<<endl;
  int certo = 1;
  MatrixXd fat1, fat2, res;
  
  cout <<"Teste 1: Multiplicacao de matrizes vazias."<<endl;
  try {
    res = fat1*fat2;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  fat1.Resize(3, 2);
  for (int i=0; i<fat1.Rows(); i++) {
    for (int j=0; j<fat1.Cols(); j++) {
      fat1(i,j) = rand();
    }
  }
  fat2.Resize(4, 8);
  for (int i=0; i<fat2.Rows(); i++) {
    for (int j=0; j<fat2.Cols(); j++) {
      fat2(i,j) = rand();
    }
  }
  
  cout <<"Teste 2: Multiplicacao de matrizes com tamanhos nao corretos."<<endl;
  try {
    res = fat1*fat2;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  cout <<"Teste 3: Congruencia dos valores."<<endl;
  fat2.Resize(2, 7);
  res = fat1*fat2;
  MatrixXd mult(3,7,0.);
  for (int i=0; i<mult.Rows(); i++) {
    for (int j=0; j<mult.Cols(); j++) {
      for (int k=0; k<fat1.Cols(); k++) {
        mult(i, j) += fat1.GetVal(i, k)*fat2(k, j);
      }
    }
  }
  
  for (int i=0; i<mult.Rows(); i++) {
    for (int j=0; j<mult.Cols(); j++) {
      if (mult(i,j) != res(i,j)) {
        certo=0;
      }
    }
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  std::cout << "---------------//----------------\n";
  return certo;
}

///Multiplica uma matriz por um vetor vec e retorna um valor de mesmo tamanho vec (respeita as regras da algebra linear);
//VectorXd operator *(VectorXd &vec);
int TestVecMatrix ()
{
  cout <<__PRETTY_FUNCTION__<<endl;
  int certo = 1;
  TVecNum<double> a, res;
  MatrixXd mat;
  
  cout<<"Teste 1: elementos da multiplicacao vazios" <<endl;
  try {
    res = mat*a;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  
  mat.Resize(3,3);
  for (int i=0; i<mat.Rows(); i++) {
    for (int j=0; j<mat.Cols(); j++) {
      mat(i,j) = rand();
    }
  }
  cout<<"Teste 2: vetor vazio*matriz real"<<endl;
  try {
    res = mat*a;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  a.Resize(10);
  for (int i=0; i<a.Size(); i++) {
    a[i] = rand();
  }
  
  cout<<"Teste 3: vetor de tamanho diferente do numero de colunas." <<endl;
  try {
    res = mat*a;
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  cout<<"Teste 4: Teste  de congruencia da multiplicacao"<<endl;
  a.Resize(3);
  res = mat*a;
  TVecNum<double> mult(mat.Rows());
  mult.setZero();
  for (int j=0; j<mat.Rows(); j++) {
    for (int i=0; i<mat.Cols(); i++) {
      mult[j] += mat.GetVal(j,i)*a[i];
    }
  }
  
  for (int i=0; i<mult.Size(); i++) {
    if (fabs(mult[i] - res[i]) > 1.e-9 ) {
      certo=0;
    }
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  
  std::cout << "---------------//----------------\n";
  return certo;
}

///Compara duas matrizes e retorna true ou false;
//bool operator == (MatrixXd &mat2);
int CompareMatrix()
{
  
  cout <<__PRETTY_FUNCTION__<<endl;
  int certo = 1;
  
  MatrixXd a,b;
  
  cout <<"Teste 1: bool functions entre funcoes vazias" <<endl;
  try {
    if (a==b) {
    }
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 1: Ok."<<endl;}
  else cout <<"Teste 1: Errado."<<endl;
  
  certo = 0;
  a.Resize(2, 2);
  
  cout <<"Teste 2: bool functions entre funcao vazia e funcao real" <<endl;
  try {
    if (a==b) {
    }
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 2: Ok."<<endl;}
  else cout <<"Teste 2: Errado."<<endl;
  
  b.Resize(3,3);
  for (int i=0; i<b.Rows(); i++) {
    for (int j=0; j<b.Cols(); j++) {
      b(i,j) = rand();
    }
  }
  
  cout <<"Teste 3: bool functions entre matrizes de diferentes tamanhos" <<endl;
  try {
    if (a==b) {
    }
  } catch (std::bad_exception) {
    certo = 1;
  }
  if(certo==1){cout<<"Teste 3: Ok."<<endl;}
  else cout <<"Teste 3: Errado."<<endl;
  
  
  cout <<"Teste 4: congruencia de valores." <<endl;
  MatrixXd c(b);
  for (int i=0; i<b.Rows(); i++) {
    for (int j=0; j<b.Cols(); j++) {
      if (c(i,j) != b(i,j)) {
        certo = 0;
      }
    }
  }
  if(certo==1){cout<<"Teste 4: Ok."<<endl;}
  else cout <<"Teste 4: Errado."<<endl;
  
  std::cout << "---------------//----------------\n";
  return certo;
}



/// verifica se o vetor funciona e eh robusto
void TesMatrixXd()
{
  if( (
       CompareMatrix() &&
       ConstructorWrongArg() &&
       ElementOutOfScope() &&
       CopyConstructor() && EqualOperator() &&
       TestVecMatrix() &&
       NullSizeMatrix() && TestPutVal() && TestGetVal() && TestRows() && TestCols() && TestResize() && TestTranspose() &&TestGetRow() && TestGetCol()&&TestSolve_LUl() /*&& Teste SelectOperator()*/
       ) == 0
     )
  {
    std::cout << "Seu codigo nao passou no Teste... D:\n";
  }
  else
  {
    std::cout << "Seu codigo passou no Teste! :D\n";
  }
}