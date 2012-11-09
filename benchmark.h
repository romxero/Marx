//benchmarkData
 #include <time.h>

int queenP(int N, char chessBoard[N][N], int count, int *externalCounter);
void displayChessBoard(int N, char chessBoard[N][N]);
void splayBoard(int i,int k, int N, char chessBoard[N][N]);
void copyBoard(int N, char chessBoard[N][N],char duplicateBoard[N][N]);
void setChessBoard(int N, char chessBoard[N][N]);
int benchMark();

int benchMark()
{
     clock_t start, end; //start and stop variables
     double cpu_time_used;
     int N = 8;
		char board[N][N]; //this is the multidemensional board right here
		int mainCounter = 0;
		
		int internalCounter = 0; //set this up so its zero to begin with
     setChessBoard(N, board); //set up the chess board
     start = clock(); //start the clock
		/* Do the work. */
		
		
	
		queenP(N, board, internalCounter,&mainCounter); //there is a stack overflow WTF~!!
		
     end = clock(); //end the clock
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; //cpu time for the clock
	
	
	
	return (int) cpu_time_used;
	
	
}



void setChessBoard(int N, char chessBoard[N][N])
{
	int i, k;
	i = k = 0; //set the values in order to process them 
	for (i = 0; i < N; ++i)
	{
			for (k = 0; k < N; ++k)
			{
				chessBoard[i][k] = '-'; //assign them all the character '-'//
				
			}
		
	}
}


int queenP(int N, char chessBoard[N][N], int count, int *externalCounter)
{
	 if (count == N)
	{
		++*externalCounter;
		
		
	}
	
	else
	{
	
			++count;
			
				
		int i, k; //counter for the  FSM 
		 
		 i = k = 0;

		for (i = 0; i < N; ++i)
		{
			for (k = 0; k < N; ++k)
			{
					if (chessBoard[i][k] == '-')
					{
						char duplicateBoard[N][N];
						copyBoard(N, chessBoard, duplicateBoard);
						duplicateBoard[i][k] = 'Q';
						splayBoard(i,k,N,duplicateBoard);
						//~ displayChessBoard(N, duplicateBoard);
						
						//~ printf("__________________________\n"); //seperate each chessboard
						//~ printf("Created by Randy White\n\n"); //seperate each chessboard
						//~ sleep(2);
					//	break;
						 
						 queenP(N, duplicateBoard,count,externalCounter);
						 
					}
				
			
				//break; //temporary
			}

			
		}
}

}
//duplicate below used to view the nqueens problem

void displayChessBoard(int N, char chessBoard[N][N])
{

		
int i, k; //counter for the  FSM 
 
 i = k = 0;

for (i = 0; i < N; ++i)
{
	for (k = 0; k < N; ++k)
	{
		printf("%c",chessBoard[i][k]); //just a regular output of whats going on
		if (k == ( N - 1))
		{
				printf("\n");
		}
		//something here
	
	}
		

}


}

void copyBoard(int N, char chessBoard[N][N],char duplicateBoard[N][N])
{
	
	int i, k; //counter for the  FSM 
 
 i = k = 0;

for (i = 0; i < N; ++i)
{
	for (k = 0; k < N; ++k)
	{
		duplicateBoard[i][k] = chessBoard[i][k];

	}


}
	
}


void splayBoard(int i,int k, int N, char chessBoard[N][N])
{
		
		int m, n, o, p;
		m = n = o = p = 0;
		for (n = 0; n < N; ++n)
		{
			if ( n != k)
			{
				chessBoard[i][n] = '*';
			}
			
			
		}
		
		for (m = 0; m < N; ++m)
		{
			if ( m != i)
			{
				chessBoard[m][k] = '*';
			}
		}
		
		m = n = o = p = 0;
		o = p = k;
		
		m = n = i;
		
		for (; n < N; ++n)
		{
			if (!(o > N))
			{
				if (chessBoard[n][o] != 'Q')
				{
					chessBoard[n][o] = '*';
				}
				++o;
			}
			
			if (!(p < 0))
			{
				if (chessBoard[n][p] != 'Q')
				{
				chessBoard[n][p] = '*';
				}
				--p;
				
			}
			
		}
		
		o = p = k;		
	
	for (; m >= 0; --m)
	{
		if (!(o > N))
			{
				if (chessBoard[m][o] != 'Q')
				{
					chessBoard[m][o] = '*';
				}
				++o;
			}
			
			if (!(p < 0))
			{
				if (chessBoard[m][p] != 'Q')
				{
				chessBoard[m][p] = '*';
				}
				--p;
				
			}
		
		
	}
	
		//~ for (; i < N; ++i)
		//~ {
						//~ for (; (k+1) < N; ++k)
						//~ {
							//~ chessBoard[i][k] = '*';
							//~ 
							//~ 
						//~ }
					//~ 
		//~ }
	
	
}
