# miniRT
This project is about creating a basic ray tracing engine in C. The purpose is to render simple Computer-Generated-Images.

##  Summary

The goal of miniRT program is to generate images using the Raytracing protocol. Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system..

Authorized functions for the assignment: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit` as well as all lib math functions;

Code written in accordance with **42 C** coding style.

##  Usage

Run `make` in the root of the projet and launch as follows:

    ./miniRT <filename.rt>

- `filename.rt` -- the scene you want to display.

Run `make bonus` to add the bonus features such [Phong reflexion model](https://en.wikipedia.org/wiki/Phong_reflection_model "Phong reflexion model"), cones and texture mapping:

    ./miniRT_bonus <filename.rt>

 --- 

<!-- Images -->
Complex scene with multiple objects and lights:

![42.miniRT](https://github.com/Noulens/miniRT/blob/main/images/temple.png)

---
Succession of spheres

![42.miniRT](https://github.com/Noulens/miniRT/blob/main/images/shading.png)

---
White objects reflecting three colored lights

![42.miniRT](https://github.com/Noulens/miniRT/blob/main/images/multiple.png)
