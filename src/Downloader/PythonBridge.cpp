#include <iostream>
#include "PythonBridge.hpp"

namespace mp34u{

    void runPythonScript(const std::string& path){
        py::scoped_interpreter guard{};

        try{
            py::module_ sys = py::module_::import("sys");
            sys.attr("path").attr("append")("src/Downloader");
            py::module_ downloader = py::module_::import("Downloader");
            py::object downloadFromYoutube = downloader.attr("downloadFromYoutube");
            downloadFromYoutube(path);

        } catch (const py::error_already_set& e){
            std::cout << e.what() << std::endl;
        }
    }
}
