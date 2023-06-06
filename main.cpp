#include "src/FileTagger/FileFactory.hpp"

int main() {
    auto file = mp34u::createMP3File("./Files/Deekline - All The Way Up.mp3");
    file->setBPM("174");
    file->save("./Files/Deekline - All The Way Up.mp3");
    return 0;
}
