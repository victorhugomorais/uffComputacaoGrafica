//victor hugo morais, leandro bucci e matheus casagrande
//aula 11 lookat
#include <iostream>
#include "transforms.h"
#include "Graphics2D.h"

using namespace std;
int main()
{
    system("clear");
    vec3 O = {2, 5, 2}, C = {0, 0, 0}, Up = {0, 2, 0};
    mat4 View = lookAt(O, C, Up);
    print(View);

    return 0;
}