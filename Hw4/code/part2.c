#include <stdio.h>
#include <stdlib.h>

typedef enum _paddingType { ZERO, HALF, SAME} PaddingType;

int convolution(double inputArr[], int inputArraySize,
                double kernelArr[], int kernelArraySize,
                double outputArr[], int *outputArraySize,
                int stride, PaddingType padding);
void addPadding(double inputArr[], int inputArraySize, double outputArr[],
                int *outputArraySize, int paddingWidth,
                void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main()
{
    double inputArr[7] = {3, 5, 7, 9, 11, 13, 15};
    double kernelArr[5] = {-1, 2, 0.5, 4, 1.7};
    double outputArr[255];
    int outputArrSize = 0;

    convolution(inputArr, 7, kernelArr, 5, outputArr, &outputArrSize, 1, SAME);
    int i;
    for(i=0; i<7; i++){
        printf("%d: %.2lf\n", i, outputArr[i]);
    }
    return 0;
}


int convolution(double inputArr[], int inputArraySize,
                double kernelArr[], int kernelArraySize,
                double outputArr[], int *outputArraySize,
                int stride, PaddingType padding)
{
    int i, j, k, l;
    int paddingWidth;
    int paddingArrSize = 0;
    double paddingArr[255];

    if(kernelArraySize > inputArraySize)
    {
        return -1;
    }

    paddingWidth = ((kernelArraySize - 1)/2);
    *outputArraySize = (((inputArraySize - kernelArraySize + (2*paddingWidth)) / stride) + 1);

    switch(padding){

        case 0:
            addPadding(inputArr, inputArraySize, paddingArr, &paddingArrSize, paddingWidth, zeroPadding);
            break;

        case 1:
            addPadding(inputArr, inputArraySize, paddingArr, &paddingArrSize, paddingWidth, halfPadding);
            break;

        case 2:
            addPadding(inputArr, inputArraySize, paddingArr, &paddingArrSize, paddingWidth, samePadding);
            break;

        default:
            break;
    }

    k=0;
    l=0;
    for(i=0; i<*outputArraySize; i++)
    {
        for(j=0; j<kernelArraySize; j++)
        {
            outputArr[k] += kernelArr[j]*paddingArr[j+l];
        }
        l += stride;
        k++;
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
