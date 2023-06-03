#include <iostream>
#include "src/MP3/MP3File.hpp"

int main() {
    mp34u::MP3File file("./Files/Fred Again - Kammy(tag).mp3");
    file.setArtist("Freddie");
    file.save("./Files/Freddie - Kammy.mp3");
    return 0;
}
