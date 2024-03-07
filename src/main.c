/**
* @file NHammadProject2
* @description It is a program that reads the Iris.csv file, makes calculations and writes the results in a file.
* @assignment BP3 Project 2
* @date 24.12.2022
* @author Nouredeen Ahmed Mahmoud Ali Hammad - nouredeen.ahmed@stu.fsm.edu.tr
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrixLib.h"

// Define a struct to represent an Iris
typedef struct{
    int id;
    float sepalLengthCm;
    float sepalWidthCm;
    float petalLengthCm;
    float petalWidthCm;
    int species;
} Iris;

// Function to map species names to integer values
int getSpecies(char* input){
    if(strcmp("Iris-setosa",input) == 0){
        return 1;
    } else if(strcmp("Iris-versicolor",input) == 0){
        return 2;
    } else if(strcmp("Iris-virginica",input) == 0){
        return 3;
    } else {
        return -1;
    }
}

int main(){

    // Opens the CSV file for reading
    FILE *file;
    file = fopen("./Iris.csv","r");

    // Checks if file was successfully opened
    if(file==NULL){
        printf("File couldn't be opened");
        exit(1);
    }

    // Reads the number of records in the file
    int noOfRecords;
    fscanf(file,"%d",&noOfRecords);

    // Allocates dynamic memory to store the iris data
    Iris* data = (Iris*)malloc(noOfRecords*sizeof(Iris));

    // Moves the cursor 2 lines down
    char buff[100];
    fgets(buff,100,file);
    fgets(buff,100,file);

    // Reads the data from the file and store it in the array of Iris objects
    for (int i = 0; i < noOfRecords; i++){
        int id;
        float sl,sw,pl,pw;
        char sp[50];
        fscanf(file,"%d,%f,%f,%f,%f,%s",&id,&sl,&sw,&pl,&pw,&sp);
        fgets(buff,100,file);

        data[i].id = id;
        data[i].sepalLengthCm = sl;
        data[i].sepalWidthCm = sw;
        data[i].petalLengthCm = pl;
        data[i].petalWidthCm = pw;
        data[i].species = getSpecies(sp);
    }

    // Closes the file
    fclose(file);


    // Fills the data matrix with data
    float** dataMatrix = returnMatrix(noOfRecords,4);
    
    for (int i = 0; i < noOfRecords; i++){
        dataMatrix[i][0] = data[i].sepalLengthCm;
        dataMatrix[i][1] = data[i].sepalWidthCm;
        dataMatrix[i][2] = data[i].petalLengthCm;
        dataMatrix[i][3] = data[i].petalWidthCm;
    }

    // Takes the transpose of the matrix
    float** dataMatrixTrans = matrixTranspose(dataMatrix,noOfRecords,4);

    // Calculates the mean values for each property
    float sepalLengthMean = mean(dataMatrixTrans[0],noOfRecords);
    float sepalWidthMean = mean(dataMatrixTrans[1],noOfRecords);
    float petalLengthMean = mean(dataMatrixTrans[2],noOfRecords);
    float petalWidthMean = mean(dataMatrixTrans[3],noOfRecords);

    // Calculates the variance values for each property
    float sepalLengthVar = covariance(dataMatrixTrans[0],dataMatrixTrans[0],noOfRecords);
    float sepalWidthVar = covariance(dataMatrixTrans[1],dataMatrixTrans[1],noOfRecords);
    float petalLengthVar = covariance (dataMatrixTrans[2],dataMatrixTrans[2],noOfRecords);
    float petalWidthVar = covariance(dataMatrixTrans[3],dataMatrixTrans[3],noOfRecords);

    // Calculates the correlation values for between sepal length and width, petal length and width, 
    // sepal and petal length, sepal and petal width
    float sepalLWCor = correlation(dataMatrixTrans[0],dataMatrixTrans[1],noOfRecords);
    float petalLWCor = correlation(dataMatrixTrans[2],dataMatrixTrans[3],noOfRecords);
    float sepalPetalLCorr = correlation(dataMatrixTrans[0],dataMatrixTrans[2],noOfRecords);
    float sepalPetalWCorr = correlation(dataMatrixTrans[1],dataMatrixTrans[3],noOfRecords);

    // Calculates the covariance matrix
    float** covMat = covarianceMatrix(dataMatrix,noOfRecords,4);
    
    // Converting calculation results to Strings
    char sepalLengthMeanS[20]; sprintf(sepalLengthMeanS,"%f",sepalLengthMean);
    char sepalWidthMeanS[20]; sprintf(sepalWidthMeanS,"%f",sepalWidthMean);
    char petalLengthMeanS[20]; sprintf(petalLengthMeanS,"%f",petalLengthMean);
    char petalWidthMeanS[20]; sprintf(petalWidthMeanS,"%f",petalWidthMean);

    char sepalLengthVarS[20]; sprintf(sepalLengthVarS,"%f",sepalLengthVar);
    char sepalWidthVarS[20]; sprintf(sepalWidthVarS,"%f",sepalWidthVar);
    char petalLengthVarS[20]; sprintf(petalLengthVarS,"%f",petalLengthVar);
    char petalWidthVarS[20]; sprintf(petalWidthVarS,"%f",petalWidthVar); 

    char sepalLWCorS[20]; sprintf(sepalLWCorS,"%f",sepalLWCor);
    char petalLWCorS[20]; sprintf(petalLWCorS,"%f",petalLWCor);
    char sepalPetalLCorrS[20]; sprintf(sepalPetalLCorrS,"%f",sepalPetalLCorr);
    char sepalPetalWCorrS[20]; sprintf(sepalPetalWCorrS,"%f",sepalPetalWCorr);

    // Converts the covariance matrix to a string
    char covMatS[200];

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            char temp[20];
            sprintf(temp,"%f",covMat[i][j]);
            strcat(temp,"\t");
            strcat(covMatS,temp);
        }
        strcat(covMatS,"\n");
    }

    // Opens the file to write
    FILE* exportFile = fopen("IrisStatistic.txt", "w");
    
    // Checks if the file was successfully opened
    if (exportFile == NULL){
        printf("File couldn't be opened\n");
        return 0;
    }

    // Arranges with concatination the string that will be written to the export file
    char output[5000];
    strcat(output,"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    strcat(output,"\nSepal Length Mean = "); strcat(output, sepalLengthMeanS);
    strcat(output,"\nSepal Width Mean = "); strcat(output, sepalWidthMeanS);
    strcat(output,"\nPetal Length Mean = "); strcat(output, petalLengthMeanS);
    strcat(output,"\nPetal Width Mean = "); strcat(output, petalWidthMeanS);
    strcat(output,"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    strcat(output,"\nSepal Length Variance = "); strcat(output, sepalLengthVarS);
    strcat(output,"\nSepal Width Variance = "); strcat(output, sepalWidthVarS);
    strcat(output,"\nPetal Length Variance = "); strcat(output, petalLengthVarS);
    strcat(output,"\nPetal Width Variance = "); strcat(output, petalWidthVarS);
    strcat(output,"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    strcat(output,"\nCorrelation between Sepal Length and Width = "); strcat(output, sepalLWCorS);
    strcat(output,"\nCorrelation between Petal Length and Width = "); strcat(output, petalLWCorS);
    strcat(output,"\nCorrelation between the lengths of sepal and petal = "); strcat(output, sepalPetalLCorrS);
    strcat(output,"\nCorrelation between the widths of sepal and petal = "); strcat(output, sepalPetalWCorrS);
    strcat(output,"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    strcat(output,"\nCovariance Matrix of the values:\n"); strcat(output,covMatS);
    strcat(output,"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

    // Writes the result string to IrisStatistic.txt file
    fprintf(exportFile, output);
    
    // Closes the file
    fclose(exportFile);
    
    return 0;
} 