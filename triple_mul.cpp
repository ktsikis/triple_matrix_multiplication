#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mc_scverify.h"
using namespace std;

static const int K = 3;
static const int L = 3;
static const int M = 4;
static const int N = 4;


#pragma hls_design top
void CCS_BLOCK(triple_matrix_mul)(short A[K][L], short B[L][M], short C[M][N], short res[K][N]){
	short temp[K][M] = {};//buffer
	
	// calculating (A*B)*C
	//calculate A*B = temp
	CALC1:for (int i = 0; i < K; i++){
		for (int j = 0; j < M; j++){
			for (int k = 0; k < L; k++){
				temp[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	
	//calculating temp*C = res
	CALC2:for (int i = 0; i < K; i++){
		for (int j = 0; j < N; j++){
			for (int k = 0; k < M; k++){
				res[i][j] += temp[i][k] * C[k][j];
			}
		}
	}
}


CCS_MAIN(int argc, char* argv[]){
	// creating random number generator for testing code
	std::srand(std::time(NULL));
	
	//define result matrix and initiate to zeros
	short result[K][N] = {};
	
	//define matrices
	short a[K][L];
	short b[L][M];
	short c[M][N];

	//initiate random matrix A
	std::cout<<endl<<"matrix A"<<endl;
	for (int i = 0; i < K; i++){
		for (int j = 0; j < L; j++){
			a[i][j] = std::rand()%20;
			std::cout<<" "<< a[i][j];
		}
		std::cout<<endl;
	}
	//initiate random matrix B
	std::cout<<endl<<"matrix B"<<endl;
	for (int i = 0; i < L; i++){
		for (int j = 0; j < M; j++){
			b[i][j] = std::rand()%20;
			std::cout<<" "<< b[i][j];
		}
		std::cout<<endl;
	}
	
	//initiate random matrix C
	std::cout<<endl<<"matrix C"<<endl;
	for (int i = 0; i < M; i++){
		for (int j = 0; j < N; j++){
			c[i][j] = std::rand()%20;
			std::cout<<" "<< c[i][j];
		}
		std::cout<<endl;
	}
	
	//run the multiplication
	triple_matrix_mul(a,b,c,result);
	
	//print Results
	std::cout<<endl<<"Results Matrix"<<endl;
	for (int i = 0; i < K; i++){
		for (int j = 0; j < N; j++){
			std::cout<<" "<< result[i][j];
		}
		std::cout<<endl;
	}
	CCS_RETURN(0);
}
