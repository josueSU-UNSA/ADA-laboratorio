#include <iostream>
#include <assert.h>
#include<ctime>
#include<random>
#include<fstream>
using namespace std;
double execution_time[11];
 int size_matrices[]={2,4,16,32,64,128,256,512,1024,2048,4096};
// 4.1 Ejercicio 1
// Dado los algoritmos de multiplicaci ́on de matrices, verificar que el algoritmo de Strassen con un tiempo de ejecuci ́on
// de Θ(n
// lg 7) es m ́as r ́apido que el algoritmo de multiplicaci ́on est ́andar (con tiempo de ejecuci ́on de Θ(n
// 3
// )) para


int random_num(){
    return rand()%10+1;//Numeros del 1 al 10
}
// matrices n × n con n ≥ 32. Realice las optimizaciones necesarias para aproximarse al tiempo te ́orico.
// Realice pruebas con diferente tama ̃nos de matrices cuadradas (tama ̃no en base a potencia 2 como 2,4,8,16,32,64,....).
// Registre los tiempos de procesamiento y verifique cual de los algoritmos es m ́as r ́apido. Elabore un gr ́afico que
// demuestre la comparaci ́on de ambos algoritmos.
template<class T>
class Matriz{
    public:
        int m_Num_row,m_Num_column;
        T **m_Matriz;
        double time_operations;
        
    public:
        Matriz(int ,int );
        void print_matrix();
        Matriz &operator=( Matriz& p);
        Matriz operator+( Matriz&p1);
        Matriz multiplicacion(Matriz &matrix_2 );
        
        
        // T operator[][](int index_1,int index_2);
        
        

    
};
template<class T>
Matriz<T>::Matriz(int num_fil,int num_col){
    this->m_Num_row=num_fil;
    this->m_Num_column=num_col;
    if(!this->m_Num_row || !this->m_Num_column){
        cout<<"wrong in matrix' dimention ";
        assert(0);//The "ASSERT" MACRO allows this program to break the normal flow and dont continue the execution
    }
    this->m_Matriz=new T*[this->m_Num_row];
    for(int i=0;i<this->m_Num_row;i++){
        this->m_Matriz[i]=new T[this->m_Num_column];//to make the columns for each of the rows
        for(int j=0;j<this->m_Num_column;j++)this->m_Matriz[i][j]=0;        
    }
    this->time_operations=0;
}
template<class T>   
void Matriz<T>::print_matrix() {
    for(int i=0;i<this->m_Num_row;i++){
        cout<<"[ ";
        for(int j=0;j<this->m_Num_column;j++)cout<<this->m_Matriz[i][j]<<" ";
        cout<<"]"<<endl;
    }  
}
template<class T>   
Matriz<T>& Matriz<T>::operator=( Matriz & matrix_to_copy){
    for(int i=0;i<this->m_Num_row;i++){
        for(int j=0;j<this->m_Num_column;j++){
            this->m_Matriz[i][j]=matrix_to_copy.m_Matriz[i][j];
        }
    }
    return *this;
}
template<class T>
Matriz<T> Matriz<T>::operator+( Matriz &matriz_2){
    if(this->m_Num_row==matriz_2.m_Num_row  && this->m_Num_column==matriz_2.m_Num_column){
        Matriz<T> matriz_sumas;
        unsigned t0,t1;
        t0=clock();
        for(int i=0;i<this->m_Num_row;i++){
            for(int j=0;j<this->m_Num_column;j++){
                matriz_sumas.m_Matriz[i][j]=this->m_Matriz[i][j]+matriz_2.m_Matriz[i][j];
            }
        }
        t1 = clock();//Final del cronometro
        this->time_operations = (double(t1-t0)/CLOCKS_PER_SEC);
        return matriz_sumas;
    }
 
    cout<<"the matrixes' dimentions are differents ";
    return matriz_2;//Esto no vale  ya q el assert para todo
    assert(0);
 
}
template<class T>
Matriz<T> Matriz<T>:: multiplicacion(Matriz &matrix_2 ){
    // matrix_multiplication=this_matrix * ,matrix_2
    
    
    if(this->m_Num_column!=matrix_2.m_Num_row){
        cout<<"the dimentions don't allow do this operation ";
        assert(0); 
    }
    
    Matriz<T> matrix_multiplication(this->m_Num_row,this->m_Num_column);//Declaration and initialization of the resultant matrix
    unsigned t0,t1;
    t0=clock();
    for(int i=0;i<this->m_Num_row;i++){
        for(int j=0;j<this->m_Num_column;j++){
            matrix_multiplication.m_Matriz[i][j]=0;
            for(int k=0;k<this->m_Num_row;k++){
                // aik·bkj
                matrix_multiplication.m_Matriz[i][j]=matrix_multiplication.m_Matriz[i][j]+this->m_Matriz[i][k]*matrix_2.m_Matriz[k][j];
            }
        }
    }
    t1=clock();
    this->time_operations=(double(t1-t0)/CLOCKS_PER_SEC);
    return matrix_multiplication;
}

