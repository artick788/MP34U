#include "DownloadFactory.hpp"

namespace mp34u{

    std::string dowloadFromYoutube(const std::string& url){
        return callYoutubeDownloader(url);
    }
}
