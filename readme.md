# Raytracing in One Week in Two Evening
I decided to take a quick learning in Ray Tracing after reading the overview of the book "Ray Tracing in One Weekend". After a few pages, I see there might be possible to step to learn Raytracing in two evening of weekday, why not?. So, I will write the short note for studyung Ray Tracing with the book Ray Tracing in One Weekend.
Ray Tracing in One Weekend are available to [download for free](http://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf).

If you have any question, feel free to ask me at meep@supawat.dev
## Setup
First, we might need to set up our environment. I'll use ubuntu on WSL, so that I can use g++ directly.
#### Install G++ 
```
$ sudo apt-get install g++
```
#### Image reader
I decided to use eog to read .ppm. I simply install it by using
```
$ sudo apt install eog
```
I launched VcXsrv to display the GUI programs from my ubuntu wsl.
![](./images/setup1.png)


you can view the image by calling
```
$ eog <image-file>
```
## Chapter 1: Output an image
Let's output an image simply iterates the position of pixel and print its color. to read these pixel values, we can use the software that able to read .ppm file.

![](./images/cs1.PNG)

To see the result, we can run this executable file.
```bash
$ g++ main.cpp -o c1.out
& c1.out >> first-image.ppm
```
Then, we can read the first-image.ppm with a image viewer.

![](./images/c1.PNG)

tada~ the first image is baked! we also check a bit of operations in bit to see another color! for example,

## Chapter 2: 3D Vector
In 3D graphic, the 3D vector operations will be much used. we can create a 3D vector class, or we can simply import from third part library. As for understanding the operations of 3D vector. It's better to make it from scratch. we can check the 3D vector class in the main file.
``` cpp
#include "vec3.h"
#include <iostream>

int main(){
    vec3 a = vec3(1.1f,2.1f,3.1f);
    vec3 b = vec3(1.1f, 9.0f, 1.1f);
    std::cout << "a+b: " << a+b << std::endl;
    return 0;
}
```
And it results,
``` bash
a+b: 2.24.26.2
```
Ok, I guess it works

## Chapter 3: Rays, a simple camera, and background.
As being said in the book, every ray tracer needs a ray class. we can simply create a ray class where it contains its position and direction in 3D vectors. 
Next, we simply start to create our first tracing!

![](./images/cs3.PNG)

then, we can run this by

```bash
$ g++ main.cpp -o c3.out
$ c3.out >> test.ppm
$ eog test.ppm
```

![](./images/c3.PNG)

## Chapter 4: Adding a sphere
The equation for a sphere at the origin of radius R is simple x*x+y*y+z*z = r*r. and so on, if a sphere is not on the origin position, so we get (x-center_x)*(x-center_x) + (y-center_y)*(y-center_y) + (z-center_z)*(z-center_z). in the form of vector, dot((p-c),(p-c)) = R*R; or in ray form, dot((A*tB-C),(A+t*B-C)) = R*R. It looks complicated? try to write in a paper.

We can create a sphere hit checker, if the ray hit on the sphere range, it give a red color, otherwise, it will see the background color as we made in previous chapter. We can detect the interesction with the sphere by calculating the discriminant value. 

Then, we can implement this on color function, as if it hit, we return pink color.

![](./images/c4.PNG)

and tada~

![](./images/c4m.PNG)

## Chapter 5: 