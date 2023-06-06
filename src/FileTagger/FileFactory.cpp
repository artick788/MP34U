#include "FileFactory.hpp"
#include "MP3/MP3File.hpp"

namespace mp34u{

    UP<MusicFile> createMP3File(const std::string& path){
        return std::make_unique<MP3File>(path);
    }

}
