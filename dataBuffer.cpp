#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer() // default constructor
{
    // initializing the following variables to 0
    numElement = 0;
    numSample = 0;
    scanline = 0;

    // initializing the following variables to NULL
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;

    dataMatrix = createDataMatrix();                      // call create data matrix function
    int num = loadRFData(dataMatrix, imagFile, realFile); // call loadRFData function
}

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // destructor calls deleteDataMatrix function to release the data stored in dataMatrix
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData;                   // define a double pointer RFData of type complex
    RFData = new complex *[numElement]; // create a new pointer of type complex with numElement elements

    for (int i = 0; i < numElement; i++)
    {
        RFData[i] = new complex[numSample]; // creates a new complex array for each numElement
    }
    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile)
{
    const int NUMLENGTH = 100; // set NUMLENGTH to 100 (for max length)
    char temp[NUMLENGTH];      // create a temporary character variable

    for (int i = 0; i < numElement; i++)
    {
        for (int j = 0; j < numSample; j++)
        {
            imagFile->getline(temp, NUMLENGTH); // open the imaginary text file
            RFData[i][j].imag = atof(temp);     // converts each charcter array to float and then stores it in corresponding RFData array

            realFile->getline(temp, NUMLENGTH); // open the real text file
            RFData[i][j].real = atof(temp);     // converts each charcter array to float and then stores it in corresponding RFData array
        }
    }

    // returns an error if the function fails to retrieve the imaginary text file or the real text file
    if (imagFile->fail() || realFile->fail())
    {
        return -1;
    }
    return 0;
}

float dataBuffer::getRealRFData(int element, int sample)
{
    return dataMatrix[element][sample].real; // returns the real component of the data that is stored
}
float dataBuffer::getImagRFData(int element, int sample)
{
    return dataMatrix[element][sample].imag; // returns the imaginary component of the data that is stored
}

void dataBuffer::deleteDataMatrix()
{
    // iterate through dataMatrix and delete all elements of the array and delete the array
    for (int i = 0; i < numElement; i++)
    {
        delete dataMatrix[i];
    }
    delete dataMatrix;
}