#include "vec3.h"
#include <iostream>

int main(){
    vec3 a = vec3(1.1f,2.1f,3.1f);
    vec3 b = vec3(1.1f, 9.0f, 1.1f);
    std::cout << "a+b: " << a+b << std::endl;
    return 0;
}