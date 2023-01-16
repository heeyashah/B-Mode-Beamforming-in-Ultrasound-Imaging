#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    // set the following variables to NULL
    imparams = NULL;
    RFData = NULL;
    next = NULL;

    // set line to 0
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params, dataBuffer *data, int numline)
{
    // set the following pointers to their corresponding variables
    imparams = params;
    RFData = data;
    line = numline;

    scanline = createScanline(imparams->getNumPixel()); // invoke createScanline and assign returned array to scanline
    beamform();                                         // invoke beamform function
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); // call deleteScanline function
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem = new float[numPixel]; // create a new arrray mem of size numPixel and return mem
    return mem;
}

void BmodeClass::beamform()
{
    // intitaliza tForward, tBackward, tTotal and s to 0
    float tForward = 0;
    float tBackward = 0;
    float tTotal = 0;
    int s = 0;
    // define pReal and pImag as float type
    float pReal;
    float pImag;

    // use imparams-> to access the parameters needed for beamform

    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        tForward = (imparams->getYPosition(line, i)) / imparams->SOS; // calculation for tforward

        for (int k = 0; k < imparams->getNumElement(); k++)
        {
            tBackward = sqrt(pow(imparams->getYPosition(line, i), 2) + pow((imparams->getXPosition(line, i)) - imparams->getElementPosition(k), 2)) / imparams->SOS; // calculation for tBackward
            tTotal = tForward + tBackward;                                                                                                                           // calculation for tTotal
            s = floor(tTotal * imparams->FS);                                                                                                                        // calculation for sample number

            if (s < imparams->getNumSample()) // check condition for pReal and pImag
            {
                pReal = pReal + RFData->getRealRFData(k, s); // calculation for pReal
                pImag = pImag + RFData->getImagRFData(k, s); // calculation for pImag
            }
        }
        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2)); // calculation to determine the echo magnitude and then store the value directly into scanline array
        // reset value of pReal and pImag to 0
        pReal = 0;
        pImag = 0;
    }
}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i]; // copies content inside scanline array to data array element by element
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline; // release the memory allocated to scanline
}