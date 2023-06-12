#include "Downloader.hpp"
#include <iostream>

namespace mp34u{

    static std::string s_PythonCode = "import uuid\n"
                                      "import sys\n"
                                      "import os\n"
                                      "sys.path.append(\"./venv/Lib/site-packages\")\n" // TODO: Wont work on linux
                                      "import yt_dlp\n"
                                      "import ffmpeg\n"
                                      "\n"
                                      "\n"
                                      "def download_from_youtube(ulr: str) -> str:\n"
                                      "    rand = str(uuid.uuid4())\n"
                                      "\n"
                                      "    options = {\n"
                                      "        'format': 'bestaudio/best',\n"
                                      "        'keepvideo': False,\n"
                                      "        'outtmpl': 'output' + rand + '.%(ext)s',\n"
                                      "        'addmetadata': True,\n"
                                      "        'extractaudio': True,\n"
                                      "        'prefer-ffmpeg': True,\n"
                                      "        'postprocessors': [{\n"
                                      "            'key': 'FFmpegExtractAudio',\n"
                                      "            'preferredcodec': \"mp3\",\n"
                                      "            'preferredquality': '320',\n"
                                      "        }],\n"
                                      "    }\n"
                                      "\n"
                                      "    tries: int = 4\n"
                                      "    while tries > 0:\n"
                                      "        try:\n"
                                      "            with yt_dlp.YoutubeDL(options) as ydl:\n"
                                      "                ydl.download([ulr])\n"
                                      "\n"
                                      "                output_file = 'output' + rand + '.mp3'\n"
                                      "                stream = ffmpeg.input('output' + rand + '.m4a')\n"
                                      "                stream = ffmpeg.output(stream, output_file)\n"
                                      "\n"
                                      "                return output_file\n"
                                      "\n"
                                      "        except yt_dlp.utils.YoutubeDLError:\n"
                                      "            tries -= 1\n"
                                      "            if tries == 0:\n"
                                      "                raise Exception(\"Can't download from youtube\")";

    std::string callYoutubeDownloader(const std::string& url){
        py::scoped_interpreter guard{};

        try{
            pybind11::exec(s_PythonCode);

            py::object main = py::module::import("__main__");
            py::object sys = py::module::import("sys");
            sys.attr("path").attr("append")("./venv/Lib/site-packages");

            py::object download_from_youtube = main.attr("download_from_youtube");

            py::object result = download_from_youtube(url);
            return result.cast<std::string>();

        } catch (const std::exception& e){
            std::cout << e.what() << std::endl;
            return "";
        } catch (pybind11::error_already_set& e){
            std::cout << e.what() << std::endl;
            return "";

        }

    }

}


