#include<iostream>
using namespace std;

const int MAX=100;
struct List{
    int data[MAX];
    int H, R;
};
bool isEmpty(List L){
    return (L.H == -1 && L.R == -1); 
}
bool isFull(List L){
    return (L.H==0 && L.R == MAX-1);
}

void Init(List & L){
    L.H = L.R = -1;
}
void show(List L){
    if (!isEmpty(L))
    for (int j=L.H;j<=L.R;j++)
        cout<<L.data[j]<<" ";
    cout<<endl;
}
void Insert(List&L, int k, int i){
    if (isFull(L)) return;
    if (isEmpty(L)){
        int m = MAX/2;
        L.data[m] = k;
        L.H=L.R = m;
    }else {//list is normal before insert
        //if L.R = MAX-1 then left shift must be done
        //else if i<(L.R-L.H+1)/2 then left shift
        //      else right shift
        if (L.R == MAX-1 || i<(L.R-L.H+1)/2){
            for (int j=L.H;j<=L.H+i-2;j++)
                L.data[j-1]=L.data[j];
            L.data[L.H+i-2] = k;
            L.H--;
        }
        else {
            for (int j=L.R;j>=L.H+i-1;j--)
            L.data[j+1]= L.data[j];
            L.data[L.H+i-1] = k;
            L.R++;
        }
    }
}

int main(){
    List L;
    Init(L);
    show(L);
    Insert(L, 10, 1);
    show(L);
    Insert(L, 20, 1);
    show(L);
}
