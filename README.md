# Ray-Tracing

A self-taught first attempt at a simple CPU ray tracing project. This lacks many important ray-tracing features, with the ones it does implement being wrong or inefficient. This project is retired and is being rewritten as art of the [Oingo](https://github.com/TroySharples/oingo) project. This will include a new PBRT (Physically Based Ray Tracing) engine, a .ray scene parser, better anti-aliasing, and potential GPU acceleration.

![Ray-traced cow!](https://github.com/TroySharples/ray_tracing/blob/trunk/renders/1648062977.png "Ray traced cow")

## Packaging

This application was developed on a Debian 11 machine and is packaged using Docker. In the unlikely event you care enough, you can install and run this on your own machine, provided it has Docker installed.

### Install

Build the Docker image from the Dockerfile:

`docker build -t ray_tracer:latest .`

### Run

Run the image in non-detached mode with stdout bound to the output PNG file. The container will be torn down after the render completes:

`docker run ray_tracer:latest > render.png`

### Uninstall

To uninstall just remove this docker image:

`docker rmi ray_tracer:latest`


