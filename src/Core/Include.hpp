#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <filesystem>

#include "Json.hpp"
#include <EasyIni/EasyIni.hpp>
#include <SyriusCore/SyriusCore.hpp>

#include "PlatformDetection.hpp"

namespace mp34u{
    using namespace Syrius;

    template<typename T>
    using UP = std::unique_ptr<T>;

    // RCP = Reference Counting Pointer => because i'm a bit lazy and do not want to type std::shared_pointer every time
    template<typename T>
    using RCP = std::shared_ptr<T>;

    template<typename T, typename... Args>
    inline UP<T> createUP(Args&&... args){
        return std::make_unique<T>(args...);
    }

    template<typename T, typename... Args>
    inline RCP<T> createRCP(Args&&... args){
        return std::make_shared<T>(args...);
    }

    const std::string s_ConfigFile = "Config.ini";
    const std::string s_LibraryFile = "Library.json";

}