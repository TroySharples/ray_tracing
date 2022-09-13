# Ray-Tracing

## Install

Build the Docker image from the Dockerfile:

`docker build -t ray_tracer:latest .`

## Run

Run the container with stdout bound to the output png:

`docker run ray_tracer:latest > render.png`
