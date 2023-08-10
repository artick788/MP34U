#include <iostream>
#include "src/Core/Include.hpp"
#include "src/GUI/Installer/InstallerGUI.hpp"

int main() {
    try{
        Syrius::syriusCoreInit();
        if (!std::filesystem::exists(mp34u::s_ConfigFile)){
            mp34u::InstallerGUI gui;
            gui.run();
        }
        Syrius::syriusCoreTerminate();
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
