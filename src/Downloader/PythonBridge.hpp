#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace mp34u{

    namespace py = pybind11;

    void runPythonScript(const std::string& path);
}