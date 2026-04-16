//-------------------------------------------1
void sort(int A[], int n){
	int *B=new int[n];
	int i1,i2,j,s,k;
	for (s=1;s<n;s*=2){			
		for(k=0; k<n; k+=2*s){		
			for(i1=k,i2=k+s,j=k; j<n && j<k+2*s;j++)
									
				if (i2>=n || i2==k+2*s || i1!=k+s && A[i1]<A[i2])
					B[j]=A[i1++];
				else
					B[j]=A[i2++];
			}
		for (j=0;j<n;j++) A[j]=B[j];
		}
	delete B;
	}					
//------------------------------------------------------2
 void sort(int in[], int n){ 
    for ( int i=1; i < n; i++) {		
		int v=in[i];						
		for (int k=0; k<i; k++)				
			if(in[k]>v) break;			
		for(int j=i-1; j>=k; j--)			 
			in[j+1]=in[j];					
		in[k]=v;								
      }}                           
//------------------------------------------------------3
 void sort(int in[],int n) {
 for ( int i=1; i<n; i++)	
	  for ( int k=i; k !=0 && in[k] < in[k-1]; k--){
      int c=in[k]; in[k]=in[k-1]; in[k-1]=c;
      }} 
//------------------------------------------------------4
void sort(int A[], int n ){
	for (int m=1; m<n; m*=2);	
	for (m/=2; m!=0; m/=2)          
	for (int k=0; k<m; k++)       
		for (int i=k+m; i<n; i+=m)		
		for (int j=i; j>=m && A[j]<A[j-m]; j-=m){
			int cc = A[j]; A[j]=A[j-m]; A[j-m]=cc;
			}
	}
//-----------------------------------------------------5
void sort(int A[], int n){
	int i,j,h;
	for (h=1; h<n/9; h=h*3+1);			
	for (;h>0;h=h/3)					
		for (i=h;i<n;i++)
			for (j=i;j>=h && A[j]<A[j-h];j-=h)
				{ int c=A[j]; A[j]=A[j-h]; A[j-h]=c; }
			}					
//------------------------------------------------------6
 void sort(int A[], int n){
	int i,found;				
    do {                             
    found =0;
    for (i=0; i<n-1; i++)
        if (A[i] > A[i+1]) {   
			int cc = A[i]; A[i]=A[i+1]; A[i+1]=cc;
            found++;                     
            }
		} while(found !=0); }            
//------------------------------------------------------7
 void sort(int A[], int n){
	int i,b,b1;						
    for (b=n-1; b!=0; b=b1) {	
		b1=0;                         
		for (i=0; i<b; i++)         
			if (A[i] > A[i+1]) {	
				int cc = A[i]; A[i]=A[i+1]; A[i+1]=cc;
				b1=i; 
				}}}
//--------------------------------------------------------8
void sort(int A[],int n){
	int z=1,a=0,b=n-1,i,last=0;			
	for (i=0;a<b;){
		if (A[i]>A[i+1]){				
		int c=A[i];A[i]=A[i+1];A[i+1]=c;
		last=i;
		}
	i+=z;							
	if (i==b || i<a) {				
		if (z>0) i=b=last;			
		else i=a=last+1;		
		z=-z;					
		}}}
//----------------------------------------------------9
void sort(int in[],int out[],int n){ 
	int i,j,cnt;
	for (i=0; i<n; i++){
		for ( cnt=0,j=0; j<n; j++){		
			if (in[j] < in[i]) cnt++;		
			else								
			if (in[j]==in[i] && j<i) cnt++;	
			}
		out[cnt]=in[i];						
		} 
	}
//------------------------------------------------------10
void sort(int a[], int n);		// любая сортировка одномерного массива
void big_sort(int A[], int N){
int max=A[0],i,j,n=sqrt(N)+1;
int **B=new int*[n];
	for (i=0; i<n; i++) B[i]=new int[n];
	for (i=0; i<N; i++) {
		B[i/n][i%n]=A[i];
		if (A[i]>max) max=A[i];			
		}
	for (j=n*n-N; j<n;j++)				
		B[n-1][j]=max+1;
	for (i=0; i<n; i++) sort(B[i],n);
	for (i=0; i<N; i++){              
		for ( int k=0, j=0; j<n; j++)		
			if (B[j][0] < B[k][0]) k=j;   
		A[i] = B[k][0];                
		for (j=1; j<n; j++) 
			B[k][j-1]=B[k][j];				
		B[k][n-1]=max+1;            
		}
	for (i=0; i<n; i++) delete []B[i];
	delete []B;
	}
