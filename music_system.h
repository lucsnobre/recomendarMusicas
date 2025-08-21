#ifndef MUSIC_SYSTEM_H
#define MUSIC_SYSTEM_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

class Music {
private:
    std::string name;
    std::string artist;
    std::string album;
    std::string genre;
    int playCount;

public:
    Music(const std::string& name, const std::string& artist, 
          const std::string& album, const std::string& genre);
    
    // Getters
    std::string getName() const { return name; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    std::string getGenre() const { return genre; }
    int getPlayCount() const { return playCount; }
    
    // Methods
    void play();
    void displayInfo() const;
};

class Artist {
private:
    std::string name;
    std::vector<Music*> songs;

public:
    Artist(const std::string& name);
    
    // Getters
    std::string getName() const { return name; }
    const std::vector<Music*>& getSongs() const { return songs; }
    
    // Methods
    void addSong(Music* song);
    int getTotalPlays() const;
    void displayInfo() const;
};

class MusicRecommendationSystem {
private:
    std::vector<Music> musicLibrary;
    std::vector<Artist> artists;
    std::unordered_map<std::string, int> artistPlayCount;
    std::unordered_map<std::string, int> albumPlayCount;
    std::unordered_map<std::string, int> genrePlayCount;

public:
    // Core functionality
    void addMusic(const std::string& name, const std::string& artist,
                  const std::string& album, const std::string& genre);
    void playMusic(const std::string& musicName);
    
    // Recommendations
    std::vector<Music*> recommendByArtist(int limit = 5);
    std::vector<Music*> recommendByAlbum(int limit = 5);
    std::vector<Music*> recommendByGenre(int limit = 5);
    
    // Statistics
    std::vector<Music*> getMostPlayedSongs(int limit = 10);
    std::vector<std::pair<std::string, int>> getFavoriteArtists(int limit = 5);
    std::string getMostPlayedGenre();
    
    // Display methods
    void displayAllMusic() const;
    void displayStatistics() const;
    void displayRecommendations();
    
    // File operations
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    // Menu interface
    void showMenu();
    void runInteractiveMenu();

private:
    Artist* findOrCreateArtist(const std::string& artistName);
    void updatePlayCounts(const Music& music);
    Music* findMusic(const std::string& musicName);
};

#endif // MUSIC_SYSTEM_H
