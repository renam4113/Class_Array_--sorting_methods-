#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>

class Array
{ int *a, n;
 public:
 Array(int len = 1, int t = 1, int d = 10); 
 Array(int *, int); 
 Array(Array &);
 ~Array(){if(a) delete []a; a = NULL;};
 Array& operator = (Array &);
 int &operator [](int); 
 bool Test();
 bool operator == (Array);
 int GetLen();
 Array operator + (Array);

 void Shell_sort();
 
 void Heapsort();
 void sift2(int, int);

 int Hoar_sort_Index(int, int);
 void Hoar_sort(int low = 0 , int high = -1);

 
 void Bit_sort();
 
 friend istream & operator >> (istream &, Array &);
 friend ostream & operator << (ostream &, Array &);
};


using namespace std;

int& Array:: operator [](int i){
    if ((i < 0 || i >= n)){
        cout << "неправильный индекс";
        return a[0];
    }
    
    return a[i];
}

int Array:: GetLen(){
    return n;
}


Array& Array:: operator = (Array & arr){
    if(this != &arr){
    delete []a;
    n = arr.n;
    a = new int[n];
    for (int i = 0; i < n; i++) 
        a[i] = arr.a[i];
    }
    return *this; 
}
Array Array:: operator + (Array arr){
    Array z(arr.n + n, 1, 10);
    for(int i = 0; i  < arr.n; i++){
        z.a[i] = arr.a[i];
    }
    for(int i = arr.n; i  < arr.n + n; i++){
        z.a[i] = a[i - arr.n];
    }
    z.Shell_sort();
    return z;    
}

bool Array:: operator == (Array arr){
    if(n != arr.n) return false;
    (*this).Shell_sort(); 
    arr.Shell_sort();
    for(int i = 0; i < n; i++) if(a[i] != arr.a[i]) return false;
    return true;
}


istream & operator >> (istream & in, Array & arr){
    int A[500];
    int i = 0;
    for(; i < 500; i++) in >> A[i];
    if(arr.a) delete []arr.a;
    arr.n = i + 1;
    arr.a = new int[arr.n];
    for(int j = 0; j < arr.n; j++) arr.a[j] = A[j];
    return in;
}

ostream & operator << (ostream &out, Array &arr){
    for(int i = 0; i < arr.n; i++) out << arr.a[i] << " ";
    return out;
} 


int max(int x, int y){
    if(x >= y) return x;
    else return y;
}



Array:: Array(int len, int t, int d){
    n = len;
    a = new int[len];

    switch(t){
        case 1:
            for(int i = 0; i < len; i++) a[i] = rand() % d + 1;
        case 2:
            a[0] = rand() % d + 1;
            for(int i = 1 ; i < len ; i++) a[i] = a[i - 1] + rand() % d + 1 ;
        case 3:
            a[n - 1] = rand() % d + 1;
            for(int i = n - 2; i >= 0; ) a[i] = a[i + 1] + rand() % d + 1;
    }
}
    
Array:: Array(int *s, int len){
    n = len;
    a = new int[n];
    for(int i = 0; i < n; i++) a[i] = s[i];
}

Array:: Array(Array &s){
    n = s.n;
    a = new int[n];
    for(int i = 0; i < n; i++) a[i] = s.a[i];
}

bool Array:: Test(){
    for(int i = 0; i < n - 1; i++) if(a[i] > a[i + 1]) return -1;
    return 0;
}





void Array:: Hoar_sort(int low, int high){
        int j = high;
        if(high == -1) j = n - 1;
        if(low < j){
        int i = low;
        int pivot = a[(low + j) / 2];

        do{
            while(a[i] < pivot) i++;
            while(a[j] > pivot) j--;
            if(i <= j){
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                i++;
                j--;
            }
        }while(i <= j);

        (*this).Hoar_sort(low, j); 
        (*this).Hoar_sort(i, high); 
        } 
}



void Array:: sift2(int i, int m){
    int k = i * 2 + 1;
    int x = a[i];
    bool flag = true;
            while((k < m) && (flag)){
                if((k + 1 < m) && a[k] < a[k + 1]) k = k + 1;
                if(x < a[k]){
                    a[i] = a[k];
                    i = k;
                    k = k * 2 + 1;
                }
                else flag = false;
            }
    a[i] = x;
}

void Array:: Heapsort(){
        clock_t start, end;
        start = clock();
        for(int i = n / 2 - 1; i >= 0; i--) sift2(i,n);
        for(int len = n - 1; len >= 1; len--){
            int temp = a[len];
            a[len] = a[0];
            a[0] = temp;
            sift2(0, len);
        }
        end = clock();
        cout << ((double) (end - start)) / ((double) CLOCKS_PER_SEC) << "- время пирамидальной " << endl;
} 
 void Array:: Shell_sort(){
    clock_t start, end;
    start = clock();
    for(int d = n / 2; d > 0; d /= 2){
        for(int i = d; i < n; i++){
            int temp = a[i];
            int j = i - d;
            for(; j >= 0 && a[j] > temp; j -= d){
                a[j + d] = a[j];
                
            }
            a[j + d] = temp;
        }
    }
    end = clock();
    cout << ((double) (end - start)) / ((double) CLOCKS_PER_SEC) << "- время шелла " << endl;
}

int main(){
    Array arr(50, 1, 100); 
    cout << arr << endl;

    return 0;
}