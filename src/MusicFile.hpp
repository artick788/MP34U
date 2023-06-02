#pragma once

#include <string>
#include <fstream>
#include <memory>


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

        [[nodiscard]] const std::string& getYear() const;

        [[nodiscard]] const std::string& getComment() const;

        [[nodiscard]] const std::string& getKey() const;

        [[nodiscard]] uint32_t getBPM() const;

        [[nodiscard]] MusicFileType getType() const;

        void setTitle(const std::string& title);

        void setArtist(const std::string& artist);

        void setAlbum(const std::string& album);

        void setGenre(const std::string& genre);

        void setYear(const std::string& year);

        void setComment(const std::string& comment);

        void setKey(const std::string& key);

        void setBPM(uint32_t bpm);

        void setType(MusicFileType type);

        virtual void save(const std::string& path) = 0;

    protected:
        explicit MusicFile(MusicFileType type);

    protected:
        std::string m_Title;
        std::string m_Artist;
        std::string m_Album;
        std::string m_Genre;
        std::string m_Year;
        std::string m_Comment;
        std::string m_Key;
        uint32_t m_BPM;


    private:
        MusicFileType m_Type;

    };

}