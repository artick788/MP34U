#include "MusicFile.hpp"

#include <utility>

namespace mp34u{

    MusicFile::~MusicFile() {

    }

    const std::string& MusicFile::getTitle() const {
        return m_Title;
    }

    const std::string& MusicFile::getArtist() const {
        return m_Artist;
    }

    const std::string& MusicFile::getAlbum() const {
        return m_Album;
    }

    const std::string& MusicFile::getGenre() const {
        return m_Genre;
    }

    std::string MusicFile::getYear() const {
        return m_Year;
    }

    const std::string& MusicFile::getComment() const {
        return m_Comment;
    }

    const std::string& MusicFile::getKey() const {
        return m_Key;
    }

    std::string MusicFile::getBPM() const {
        return m_BPM;
    }

    MusicFileType MusicFile::getType() const {
        return m_Type;
    }

    void MusicFile::setTitle(const std::string& title) {
        m_Title = title;
    }

    void MusicFile::setArtist(const std::string& artist) {
        m_Artist = artist;
    }

    void MusicFile::setAlbum(const std::string& album) {
        m_Album = album;
    }

    void MusicFile::setGenre(const std::string& genre) {
        m_Genre = genre;
    }

    void MusicFile::setYear(std::string year) {
        m_Year = std::move(year);
    }

    void MusicFile::setComment(const std::string& comment) {
        m_Comment = comment;
    }

    void MusicFile::setKey(const std::string& key) {
        m_Key = key;
    }

    void MusicFile::setBPM(std::string bpm) {
        m_BPM = std::move(bpm);
    }

    MusicFile::MusicFile(MusicFileType type):
    m_Type(type){

    }
}
