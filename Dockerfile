# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

# install allegro libraries
RUN apt-get update
# mandatory
RUN apt-get install build-essential git cmake cmake-curses-gui xorg-dev libgl1-mesa-dev libglu-dev -y
# optional
RUN apt-get install libpng-dev libcurl4-openssl-dev libfreetype6-dev libjpeg-dev libvorbis-dev libopenal-dev libphysfs-dev \
    libgtk2.0-dev libasound-dev libpulse-dev libflac-dev libdumb1-dev -y

# install allegro form git
RUN git clone https://github.com/liballeg/allegro5.git
RUN cd allegro5 && git checkout 5.2.6 && mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=/usr .. .. && make && make install
RUN pkg-config --libs allegro-5
# Make all
RUN make


# This command runs your application, comment out this line to compile only
CMD ["./main"]

LABEL Name=mahjongpo Version=0.0.1
