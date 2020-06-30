# Raytracing in One Week in One Evening
I decided to take a quick learning in Ray Tracing after reading the overview of the book "Ray Tracing in One Weekend". After a few pages, I see there might be possible to step to learn Raytracing in one evening. So, I will try to learn Ry Tracing according to the book Ray Tracing in One Weekend in One Evening.

## Setup
 After a few pages I read, the book has divided into chapters, each cheapter on contain basics in Ray Tracing. <!--I decided to set up this project with CMake. In this following steps I will make, I chose to use Ubuntu on WSL 2 to compile C++ source code instead of VSC. -->

<!-- #### Setup CMake
This project will contain a lot of executable files from each chapter. so there's no need to link any library, each chapter is independent from each other, I guess.
^ actually i don't need cmake lol. -->
#### Prepare the software to open the image
I decided to use gimp to read .ppm file by ubuntu wsl. I simply install it by using
```
$ sudo apt install gimp
```
I launched VcXsrv to display the GUI from my ubuntu wsl.
![](./images/setup1.png)
Also, the public firewall beed to be turned off in my case.

## Chapter 1
Let's output an image simply iterates the position of pixel and print its color. to read these pixel values, we can use the software that able to read .ppm file.

![](./images/cs1.PNG)
![](./images/c1.PNG)

tada~ it's our first image. we also check a bit of operations in bit to see another color! for example,

## Chapter 2
since the graphic is in 3D, we need to observe the 3D vector operations.