/**
* @file NHammadProject1
* @description It is a program that executes and tests matrix operations.
* @assignment BP3 Project 1
* @date 4.12.2022
* @author Nouredeen Ahmed Mahmoud Ali Hammad - nouredeen.ahmed@stu.fsm.edu.tr
*/

float *returnVector(int);
float **returnMatrix(int, int);
void freeMatrix(float **, int);
float mean(float *, int);
float correlation(float *, float *, int);
float covariance(float *, float *, int);
float **matrixMultiplication(float **, float **, int, int, int, int);
float **matrixTranspose(float **, int, int);
float *rowMeans(float **, int, int);
float *columnMeans(float **, int, int);
float **covarianceMatrix(float **, int, int);
float determinant(float **, int);
void printVector(float *, int);
void printMatrix(float **, int, int);

//EXTRA UTILITY FUNCTIONS
float* genRandomVector(int);
float** genRandomMatrix(int, int);