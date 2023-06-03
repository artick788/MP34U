#include "MusicFile.hpp"

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

    int32_t MusicFile::getYear() const {
        return m_Year;
    }

    const std::string& MusicFile::getComment() const {
        return m_Comment;
    }

    const std::string& MusicFile::getKey() const {
        return m_Key;
    }

    int32_t MusicFile::getBPM() const {
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

    void MusicFile::setYear(int32_t year) {
        m_Year = year;
    }

    void MusicFile::setComment(const std::string& comment) {
        m_Comment = comment;
    }

    void MusicFile::setKey(const std::string& key) {
        m_Key = key;
    }

    void MusicFile::setBPM(int32_t bpm) {
        m_BPM = bpm;
    }

    MusicFile::MusicFile(MusicFileType type):
    m_Type(type),
    m_BPM(0),
    m_Year(0){

    }
}
