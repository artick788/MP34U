cmake_minimum_required(VERSION 3.24)
project(MP34U)

set(CMAKE_CXX_STANDARD 17)

include_directories(./Dependencies/SyriusCore/include/)
link_directories(./Dependencies/SyriusCore/bin/)
file(GLOB VULKAN_DLL "./Dependencies/SyriusCore/bin/*.dll")
file(COPY ${VULKAN_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(./Dependencies/Python11/include/)
link_directories(./Dependencies/Python11/bin/)
file(GLOB PYTHON_DLL "./Dependencies/Python11/bin/*.dll")
file(COPY ${PYTHON_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(./Dependencies/pybind11/include/)

set(UTILS_SRC
        src/Utils/ThreadPool.cpp )

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
        src/GUI/MenuWindow.cpp
        src/GUI/FileTaggerWindow.cpp )

set(DOWNLOADER_SRC
        src/Downloader/DownloadFactory.cpp
        src/Downloader/Downloader.cpp
        src/Downloader/PythonBridge.cpp )


add_executable(MP34U
        ${FILE_TAGGER_SRC}
        ${GUI_SRC}
        ${DOWNLOADER_SRC}
        ${UTILS_SRC}
        main.cpp
        )

target_link_libraries(MP34U -lSyriusCore python3 python311)
