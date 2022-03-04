#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> Multiply(vector<vector<int>> mat1, vector<vector<int>> mat2, int Size){
    vector<vector<int>> result;
    for(int i = 0; i < Size; i++){
        vector<int> vec;
        for(int j = 0; j < Size; j++){
            int sum = 0;
            for(int k = 0; k < Size; k++){
                sum += mat1[i][k]*mat2[k][j];
            }
            vec.push_back(sum);
        }
        result.push_back(vec);
    }
    return result;
}

void Matrix_Sum(int N, vector<vector<int>>& MatrixA, vector<vector<int>>& MatrixB, vector<vector<int>>& Sum_Matrix){

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			Sum_Matrix[i][j] = MatrixA[i][j] + MatrixB[i][j];
		}
	}
}

void Matrix_Sub(int N, vector<vector<int>>& MatrixA, vector<vector<int>>& MatrixB, vector<vector<int>>& Sub_Matrix){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			Sub_Matrix[i][j] = MatrixA[i][j] -MatrixB[i][j];
		}
	}
}

void Matrix_Mul(int N, vector<vector<int>>& MatrixA, vector<vector<int>>& MatrixB, vector<vector<int>>& Mul_Matrix){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			Mul_Matrix[i][j] = 0;
			for (int k = 0; k < N; k++){
				Mul_Matrix[i][j] += MatrixA[i][k] * MatrixB[k][j];
			}
		}
	}
}

