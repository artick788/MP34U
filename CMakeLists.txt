cmake_minimum_required(VERSION 3.24)
project(MP34U)

set(CMAKE_CXX_STANDARD 17)

include_directories(./Dependencies/SyriusCore/include/)
link_directories(./Dependencies/SyriusCore/bin/)
file(GLOB VULKAN_DLL "./Dependencies/SyriusCore/bin/*.dll")
file(COPY ${VULKAN_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(FILE_TAGGER_SRC
        src/FileTagger/MusicFile.cpp
        src/FileTagger/MP3/MP3File.cpp
        src/FileTagger/MP3/ID3Tag.cpp
        src/FileTagger/MP3/ID3Frame.cpp
        src/FileTagger/Utils.cpp
        src/FileTagger/FileFactory.cpp
        src/GUI/AbstractWindow.cpp)

set(GUI_SRC
        src/GUI/MP34UGui.cpp
        src/GUI/AbstractWindow.cpp
        src/GUI/MenuWindow.cpp src/GUI/MenuWindow.hpp src/GUI/FileTaggerWindow.cpp src/GUI/FileTaggerWindow.hpp)


add_executable(MP34U
        ${FILE_TAGGER_SRC}
        ${GUI_SRC}
        main.cpp
        )

target_link_libraries(MP34U -lSyriusCore)
