/**
* @file NHammadProject1
* @description It is a program that executes and tests matrix operations.
* @assignment BP3 Project 1
* @date 4.12.2022
* @author Nouredeen Ahmed Mahmoud Ali Hammad - nouredeen.ahmed@stu.fsm.edu.tr
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrixLib.h"

//Allocates and returns a vector (1 dimension array) of specified size with values of 0
float *returnVector(int size){
    float *result = (float*)calloc(size, sizeof(float));
    return result;
}


//Allocates and returns a matrix (2 dimension array) of specified row and column number with values of 0
float **returnMatrix(int row, int col){
    float **result = (float**)calloc(row, sizeof(float*));

    for (int i = 0; i < row; i++){
        result[i] = (float*)calloc(col, sizeof(float));
    }
    
    return result;
}

//Frees the specified matrix from the heap and returns it back to the system
void freeMatrix(float **mat, int row){
    for (int i = 0; i < row; i++){
        free(mat[i]);
    }
    free(mat);
}

//Calculates and returns the mean of the specified vector
float mean(float *vec, int size){
    float sum = 0;
    for (int i = 0; i < size; i++){
        sum += vec[i];
    }
    float mean = sum/size;
    return mean;
}

//Calculates and returns the correlation between two vectors
float correlation(float *vec1, float *vec2, int size){
    
    float cov_12 = covariance(vec1,vec2,size);
    float var_1 = covariance(vec1,vec1,size);
    float var_2 = covariance(vec2,vec2,size);

    float stdev_1 = sqrt(var_1);
    float stdev_2 = sqrt(var_2);
    
    float result = cov_12/(stdev_1*stdev_2);
    
    return result;
}

//Calculates and returns the covariance between two vectors
float covariance(float *vec1, float *vec2, int size){
    float result = 0;
    float mean1 = mean(vec1,size);
    float mean2 = mean(vec2,size);
    for (int i = 0; i < size; i++){
        result += (vec1[i] - mean1) * (vec2[i] - mean2);
    }
    result = result/size;
    return result;
}

//Performs matrix multiplication and returns result
float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2){
    float** result = (float**) returnMatrix(row1,col2);
    float temp;

    for (int i = 0; i < row1; i++){
        for (int j = 0; j < col2; j++){
            temp = 0;
            for (int k = 0; k < col1; k++){
                temp += mat1[i][k] * mat2[k][j];
            }
            result[i][j] = temp;
        }
    }
    return result;
}

//Returns the transpose matrix of the specified matrix
float **matrixTranspose(float **mat, int row, int col){
    float** result = returnMatrix(col,row);
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            result[j][i] = mat[i][j];
        }
    }
    return result;
}

//Finds the means of each "j"th element in each row and returns them in a vector
float *rowMeans(float **mat, int row, int col){
    float sumOfColumn;
    float* result = calloc(col,sizeof(float));

    for (int j = 0; j < col; j++){
        // resets the sum of column when switching to the next column
        sumOfColumn = 0;
        for (int i = 0; i < row; i++){
            sumOfColumn += mat[i][j];
        }
        result[j] = sumOfColumn/row;
    }
    return result;
}

//Finds the means of each row and returns them in a vector
float *columnMeans(float **mat, int row, int col){
    float sumOfRow;
    float* result = calloc(row,sizeof(float));

    for (int i = 0; i < row; i++){
        //resets the sum of row when switching to the next row
        sumOfRow = 0;
        for (int j = 0; j < col; j++){
            sumOfRow += mat[i][j];
        }
        result[i] = sumOfRow/col;
    }
    return result;
}

//Takes the matrix and its dimensions as parameters, then returns the variance covariance matrix of this matrix (by column)
float **covarianceMatrix(float **mat, int row, int col){

    //Gets the column mean vector
    float *rowMeanVector = rowMeans(mat, row, col);

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            //Subtracts the average of the column to which it belongs from each element
            mat[i][j] -= rowMeanVector[j];
        }
    }

    float **transpose = matrixTranspose(mat, row, col);                        
    float **covMat = matrixMultiplication(transpose, mat, col, row, row, col); 

    freeMatrix(transpose, col);
    free(rowMeanVector);

    for (int i = 0; i < col; i++){
        for (int j = 0; j < col; j++){
            covMat[i][j] /= row;
        }
    }

    return covMat;
}

//Calculates and returns the determinant of the specified matrix
float determinant(float **mat, int row){

    //Expands current matrix and allocates memory for it
    for (int i = 0; i < row; i++){
        mat[i] = (float*) realloc(mat[i], 5*sizeof(float));
    }
    
    //Fills in the expanded part of the matrix according to sarrus' determinant rule
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++){
            mat[i][j+3] = mat[i][j];
        }
    }

    //Calculates the determinant with Sarrus' rule
    float result = 0;
    for (int i = 0; i < 3; i++){
        result += mat[0][i] * mat[1][i+1] * mat[2][i+2];
        result -= mat[2][i] * mat[1][i+1] * mat[0][i+2];
    }
    
    return result;
}

//Prints all the specified vector's elements to the console
void printVector(float *vec, int N){
    for (int i = 0; i < N; i++){
        printf("%.3f    ",vec[i]);
    }
}

//Prints all the specified matrix's elements to the console
void printMatrix(float **mat, int row, int col){

    for (int i = 0; i < row; i++){
        
        for (int j = 0; j < col; j++){
            printf("%.3f    ", mat[i][j]);
        }

        printf("\n");
    }
}

//////////// EXTRA UTILITY FUNCTIONS ////////////

//creates matrix and fills it with values randomly between 0 and 9
float** genRandomMatrix(int row, int col){
    float** result = returnMatrix(row,col);
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            result[i][j] = rand()%10;
        }
    }
    return result;
}

//creates vector and fills it with values randomly between 0 and 9
float* genRandomVector(int size){
    float* result = returnVector(size);
    for (int i = 0; i < size; i++){
        result[i] = rand()%10;
    }
    return result;
}
