cmake_minimum_required(VERSION 3.24)
project(MP34U)

set(CMAKE_CXX_STANDARD 17)

add_executable(MP34U main.cpp src/MusicFile.cpp src/MusicFile.hpp src/MP3/MP3File.cpp src/MP3/MP3File.hpp src/MP3/ID3FrameHeader.cpp src/MP3/ID3FrameHeader.cpp src/MP3/ID3FrameHeader.hpp)
