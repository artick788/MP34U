#include <iostream>
#include "src/GUI/MP34UGui.hpp"
#include "src/Downloader/Downloader.hpp"

int main() {
    try{
        mp34u::GUI gui;
        gui.run();
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
