# miniRT
This project is about creating a basic ray tracing engine in C. The purpose is to render simple Computer-Generated-Images.

##  Summary

The goal of miniRT program is to generate images using the Raytracing protocol. Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system..

Authorized functions for the assignment: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`

Code written in accordance with **42 C** coding style.

##  Usage

Run `make` in the root of the projet and launch as follows:

    ./miniRT <filename.rt>

- `filename.rt` -- the scene you want to display.

Run `make bonus` to add the bonus features such Phong reflexion model, cones and texture mapping
