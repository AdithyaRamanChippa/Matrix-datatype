#include <bits/stdc++.h>
#define ll long long



using namespace std;

template<typename T>
class matrix{
   ll int row,column,dimension;
   vector<T> a;

   public:
   matrix(int r=1,int c=1,int d=1){
        dimension=d;
        row=r;
        column=c;
     for(int i=0;i<d;i++){
        for(int i=0;i<r;i++){
            for(int i=0;i<c;i++){
                a.push_back((rand()%5));
            }
        }
      }
    }

    int Row(){ return this->row;}
    int Column(){ return this->column;}
 
    void print_m(){
        for(int i=0;i<a.size();i++){
            cout<<a[i]<<" ";
        }
        cout<<endl;
    }
   void print_matrix(){
    for(int k=0;k<dimension;k++){
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                cout<<a[row*column*k+i*column+j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }
        
   }

   matrix operator+(matrix b){
        matrix<T> c(row,column);
        if(this->row==b.row && this->column==b.column){
            for(int i=0;i<a.size();i++){
                c.a[i]= this->a[i]+b.a[i];
            }
            return c;
        }
        else{
            cout<<"operation cant be performed"<<endl;
            exit(1);
        }
   }


   matrix<T> operator-(matrix b){
        matrix<T> c(row,column,dimension);
        if(this->row==b.row && this->column==b.column){
            for(int i=0;i<a.size();i++){
                c.a[i]= this->a[i]-b.a[i];
            }
            return c;
        }
        else{
            cout<<"operation cant be performed"<<endl;
            exit(1);
        }
   }


    matrix<T> operator*(matrix b){
        matrix<T> c(this->row,b.column);
        if(this->column==b.row){
            c=c-c; // because c is constructed by random values initially so below has '+=' operator instead of '=', so it made to zero by subtracting itself

            for(int i=0;i<this->row;i++){
                for(int j=0;j<b.column;j++){
                    for(int k=0;k<this->column;k++){
                        c.a[i*this->row+j] += this->a[i*this->column+k]*b.a[k*b.column+j];
                    }
                }
            }

            
            
            return c;
        }
        else{
            cout<<"Multiplication is not possible"<<endl;
            exit(1);
        }
    }

    T* operator[](int h){
        if(h>=0 && h<this->row){
        // slicing our 1D vector based on row value 
            int index= h*(this->column);
            
            return &(a[index]);
        }
        else{
            cout<<"Unable to Access out of bound elements"<<endl;
            exit(1);
        }
       
    }
   
    
    // vector<double> operator[](int h){
    //     if(h>=0 && h<this->dimension){
    //         vector<double> s(this->row*this->column);
    //         int index = h*(this->column*this->dimension);
    //         for(int i=0;i<h.size();i++){
    //             s[i]=this
    //         }
    //     }
    // }


    matrix<T> transpose(){
        matrix<T> c(this->column,this->row);
        // for(int i=0;i<this->row;i++){
        //     for(int j=0;j<this->column;j++){
        //         c[j][i] = (*this)[i][j];
        //     }
        // }
        int k=0;
        for(int i=0;i<this->column;i++){
            for(int j=0;j<this->row;j++){
                //c.a.push_back(this->a[j*(this->column)+i]);
                c.a[k] =this->a[j*(this->column)+i];
                k++;
            }
        }
        return c;
    }

    
   double determinant() {
    if (row != column) {
        cout << "Determinant is only defined for square matrices" << endl;
        exit(1);
    }

    if (row == 1) {
        return a[0];
    }

    double det = 0;
    int sign = 1;

    for (int i = 0; i < column; i++) {
        matrix<T> submatrix(row - 1, column - 1);

        int sub_i = 0, sub_j = 0;
        for (int j = 1; j < row; j++) {
            sub_j = 0;
            for (int k = 0; k < column; k++) {
                if (k != i) {
                    submatrix.a[sub_i*(submatrix.column)+sub_j] = a[j * column + k];
                    sub_j++;
                }
            }
            sub_i++;
        }

        det += sign * a[i] * submatrix.determinant();
        sign *= -1;
    }

    return det;
}

// matrix inverse(){
//     matrix c(this->row,this->column);
//     // if(this->determinant()==0){
//     //     cout<<"A Inverse does not Exist";
//     //     exit(1);
//     // }    
//     for(int i=0;i<c.a.size();i++){
//             c.a[i]=0;
//     }

    
//     for(int i=0;i<c.row;i++){
//             c.a[i*c.column+i]=1;
//     }

//     return c;
// }



void swapRows(vector<double>& row1, vector<double>& row2) {
    swap(row1, row2);
}

matrix<double> inverse(){

//     // if(this->determinant()==0){
//     //     cout<<"A Inverse does not Exist";
//     //     exit(1);
//     // }    
//     for(int i=0;i<c.a.size();i++){
//             c.a[i]=0;
//     }
    if (row != column) {
        cout << "Matrix must be square for inversion" << endl;
        exit(1);
    }
    if(this->determinant()==0){
        cout<<"A Inverse doesn't Exist"<<endl;
        exit(1);
    }

    int n = row;
    vector<vector<double>> combinedM(n, vector<double>(2 * n)); 
    matrix<double> inv(row, column);                                         

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            combinedM[i][j] = a[i * n + j];
        }
        combinedM[i][i + n] = 1;
    }

    
    for (int i = 0; i < n; i++) {
        if (combinedM[i][i] == 0) {
            
            int j;
            for (j = i + 1; j < n; j++) {
                if (combinedM[j][i] != 0) {
                    swapRows(combinedM[i], combinedM[j]);
                    break;
                }
            }
            // if (j == n) {
            //     cout << "Matrix is not invertible" << endl;
            //     exit(1);
            // }
        }

        double pivot = combinedM[i][i];
        for (int j = i; j < 2 * n; j++) {
            combinedM[i][j] /= pivot;
        }
        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = combinedM[j][i];
                for (int k = i; k < 2 * n; k++) {
                    combinedM[j][k] -= factor * combinedM[i][k];
                }
            }
        }
    }

  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //inv.a[i*(inv.Column())+j] = combinedM[i][j + n];
            inv[i][j] = combinedM[i][j + n];
        }
    }

    return inv;
}

