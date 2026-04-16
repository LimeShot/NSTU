//-------------------------------------------------------105-07.cpp
//---------------------------------------------------1
template <class T> class S{
   T *A;
   int n,sp;
public:
   S(int n0){ n=n0; sp=-1; A=new T[n]; }
   S& operator <<(T m){
         if (sp!=n-1) A[++sp]=m;
         return *this; }
   S& operator >>(T &m){
         if (sp==-1) m=0; else m=A[sp--];
         return *this; }
   };
void main(){
   S<int> a(10);
   a << 1 << 5 << 7;
   int a1,a2,a3,a4=6;
   a >> a1 >> a2 >> a3 >> a4;
   }
//---------------------------------------------------2
template <class T,int n> class S{
   T A[n];
   int sp;
public:
   S(){ sp=-1; }
   S& operator <<(T m){
         if (sp!=n-1) A[++sp]=m;
         return *this; }
   S& operator >>(T &m){
         if (sp==-1) m=0; else m=A[sp--];
         return *this; }
   };
void main(){
   S<int,3> a;
   a << 1 << 5 << 7 << 9;
   int a1,a2,a3,a4=6;
   a >> a1 >> a2 >> a3 >> a4;
   }
//---------------------------------------------------3
template <class T> class S{
   T **A;
   int n,sp;
public:
   S(int n0){ n=n0; sp=-1; A=new T*[n]; }
   S& operator <<(T &v){
         if (sp!=n-1) A[++sp]=&v;
         return *this; }
   T *operator ()(){
         T *m=NULL;
         if (sp!=-1) m=A[sp--];
         return m; }
   };
void main(){
   S<int> a(3);
   int V[]={1,3,5,7};
   a << V[1] <<V[3] << V[0] << V[2];
   int a1,a2,*a3,*a4;
   a1=*a();
   a2=*a();
   a3=a();
   a4=a();
   }

//---------------------------------------------------4
template <class T,int n> class S{
   int A[n];
   int k;
public:
   S(){ k=0; }
   S& operator <<(T &m){
         if (k!=n) A[k++]=m;
         return *this; }
   S& operator >>(T &m){
         if (k==0) return *this;
         m=A[0];
         for (int i=0; i<k-1; i++) A[i]=A[i+1];
         k--;
         return *this; }
   };
void main(){
   S<int,10> a;
   a << 1 << 5 << 7;
   int a1,a2,a3,a4=6;
   a >> a1 >> a2 >> a3 >> a4;
   }
//---------------------------------------------------5
template <class T> class S{
   T *A;
   int n,k;
public:
   S(int n0){ n=n0; k=0; A=new T[n]; }
   S& operator <<(T m){
         if (k!=n) A[k++]=m;
         return *this; }
   T operator[](int i)
      { if (k==0 || i>=k) return 0;
      return A[i];
      }
   S& operator -(int m){
         if (k==0 || m>=k) return *this;
         for (int i=m; i<k-1; i++) A[i]=A[i+1];
         k--;
         return *this; }
   };
void main(){
   S<int> a(10); a << 1 << 5 << 7 << 9 << 11;
   int a1=a[2],a2,a3;
   a - 2 - 2;
   a2=a[2];
   a3=a[5];
   }
//---------------------------------------------------6
template <class T, int n> class S{
   T A[n];
   int k;
public:
   S(){ k=0; }
   S& operator <<(T m){
         if (k!=n) A[k++]=m;
         return *this; }
   T operator[](int i)
      { if (k==0 || i>=k) return 0;
      return A[i];
      }
   S& operator -(int m){
         if (k==0 || m>=k) return *this;
         for (int i=m; i<k-1; i++) A[i]=A[i+1];
         k--;
         return *this; }
   };
void main(){
   S<int,10> a; a << 1 << 5 << 7 << 9 << 11;

   int a1=a[2],a2,a3;
   a - 2 - 2;
   a2=a[2];
   a3=a[5];
   }
//---------------------------------------------------7
template <class T, int n> class S{
   T *A[n];
   int k;
public:
   S(){ k=0; }
   S& operator <<(T &m){
         if (k!=n) A[k++]=&m;
         return *this; }
   T *operator[](int i)
      { if (k==0 || i>=k) return NULL;
      return A[i];
      }
   S& operator -(int m){
         if (k==0 || m>=k) return *this;
         for (int i=m; i<k-1; i++) A[i]=A[i+1];
         k--;
         return *this; }
   };
void main(){
   int b[]={1,5,7,9,11};
   S<int,10> a;
   for (int i=4; i>=0; i--) a << b[i];
   int a1=*a[2],a2,a3,*p;
   a - 2 - 2;
   a2=*a[2];
   p=a[5];
   }
//---------------------------------------------------8
template <class T> class S{
   T *A;
   int n,k;
public:
   S(int n0){ n=n0; k=0; A=new T[n]; }
   S& operator <<(T m){
         int i,j;
         for (i=0; i<k && m > A[i]; i++);
         for (j=k-1; j>=i; j--) A[j+1]=A[j];
         A[i]=m; k++;
         return *this; }
   T operator[](int i)
      { if (k==0 || i>=k) return 0;
      return A[i];
      }
   };
void main(){
   S<int> a(10); a << 13 << 5 << 17 << 9 << 11;
   int a1=a[1],a2,a3;
   a2=a[2];
   a3=a[5];
   }
//---------------------------------------------------9
template <class T, int n> class S{
   T A[n];
   int k;
public:
   S(){ k=0; }
   S& operator <<(T m){
         int i,j;
         for (i=0; i<k && m > A[i]; i++);
         for (j=k-1; j>=i; j--) A[j+1]=A[j];
         A[i]=m; k++;
         return *this; }
   T operator[](int i)
      { if (k==0 || i>=k) return 0;
      return A[i];
      }
   };
void main(){
   S<int,10> a; a << 13 << 5 << 17 << 9 << 11;
   int a1=a[1],a2,a3;
   a2=a[2];
   a3=a[5];
   }
//---------------------------------------------------10
template <class T, int n> class S{
   T *A[n];
   int k;
public:
   S(){ k=0; }
   S& operator <<(T &m){
         int i,j;
         for (i=0; i<k && m > *A[i]; i++);
         for (j=k-1; j>=i; j--) A[j+1]=A[j];
         A[i]=&m; k++;
         return *this; }
   T *operator[](int i)
      { if (k==0 || i>=k) return NULL;
      return A[i];
      }
   };
void main(){
   int b[]={13,5,17,9,11};
   S<int,10> a;
   for (int i=0;i<5;i++) a << b[i];
   int a1=*a[1],a2,*p;
   a2=*a[2];
   p=a[5];
   }
