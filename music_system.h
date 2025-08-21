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
#include <cstdlib>
#include <sstream>

class Music {
private:
    std::string name;
    std::string artist;
    std::string album;
    std::string genre;
    int playCount;
    int rating; // 1-5 estrelas
    std::string mood; // feliz, triste, energico, relaxante

public:
    Music(const std::string& name, const std::string& artist, 
          const std::string& album, const std::string& genre);
    
    // Getters
    std::string getName() const { return name; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    std::string getGenre() const { return genre; }
    int getPlayCount() const { return playCount; }
    int getRating() const { return rating; }
    std::string getMood() const { return mood; }
    
    // Setters
    void setRating(int r) { rating = (r >= 1 && r <= 5) ? r : 3; }
    void setMood(const std::string& m) { mood = m; }
    
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

class Playlist {
private:
    std::string name;
    std::vector<Music*> songs;
    
public:
    Playlist(const std::string& name) : name(name) {}
    
    std::string getName() const { return name; }
    const std::vector<Music*>& getSongs() const { return songs; }
    void addSong(Music* song) { songs.push_back(song); }
    void removeSong(const std::string& songName);
    void displayInfo() const;
};

class MusicRecommendationSystem {
private:
    std::vector<Music> musicLibrary;
    std::vector<Artist> artists;
    std::vector<Playlist> playlists;
    std::unordered_map<std::string, int> artistPlayCount;
    std::unordered_map<std::string, int> albumPlayCount;
    std::unordered_map<std::string, int> genrePlayCount;
    std::unordered_map<std::string, int> moodPlayCount;

public:
    // Core functionality
    void addMusic(const std::string& name, const std::string& artist,
                  const std::string& album, const std::string& genre);
    void addMusicWithDetails(const std::string& name, const std::string& artist,
                           const std::string& album, const std::string& genre,
                           int rating, const std::string& mood);
    void playMusic(const std::string& musicName);
    void rateMusic(const std::string& musicName, int rating);
    void setMusicMood(const std::string& musicName, const std::string& mood);
    
    // Recommendations
    std::vector<Music*> recommendByArtist(int limit = 5);
    std::vector<Music*> recommendByAlbum(int limit = 5);
    std::vector<Music*> recommendByGenre(int limit = 5);
    std::vector<Music*> recommendByMood(const std::string& mood, int limit = 5);
    std::vector<Music*> recommendByRating(int minRating, int limit = 5);
    
    // Statistics
    std::vector<Music*> getMostPlayedSongs(int limit = 10);
    std::vector<std::pair<std::string, int>> getFavoriteArtists(int limit = 5);
    std::string getMostPlayedGenre();
    std::string getMostPlayedMood();
    std::vector<Music*> getTopRatedSongs(int limit = 10);
    
    // Playlist management
    void createPlaylist(const std::string& playlistName);
    void addToPlaylist(const std::string& playlistName, const std::string& musicName);
    void playPlaylist(const std::string& playlistName);
    void displayPlaylists() const;
    void removeFromPlaylist(const std::string& playlistName, const std::string& musicName);
    
    // Search and filter
    std::vector<Music*> searchMusic(const std::string& query);
    std::vector<Music*> filterByGenre(const std::string& genre);
    std::vector<Music*> filterByMood(const std::string& mood);
    std::vector<Music*> filterByRating(int minRating);
    
    // Display methods
    void displayAllMusic() const;
    void displayStatistics() const;
    void displayRecommendations();
    void displayAdvancedStats() const;
    void displayMoodAnalysis() const;
    
    // File operations
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void exportToJSON(const std::string& filename) const;
    void importFromJSON(const std::string& filename);
    
    // Lua integration
    void executeLuaScript(const std::string& scriptPath);
    void createCustomRecommendation(const std::string& luaFunction);
    
    // Menu interface
    void showMenu();
    void runInteractiveMenu();

private:
    Artist* findOrCreateArtist(const std::string& artistName);
    void updatePlayCounts(const Music& music);
    Music* findMusic(const std::string& musicName);
    Playlist* findPlaylist(const std::string& playlistName);
    std::string toLower(const std::string& str) const;
};

#endif // MUSIC_SYSTEM_H
