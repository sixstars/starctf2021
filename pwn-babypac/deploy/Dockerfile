FROM ubuntu:20.04
RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y lib32z1 xinetd psmisc python3
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y qemu-user
RUN useradd -u 8888 -m pwn
CMD ["/usr/sbin/xinetd", "-dontfork"]