matrix adjoint(){
    matrix c= this->inverse();
    double d=this->determinant();
    for(int i=0;i<c.row*c.column;i++){
        c.a[i]= c.a[i]*d;
    }
    return c;
}

 

    

    // matrix operator*(matrix b){
    //     matrix c(row,column,dimension);
        
    // }


};



//matrix::matrix  operator[](int rows,int columns){



// double& operator[](int i){
//     if(i<this->row && j<column)
//     return a[(i)*(column)+j];
//     else{
//             cout<<"Trying to Access out of bound values";
//             exit(1);
//     } 
// }
int main(){
    // matrix a(2,2);
    // a.print_matrix();
    // a.print_m();
    // matrix b(2,2);
    // b.print_matrix();
    // // matrix d(3,3);
    // // d.print_matrix();
    // // matrix c=a+b+d;
    // // c.print_matrix();
    // // cout<<c(2,2);
    // matrix c=a*b;
    // matrix b(2,2);
    // b.print_matrix();
    // matrix c(2,2);
    // c.print_matrix();

    // c.print_matrix();
    // matrix d=b*c;
    // d.print_matrix();
    //auto cap = c[1][2];
   // c.print_matrix();
    //matrix a(1000,1000);
    //a.print_matrix();
    //matrix b(2,2);
    //b.print_matrix();
    //matrix d=c*a;
    //d.print_matrix();
    // c.print_matrix();
    // matrix g = c.transpose();
    // g.print_matrix();
    // cout<<g.determinant();
    //g.print_m();

    matrix<int> m(10,10);
    m.print_matrix();
    matrix<double> d = m.inverse();
    d.print_matrix();
    // m[0][0]= 5;
    // matrix<int> r(1,1);
    // r.print_matrix();
    // matrix ad =m+r;
    // ad.print_matrix();

    

    
    
    
    
    return 0;
}

