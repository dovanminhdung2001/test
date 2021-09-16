#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <windows.h>
#include <math.h>

int A[5][5],i,j,k,a,b;	
int r,x,y ;  

void setUpA (int A[][5]){
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			A[i][j] = 0 ;	
}

void txtColor( WORD color ) { // 	doi mau chu 
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void prin (int x){
	if (x==0) { 
		txtColor(15);
		printf("\t\t.");
	}
	else{ 
		txtColor ( ((int) (log(x)/log(2))) % 16  );
		printf("\t\t%d",x)  ; 
	}
}

int  score (int A[][5]){
	int d;
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			d +=A[i][j];
	return d;			
}

void display ( int A[][5]){
	int i,j;
	for (i=0;i<5;i++) {
		printf("\n\n\n");
		for (j=0;j<5;j++)
			prin (A[i][j]);
		printf("\n\n\n");
	}
	txtColor(15);
	printf("\n\t\t\t Score = %d",score(A));
}
	  
int  isFull (int A[][5]){	 
	for (a=0;a<5;a++)
		for (j=0;j<5;j++)
			if (A[a][j] == 0)
				return 0; 
	return 1;
}

void addNumber ( int A[][5] ){	
	
	for (i=0;i<2;i++){
		
		if ( isFull(A) )		 
			break;
		
		int x,y,r;
		r = 1 + rand() % 2; 				//	87,5% r = 1; 12.5% r = 2;
		if( r==2)						 
			r = 1 + rand() % 2;
		if( r==2)
			r = 1 + rand() % 2;			
				
		do{
			 x = 0 + rand() % 5;
			 y = 0 + rand() % 5;	
		}	while ( A[x][y] != 0 );			
		  
		A[x][y] = 2*r;							  			
	}	
}

int  colIsEmpty (int A[][5],int j){	
	for ( i=0 ; i<5 ; i++ )
		if ( A[i][j] != 0 )
			return 0;
	return 1;
}  
  
int  colIsFull (int A[][5],int j){
	for (i=0;i<5;i++)
		if ( A[i][j] == 0)
			return 0;		
	return 1;
} 

int  colIsStuck (int A[][5],int j){
	if ( !colIsFull(A,j) )
		return 0;
	else 
		for ( i=0 ; i<4 ; i++ )				
			if ( A[i][j] == A[i+1][j] )
				return 0;				
	return 1;
}

int  colCanUp (int A[][5],int j){
	if ( colIsStuck(A,j) || colIsEmpty(A,j) )
		return 0;
	for ( i=0 ; i<4 ; i++ )				
		if ( A[i][j] == A[i+1][j] && A[i][j] )	
			return 1;
	for ( i=0 ; i<4 ; i++)
		if( !A[i][j] )
			for (k=i+1;k<5;k++)
				if ( A[k][j] )
					return 1;
	return 0;				 
}

int  canUp (int A[][5]){
	for ( j=0; j<5; j++)
		if ( colCanUp(A,j) )
			return 1;
	return 0;		
}

int  colCanDown(int A[][5],int j){
	if ( colIsStuck(A,j) || colIsEmpty(A,j) )
		return 0;
	for ( i=4 ; i>0 ; i--)
		if ( A[i][j] == A[i-1][j] && A[i][j] )
			return 1;
	for ( i=4 ; i>0 ; i--)
		if ( !A[i][j] )
			for (k=i-1;k>=0;k--)
				if ( A[k][j] )
					return 1;
	return 0;							
}

int  canDown ( int A[][5] ){
	for ( j=0; j<5; j++)
		if ( colCanDown(A,j) )
			return 1;
	return 0;		
} 
  
void up  (int A[][5]) { 
	if ( canUp (A) ){
		for ( j=0 ; j<5 ; j++ ){
			if( colCanUp(A,j) ){
				
				int n=0;
				for( i=0;i<5;i++ )
					if ( A[i][j] ){
						A[n][j] = A[i][j];
						n++;
					}
				for( i=n;i<5;i++)
					A[i][j]=0;
				
				for ( i=0 ; i<4 ; i++ )
					if ( A[i][j] == A[i+1][j] && A[i][j] ){
						A[i][j] += A[i+1][j];
					    A[i+1][j] = 0;
					}	 
					
				n=0;		
			 	for( i=0;i<=4;i++ )
					if ( A[i][j] ){
						A[n][j] = A[i][j];
						n++;
					}
				for( i=n;i<=4;i++)
					A[i][j]=0; 
			}
		}
	}	
}
 
void down (int A[][5]){
	if ( canDown(A) ){
		for ( j=0 ; j<5 ; j++ ){
			if( colCanDown(A,j) ){
				
				int n=4;
				for( i=4;i>=0;i-- )
					if ( A[i][j] ){
						A[n][j] = A[i][j];
						n--;
					}
				for( i=n;i>=0;i--)
					A[i][j]=0;
				
				for ( i=4 ; i>0 ; i-- )
					if ( A[i][j] == A[i-1][j] && A[i][j] ){
						A[i][j] += A[i-1][j];
					    A[i-1][j] = 0;
					}	
					
				n=4;
				for( i=4;i>=0;i-- )
					if (A[i][j] ){
						A[n][j] = A[i][j];
						n--;
					}
				for( i=n;i>=0;i--)
					A[i][j]=0;	
			}
		}
	}
} 
 
int  rowIsEmpty (int A[][5],int i){
	for (j=0;j<5;j++)
		if ( A[i][j] != 0 )
			return 0;
	return 1;		
} 

int  rowIsFull (int A[][5], int i){
	for (j=0;j<5;j++)
		if ( A[i][j] == 0)
			return 0;
	return 1;		
}

int  rowIsStuck (int A[][5], int i){
	if ( !rowIsFull(A,i) )
		return 0;
	else	
		for ( j=0 ; j<4 ; j++ )
			if ( A[i][j] == A[i][j+1] )
				return 0;
	return 1;
}

int  rowCanLeft( int A[][5], int i){
	if ( rowIsStuck(A,i) || rowIsEmpty(A,i) )
		return 0;
	for ( j=0 ; j<4 ; j++ )				
		if ( A[i][j] == A[i][j+1] && A[i][j] )	
			return 1;
	for ( j=0 ; j<4 ; j++)
		if( !A[i][j] )
			for (k=j+1;k<5;k++)
				if ( A[i][k] )
					return 1;
	return 0;				 	
}

int  canLeft( int A[][5] ){
	for ( i=0; i<5; i++)
		if ( rowCanLeft(A,i) )
			return 1;
	return 0;			
}

int  rowCanRight( int A[][5],int i){
	if ( rowIsStuck(A,i) || rowIsEmpty(A,i) )
		return 0;
	for ( j=4; j>0; j--)
		if ( A[i][j] == A[i][j-1] && A[i][j] )
			return 1;
	for ( j=4; j>0; j--)
		if ( !A[i][j] )
			for (k=j-1;k>=0;k--)
				if ( A[i][k] )
					return 1;
	return 0;				
}

int  canRight ( int A[][5]){
	for ( i=0; i<5; i++)
		if ( rowCanRight(A,i) )
			return 1;
	return 0;		
}

void left ( int A[][5] ){
	if ( canLeft (A) ){
		for ( i=0 ; i<5 ; i++){
			if ( rowCanLeft(A,i)  ){
				
				int n=0;
				for ( j=0 ; j<5 ; j++ )
					if ( A[i][j] ){
						A[i][n] = A[i][j];
						n++;
					}
				for ( j=n ; j<5 ; j++)	
					A[i][j] = 0;
					
				for ( j=0 ; j<4 ; j++ )
					if ( A[i][j] == A[i][j+1] && A[i][j] ){
						A[i][j] += A[i][j+1];
					    A[i][j+1] = 0;
					}	 	
					
				n=0;
				for ( j=0 ; j<5 ; j++ )
					if ( A[i][j] ){
						A[i][n] = A[i][j];
						n++;
					}
				for ( j=n ; j<5 ; j++)	
					A[i][j] = 0;	
			}
		}	
	}
}

void right (int A[][5] ){
	if ( canRight(A) ){
		for ( i=0 ; i<5 ; i++ ){
			 if ( rowCanRight(A,i) ){
			 	
			 	int n=4;
			 	for ( j=4; j>=0; j--)
			 		if( A[i][j]){
			 			A[i][n] = A[i][j];
			 			n--;
					 }	
				for ( j=n; j>=0; j--)	 
					 A[i][j]=0;
					 				 
				for ( j=4; j>0; j--)
					if ( A[i][j] == A[i][j-1] && A[i][j] ){
						A[i][j] += A[i][j-1];
						A[i][j-1] = 0;	
					}
					
				n=4;	
				for ( j=4; j>=0; j--)
					if (A[i][j] ){
						A[i][n] = A[i][j];
						n--;
					}
				for ( j=n; j>=0; j--)	 
					 A[i][j]=0;				 
			 }
		}
	}
}

int canMove (int A[][5]){
	
	for (k=0;k<5;k++)
		if ( rowCanLeft(A,k) || rowCanRight(A,k) || colCanUp(A,i) || colCanDown(A,i) )
			return 1;
	return 0;			
}	

int  readMove (int A[][5]){
	
	fflush(stdin);
	char select;
	
	while(1){			
		select = getch();
		if (select == 27)
 			break;		
		if (select == -32)	{			
		 	select = getch();
			break; 	
		}
	}
	return select;			
}

void playGame (int A[][5]){
	
	setUpA(A);	
	addNumber(A);
	display(A);
	
	do{
			int move = readMove(A);
			switch ( move ){
				case 72: 
					if ( canUp(A) ){
						up(A); 
						addNumber(A);
						break;
					}
					 
						
				case 80: 
					if ( canDown(A) ){
						down(A); 
						addNumber(A);
						break;
					} 
								
				case 75: 
					if ( canLeft(A) ){
						left(A); 
						addNumber(A);
						break;
					}
							
				case 77 : 
					if ( canRight(A) ){
						right(A); 
						addNumber(A); 
						break;
					} 								 
			} 			
			system("cls");
			display(A);
	}	while (  canMove(A) && readMove(A) != 27  ) ;
	
	system("cls");
	getch();getch(); 
	display(A);	
	printf("\t\tYou lose!!");
}

void main(){
 	playGame(A);
}
	
	
	
	 
 