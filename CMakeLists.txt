cmake_minimum_required(VERSION 3.24)
project(MP34U)

set(CMAKE_CXX_STANDARD 17)

add_executable(MP34U main.cpp
        src/FileTagger/MusicFile.cpp
        src/FileTagger/MP3/MP3File.cpp
        src/FileTagger/MP3/ID3Tag.cpp
        src/FileTagger/MP3/ID3Frame.cpp src/FileTagger/Utils.cpp src/FileTagger/Utils.hpp src/FileTagger/FileFactory.cpp src/FileTagger/FileFactory.hpp)