//------------------------------------------------------11
void sort(int A[], int n){
	int i,i1,i2,s,k;
	for (s=1; 1; s*=2){						
		int nn=n/s;
		if (n%s!=0) nn++;					
		int n1=nn/2*s;					
		int n2=n-n1;
		if (n1<=0 || n2<=0) return;
		int *B1=new int[n1],*B2=new int[n2];
		for (i=0; i<n1; i++) B1[i]=A[i];
		for (i=0; i<n2; i++) B2[i]=A[i+n1]; 
		i1=i2=0;
		for (i=0,k=0; i<n; i++){			
			if (i1==s && i2==s)				
				k+=s,i1=0,i2=0;           
			if (i1==s || k+i1==n1) A[i]=B2[k+i2++];
			else						
			if (i2==s || k+i2==n2) A[i]=B1[k+i1++];
			else                      
			if (B1[k+i1 ] < B2[k+i2 ]) A[i]=B1[k+i1++];
			else A[i]=B2[k+i2++];
			}
		delete []B1; delete []B2; 
	}}
//----------------------------------------------------------12
void sort(int in[], int out[], int n){
	int i,j,k,max;
	for (max=in[0],i=0;i<n;i++)
		if (in[i]>max) max=in[i];
	int *cnt=new int[max+1];
	for(i=0;i<=max;i++) cnt[i]=0;
	for(i=0;i<n;i++) cnt[in[i]]++;	
	for(j=0,i=0;i<=max;i++)
		while(cnt[i]--!=0)			
			out[j++]=i;				
	}							
//------------------------------------------------------13
 void sort(int in[], int n){ 
    for ( int i=0; i < n-1; i++){			
		for ( int j=i+1, k=i; j<n; j++)		
			if (in[j] < in[k]) k=j;         
		int c=in[k]; in[k] = in[i]; in[i] = c;
		}}                             
//------------------------------------------------------14
 void sort(int in[], int a, int b){
	int i,j,mode;
	if (a>=b) return;                           
	for (i=a, j=b, mode=1; i < j; mode >0 ? j-- : i++)
		if (in[i] > in[j]){           
			int c = in[i]; in[i] = in[j]; in[j]=c;
			mode = -mode;                
			}
	sort(in,a,i-1); sort(in,i+1,b);
	}
//-----------------------------------------------------15
 void sort(int in[], int a, int b){
	int i,j,mode;
	double sr=0;
	if (a>=b) return;					
	for (i=a; i<=b; i++) sr+=in[i];
	sr=sr/(b-a+1);
	for (i=a, j=b; i <= j;){
		if (in[i]< sr) { i++; continue; }	
		if (in[j]>=sr) { j--; continue; }	
		int c = in[i]; in[i] = in[j]; in[j]=c;
		i++,j--;						
		}
	if (i==a) return;					
	sort(in,a,j); sort(in,i,b);
	}			
//--------------------------------------------------------16
void sort(int A[], int n){
	for(j=0;n!=0;j++){
    	for (k=0,i=1; i<n; i++)
		if (A[i]<A[k]) k=i;
    	B[j]=A[k];
    	for (;k<n-1;k++) A[k]=A[k+1];
    	n--;
		}
	}
//--------------------------------------------------------17
void sort(int A[], int B[], int n){
	for(j=0,max=A[0];j<n;j++) 
		if (A[j]>max) max=A[j];
	for(j=0;j<n;j++){
    	for (k=0,i=1; i<n; i++)
			if (A[i]<A[k]) k=i;
    	B[j]=A[k];
    	A[k]=max+1;
		}
	}
//--------------------------------------------------------18
void sort(int A[], int n){
	while(n!=0){
    	for (k=0,i=1; i<n; i++)
			if (A[i]<A[k]) k=i;
    	c=A[k]; A[k]=A[n-1]; A[n-1]=c;
    	n--;
		}
	}