void Strassen(int N, vector<vector<int>>& MatrixA, vector<vector<int>>& MatrixB, vector<vector<int>>& MatrixC){
    vector<int> v0(N/2, 0);
	
	vector<vector<int>> MatrixA11(N/2 ,v0);
	vector<vector<int>> MatrixA12(N/2, v0);
	vector<vector<int>> MatrixA21(N/2, v0);
	vector<vector<int>> MatrixA22(N/2, v0);

	vector<vector<int>> MatrixB11(N/2, v0);
	vector<vector<int>> MatrixB12(N/2, v0);
	vector<vector<int>> MatrixB21(N/2, v0);
	vector<vector<int>> MatrixB22(N/2, v0);

	vector<vector<int>> MatrixC11(N/2, v0);
	vector<vector<int>> MatrixC12(N/2, v0);
	vector<vector<int>> MatrixC21(N/2, v0);
	vector<vector<int>> MatrixC22(N/2, v0);
	
	
	 
	for (int i = 0; i < N / 2; i++){
		for (int j = 0; j < N / 2; j++){
			MatrixA11[i][j] = MatrixA[i][j];
			MatrixA12[i][j] = MatrixA[i][j + N / 2];
			MatrixA21[i][j] = MatrixA[i + N / 2][j];
			MatrixA22[i][j] = MatrixA[i + N / 2][j + N / 2];

			MatrixB11[i][j] = MatrixB[i][j];
			MatrixB12[i][j] = MatrixB[i][j + N / 2];
			MatrixB21[i][j] = MatrixB[i + N / 2][j];
			MatrixB22[i][j] = MatrixB[i + N / 2][j + N / 2];
		}
	}
   
	vector<vector<int>> MatrixS1(N/2, v0);
	vector<vector<int>> MatrixS2(N/2, v0);
	vector<vector<int>> MatrixS3(N/2, v0);
	vector<vector<int>> MatrixS4(N/2, v0);
	vector<vector<int>> MatrixS5(N/2, v0);
	vector<vector<int>> MatrixS6(N/2, v0);
	vector<vector<int>> MatrixS7(N/2, v0);
	vector<vector<int>> MatrixS8(N/2, v0);
	vector<vector<int>> MatrixS9(N/2, v0);
	vector<vector<int>> MatrixS10(N/2, v0);
	
	

	Matrix_Sub(N/2, MatrixB12, MatrixB22, MatrixS1);
	Matrix_Sum(N / 2, MatrixA11, MatrixA12, MatrixS2);
	Matrix_Sum(N / 2, MatrixA21, MatrixA22, MatrixS3);
	Matrix_Sub(N / 2, MatrixB21, MatrixB11, MatrixS4);
	Matrix_Sum(N / 2, MatrixA11, MatrixA22, MatrixS5);
	Matrix_Sum(N / 2, MatrixB11, MatrixB22, MatrixS6);
	Matrix_Sub(N / 2, MatrixA12, MatrixA22, MatrixS7);
	Matrix_Sum(N / 2, MatrixB21, MatrixB22, MatrixS8);
	Matrix_Sub(N / 2, MatrixA11, MatrixA21, MatrixS9);
	Matrix_Sum(N / 2, MatrixB11, MatrixB12, MatrixS10);

	
	vector<vector<int>> MatrixP1(N/2, v0);
	vector<vector<int>> MatrixP2(N/2, v0);
	vector<vector<int>> MatrixP3(N/2, v0);
	vector<vector<int>> MatrixP4(N/2, v0);
	vector<vector<int>> MatrixP5(N/2, v0);
	vector<vector<int>> MatrixP6(N/2, v0);
	vector<vector<int>> MatrixP7(N/2, v0);


	Matrix_Mul(N / 2, MatrixA11, MatrixS1, MatrixP1);
	Matrix_Mul(N / 2, MatrixS2, MatrixB22, MatrixP2);
	Matrix_Mul(N / 2, MatrixS3, MatrixB11, MatrixP3);
	Matrix_Mul(N / 2, MatrixA22, MatrixS4, MatrixP4);
	Matrix_Mul(N / 2, MatrixS5, MatrixS6, MatrixP5);
	Matrix_Mul(N / 2, MatrixS7, MatrixS8, MatrixP6);
	Matrix_Mul(N / 2, MatrixS9, MatrixS10, MatrixP7);

	
	Matrix_Sum(N / 2, MatrixP5, MatrixP4, MatrixC11); 
	Matrix_Sub(N / 2, MatrixC11, MatrixP2, MatrixC11);
	Matrix_Sum(N / 2, MatrixC11, MatrixP6, MatrixC11);
	Matrix_Sum(N / 2, MatrixP1, MatrixP2, MatrixC12);
	Matrix_Sum(N / 2, MatrixP3, MatrixP4, MatrixC21);	
	Matrix_Sum(N / 2, MatrixP5, MatrixP1, MatrixC22);	
	Matrix_Sub(N / 2, MatrixC22, MatrixP3, MatrixC22);
	Matrix_Sub(N / 2, MatrixC22, MatrixP7, MatrixC22);
	
	for (int i = 0; i < N / 2; i++){
		for (int j = 0; j < N / 2; j++){
			MatrixC[i][j] = MatrixC11[i][j];
			MatrixC[i][j+N/2] = MatrixC12[i][j];
			MatrixC[i+N/2][j] = MatrixC21[i][j];
			MatrixC[i+N/2][j+N/2] = MatrixC22[i][j];
		}
	}
}

void MatInput(vector<vector<int>>& mat, int Size){
    for(int i = 0; i < Size; i++){
        vector<int> vec;
        for(int j = 0; j < Size; j++){
            int num;
            cin >> num;
            vec.push_back(num);
        }
        mat.push_back(vec);
    }
}

void MatOutput(vector<vector<int>>& mat, int Size){
    for(int i = 0; i < Size; i++){
        for(int j = 0; j < Size-1; j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<mat[i][Size-1]<<endl;
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<vector<int>>> allMat;
    for(int i = 0; i < 2*n; i++){
        vector<vector<int>> mat;
        MatInput(mat, m);
        allMat.push_back(mat);
    }

    vector<vector<vector<int>>> result;
    for(int i = 0; i < 2*n; i += 2){
        vector<int> tempVec(m,0);
        vector<vector<int>> resultMat(m,tempVec);
        Strassen(m,allMat[i], allMat[i+1], resultMat);
        result.push_back(resultMat);
    }


    for(int i = 0; i < n; i++){
        MatOutput(result[i], m);
    }
    
    return 0;
}