bool make_txt_size(string name_file){
    ofstream file;
    file.open(name_file);
    if(file.fail()){
        exit(1);//PARA SALIR DEL PROGRAMA
        file.close();
        return false;
    }
    for(int i=0;i<11;i++)file<<size_matrices[i]<<endl;
    file.close();
    return true;
}

bool make_txt_time(string name_file){
    ofstream file;
    file.open(name_file);
    if(file.fail()){
        exit(1);//PARA SALIR DEL PROGRAMA
        file.close();
        return false;
    }
    for(int i=0;i<11;i++)file<<execution_time[i]<<endl;
    file.close();
    return true;
}


int main(){
    srand(time(0));
    // int num_fil_n_c=128,num_col_n_c=128;
    for(int i=0;i<11;i++){

        int num_fil=size_matrices[i],num_col=size_matrices[i];
        Matriz<int> test_matrix_1(num_fil,num_col);
    
        for(int i=0;i<num_fil;i++){
            for(int j=0;j<num_col;j++){
    
                test_matrix_1.m_Matriz[i][j]=random_num();
    
            }
        }
    
    
        Matriz<int> test_matrix_2(num_fil,num_col);
        for(int i=0;i<num_fil;i++){
            for(int j=0;j<num_col;j++){
                
                test_matrix_2.m_Matriz[i][j]=random_num();
                
            }
        }
        Matriz<int> test_matrix_3(num_fil,num_col);
        
        
        // cout<<"Las matrices son:\n-Matriz 1:\n";
        // for(int i=0;i<40;i++)cout<<"-";
        // cout<<endl;
        // test_matrix_1.print_matrix();
        
        // cout<<"-Matriz 2:\n";
        // for(int i=0;i<40;i++)cout<<"-";
        // cout<<endl;
        // test_matrix_2.print_matrix();
        
        
        
        // for(int i=0;i<40;i++)cout<<"-";
        // cout<<endl;
        // cout<<"La matriz multiplicacion es\n";
        
        
        
        Matriz<int>matrix_multiplic(num_fil,num_col);
        matrix_multiplic=test_matrix_1.multiplicacion(test_matrix_2);
        execution_time[i]=test_matrix_1.time_operations;
        // matrix_multiplic.print_matrix();
        // cout<<"El tiempo de ejecucion de la multiplicacion de ambas matrices es "<<test_matrix_1.time_operations<<endl;
    }
    (make_txt_size("Multiplicacion_tradicional_tamanos.txt"))?cout<<"TXT de dimensiones generada\n":cout<<"TXT de dimensiones NO generado\n";
    (make_txt_time("Multiplicacion_tradicional_times.txt"))?cout<<"TXT de execution time generada\n":cout<<"TXT de execution time NO generado\n";
    
    return 0;
}