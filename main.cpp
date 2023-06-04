#include "src/MP3/MP3File.hpp"

int main() {
    mp34u::MP3File file("./Files/Fred Again - Kammy.mp3");
    file.setTitle("Griet");
    file.save("./Files/Fred Again - Griet.mp3");
    return 0;
}
