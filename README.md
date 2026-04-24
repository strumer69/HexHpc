# HexHpc
### Experience working with linux cluster of THD Deggendorf.


This is my first step working with the HEXHPC cluster at THD Deggendorf. Let’s start with a simple C++ “Hello World” example.

link to documentation: 
https://hexhpc.th-deg.de/

## 1. Login to the Cluster

The cluster is accessible via SSH using your university LDAP account:

ssh xx12345@hexhpc.th-deg.de

## 2. Create a Simple C++ Program

Open a file using nano or vim:

nano hello.cpp

Add the following code:

#include <iostream>

int main() {
    std::cout << "Hello from HEXHPC!" << std::endl;
    return 0;
}

