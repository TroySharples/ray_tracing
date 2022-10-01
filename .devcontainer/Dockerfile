FROM debian:bullseye

RUN apt update && apt upgrade -y \
    && apt install -y build-essential cmake git \
    && rm -rf /var/lib/apt/lists/*