#include "imageParam.h"

using namespace std;

imageParam::imageParam()
{
    // set values for numElement, numSample and numScanline
    numElement = 128;
    numSample = 3338;
    numScanline = 127;

    elementPosition = genElementPosition();                                      // call genElementPosition function and assign returned Position array to elementPosition
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); // call genScanline function and assign returned 2D array scanlinePosition to scanlinePosition
}

imageParam::~imageParam()
{
    deletePositionArray(); // destructor calls the deletePositionArray to delete scanlinePosition array
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    float *Position = new float[numElement]; // define an array called Position that has numElement number of elements (128 elements)

    // for loop that starts at 0 and goes until number of elements, increasing by 1
    for (int n = 0; n < numElement + 1; n++)
    {
        Position[n] = (n - ((float(numElement) - 1.0) / 2.0)) * PITCH; // calculate the physical location for the nth element
    }
    return Position;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float *elementLocation)
{
    // prompt user to enter desired imaging depth and store it into desiredDepth
    cout << "Input desired depth: " << endl;
    cin >> desiredDepth;

    // prompt user to enter desired number of pixel and store it into numPixel
    cout << "Input desired number of pixels: " << endl;
    cin >> numPixel;

    float2 **scanlinePosition = new float2 *[numScanline]; // float array called scanlinePosition to store the results from beamform
    float depthstepsize = desiredDepth / numPixel;         // calculation for stepsize to determine the increment of the depth size to match corresponding numPixel element

    for (int i = 0; i < numScanline; i++)
    {
        scanlinePosition[i] = new float2[numPixel]; // creating a new arrya of float2 type with numPixel number of elements

        for (int j = 0; j < numPixel; j++)
        {
            scanlinePosition[i][j].x = (i - ((numScanline - 1) / 2)) * PITCH; // determine lateral position of the particular scanline
            scanlinePosition[i][j].y = depthstepsize * j;                     // determine the depth of each pixel
        }
    }
    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{

    return scanlinePosition[scanline][pixel].x; // return the x component
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y; // return the y component
}

float imageParam::getElementPosition(int element)
{

    return elementPosition[element]; // return elementPosition array at element
}

int imageParam::getNumElement()
{
    return numElement; // return numElement (private component of class imageParam)
}

int imageParam::getNumSample()
{
    return numSample; // return numSample (private component of class imageParam)
}

int imageParam::getNumScanline()
{
    return numScanline; // return numScanline (private component of class imageParam)
}

int imageParam::getNumPixel()
{
    return numPixel; // return numPixel (private component of class imageParam)
}

void imageParam::deletePositionArray()
{
    // iterate through scanlinePositon and delete all elements in the array to release the memory allocated
    for (int i = 0; i < numPixel; i++)
    {
        delete scanlinePosition[i];
    }
    // delete the arrays elementPosition and scanlinePosition
    delete elementPosition;
    delete scanlinePosition;
}
