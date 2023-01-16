
    }

    // Read data from files into dataBuffer objects
    dataBuffer *dataHead = new dataBuffer(imagFile, realFile, parameters->getNumElement(), parameters->getNumSample(), 0); // Create head node
    dataHead->next = NULL;                                                                                                 // Initialize head node "next" attibute
    dataBuffer *currentData = dataHead;                                                                                    // Initialize current data pointer
    for (int i = 1; i < parameters->getNumScanline(); i++)
    {
        currentData->next = new dataBuffer(imagFile, realFile, parameters->getNumElement(), parameters->getNumSample(), i); // Create new node and assign address to current node "next" attribute
        currentData = currentData->next;                                                                                    // Point current node to newly created node
