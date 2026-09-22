#include "include/socketApp.h"
#include <iostream>

int main()
{
    // Initialize WSA
    InitializeWSAData();

    // Initialize window
    Window SocketWindow("Socket App",50,50,640,600);

    // Nothing will be run after this line
    SocketWindow.HandleEvents();
}