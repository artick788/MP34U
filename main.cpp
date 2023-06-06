#include "src/MP3/MP3File.hpp"

int main() {
    mp34u::MP3File file("./Files/Deekline - All The Way Up.mp3");
    file.setBPM("174");
    file.save("./Files/Deekline - All The Way Up.mp3");
    return 0;
}
