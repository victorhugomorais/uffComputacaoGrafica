#include "Graphics3D.h"
#include "SimpleShader.h"
#include "transforms.h"

#include <iostream>

using namespace std;
int main()
{
    system("clear");
    mat4 P = perspective(45, 3, 1.7, 100.4);
    print(P);

    return 0;
}