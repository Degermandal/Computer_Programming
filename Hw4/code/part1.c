#include <stdio.h>
#include <stdlib.h>

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main()
{
    double inputArr[5] = {5, 6, 7, 8, 9};
    double outputArr[255];
    int outputArrSize = 0;
    int i;
    addPadding(inputArr, 5 , outputArr, &outputArrSize, 4, halfPadding);
    for(i=0; i<13; i++){
        printf("%d: %lf\n", i, outputArr[i]);
    }
    return 0;
}


void addPadding(double inputArr[], int inputArraySize, double outputArr[], int *outputArraySize, int paddingWidth, void paddingMethod(double[], int, int))
{
    int i;

    *outputArraySize = inputArraySize + 2*paddingWidth;

    /*Copy input array to output array with paddings.*/
    for(i = 0; i<inputArraySize; i++){
        outputArr[paddingWidth+i] = inputArr[i];
    }

    paddingMethod(outputArr, *outputArraySize, paddingWidth);

}

void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
    int i, j;
    int temp;

    temp = 0;
    for(i=0; i<2; i++)
    {
        for(j=0; j<paddingWidth; j++)
        {
            outputArr[j+temp] = 0;
        }
        temp = outputArraySize - paddingWidth;
    }
}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth)
{
    int i, j;
    int temp;
    double holder;

    holder = outputArr[paddingWidth];
    temp = 0;
    for(i=0; i<2; i++)
    {
        for(j=0; j<paddingWidth; j++)
        {
            outputArr[j+temp] = holder;
        }
        temp = outputArraySize - paddingWidth;
        holder = outputArr[outputArraySize - paddingWidth - 1];
        /*printf("NUM: %d\n", (outputArraySize - paddingWidth - 1));
        printf("HOLDER: %lf\n", holder);*/
    }
}
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
    int i, j;
    int temp;
    double holder;

    holder = outputArr[paddingWidth];
    temp = 0;
    for(i=0; i<2; i++)
    {
        for(j=0; j<paddingWidth; j++)
        {
            outputArr[j+temp] = (holder/2);
        }
        temp = outputArraySize - paddingWidth;
        holder = outputArr[outputArraySize - paddingWidth - 1];
    }
}
