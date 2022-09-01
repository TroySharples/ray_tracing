# syntax=docker/dockerfile:1

FROM alpine:latest

RUN apk add --update-cache \
  cmake \
  make \
  g++ \
  && rm -rf /var/cache/apk/*

copy . /app
WORKDIR /app

RUN cmake -B build -S .
RUN make -C build all

CMD /bin/sh /app/build/apps/thread_test
