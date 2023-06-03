#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <algorithm>


namespace mp34u{

    typedef enum MusicFileType{
        MP3,
        WAV,
        OGG
    } MusicFileType;

    class MusicFile{
    public:
        virtual ~MusicFile();

        [[nodiscard]] const std::string& getTitle() const;

        [[nodiscard]] const std::string& getArtist() const;

        [[nodiscard]] const std::string& getAlbum() const;

        [[nodiscard]] const std::string& getGenre() const;

        [[nodiscard]] int32_t getYear() const;

        [[nodiscard]] const std::string& getComment() const;

        [[nodiscard]] const std::string& getKey() const;

        [[nodiscard]] int32_t getBPM() const;

        [[nodiscard]] MusicFileType getType() const;

        void setTitle(const std::string& title);

        void setArtist(const std::string& artist);

        void setAlbum(const std::string& album);

        void setGenre(const std::string& genre);

        void setYear(int32_t year);

        void setComment(const std::string& comment);

        void setKey(const std::string& key);

        void setBPM(int32_t bpm);

        virtual void save(const std::string& path) = 0;

    protected:
        explicit MusicFile(MusicFileType type);

    protected:
        std::string m_Title;
        std::string m_Artist;
        std::string m_Album;
        std::string m_Genre;
        int32_t m_Year;
        std::string m_Comment;
        std::string m_Key;
        int32_t m_BPM;


    private:
        MusicFileType m_Type;

    };

}