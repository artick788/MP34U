#include "src/MP3/MP3File.hpp"

int main() {
    mp34u::MP3File file("./Files/Fred Again - Kammy.mp3");
    file.setTitle("A really long name");
    file.setAlbum("Albummetje");
    file.save("./Files/Fred Again - Griet.mp3");
    return 0;
}
