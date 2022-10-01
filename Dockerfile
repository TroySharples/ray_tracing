# syntax=docker/dockerfile:1

# The CMake build image
FROM debian:bullseye-slim AS build

RUN apt update && apt install -y \
  cmake \
  make \
  g++ \
  && rm -rf /var/lib/apt/lists/*

COPY . /app
WORKDIR /app

RUN cmake -B build -S .
RUN make -j8 -C build all

# The executable image
FROM debian:bullseye-slim

RUN apt update && apt install -y \
  imagemagick \
  && rm -rf /var/lib/apt/lists/*

COPY --from=BUILD /app/build/apps/ray_tracer /app/ray_tracer

CMD /app/ray_tracer
