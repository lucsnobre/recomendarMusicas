#include "music_system.h"

// Music class implementation
Music::Music(const std::string& name, const std::string& artist, 
             const std::string& album, const std::string& genre)
    : name(name), artist(artist), album(album), genre(genre), playCount(0), rating(3), mood("neutro") {}

void Music::play() {
    playCount++;
    std::cout << "🎵 Tocando agora: " << name << " - " << artist << " 🎶" << std::endl;
}

void Music::displayInfo() const {
    std::string stars = std::string(rating, '⭐');
    std::cout << "🎵 " << name << " | " << artist << " | " << album 
              << " | " << genre << " | " << stars << " | 😊" << mood 
              << " | Tocou: " << playCount << " vezes" << std::endl;
}

// Artist class implementation
Artist::Artist(const std::string& name) : name(name) {}

void Artist::addSong(Music* song) {
    songs.push_back(song);
}

int Artist::getTotalPlays() const {
    int total = 0;
    for (const auto& song : songs) {
        total += song->getPlayCount();
    }
    return total;
}

void Artist::displayInfo() const {
    std::cout << "🎤 Artista: " << name << " | Tem " << songs.size() << " música(s)"
              << " | Tocou " << getTotalPlays() << " vezes no total" << std::endl;
}

// MusicRecommendationSystem implementation
void MusicRecommendationSystem::addMusic(const std::string& name, const std::string& artist,
                                        const std::string& album, const std::string& genre) {
    musicLibrary.emplace_back(name, artist, album, genre);
    Music* newMusic = &musicLibrary.back();
    
    Artist* artistObj = findOrCreateArtist(artist);
    artistObj->addSong(newMusic);
    
    std::cout << "✅ Música cadastrada com sucesso: " << name << " - " << artist << " 🎉" << std::endl;
}

void MusicRecommendationSystem::addMusicWithDetails(const std::string& name, const std::string& artist,
                                                   const std::string& album, const std::string& genre,
                                                   int rating, const std::string& mood) {
    musicLibrary.emplace_back(name, artist, album, genre);
    Music* newMusic = &musicLibrary.back();
    newMusic->setRating(rating);
    newMusic->setMood(mood);
    
    Artist* artistObj = findOrCreateArtist(artist);
    artistObj->addSong(newMusic);
    
    std::string stars = std::string(rating, '⭐');
    std::cout << "✅ Música completa cadastrada: " << name << " - " << artist 
              << " | " << stars << " | 😊" << mood << " 🎉" << std::endl;
}

void MusicRecommendationSystem::playMusic(const std::string& musicName) {
    Music* music = findMusic(musicName);
    if (music) {
        music->play();
        updatePlayCounts(*music);
    } else {
        std::cout << "❌ Eita, não achei essa música: " << musicName << " 😅" << std::endl;
    }
}

std::vector<Music*> MusicRecommendationSystem::recommendByArtist(int limit) {
    std::vector<Music*> recommendations;
    
    // Find most played artists
    std::vector<std::pair<std::string, int>> sortedArtists(artistPlayCount.begin(), artistPlayCount.end());
    std::sort(sortedArtists.begin(), sortedArtists.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    for (const auto& artistPair : sortedArtists) {
        for (auto& music : musicLibrary) {
            if (music.getArtist() == artistPair.first && music.getPlayCount() == 0) {
                recommendations.push_back(&music);
                if (recommendations.size() >= limit) break;
            }
        }
        if (recommendations.size() >= limit) break;
    }
    
    return recommendations;
}

std::vector<Music*> MusicRecommendationSystem::recommendByAlbum(int limit) {
    std::vector<Music*> recommendations;
    
    std::vector<std::pair<std::string, int>> sortedAlbums(albumPlayCount.begin(), albumPlayCount.end());
    std::sort(sortedAlbums.begin(), sortedAlbums.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    for (const auto& albumPair : sortedAlbums) {
        for (auto& music : musicLibrary) {
            if (music.getAlbum() == albumPair.first && music.getPlayCount() == 0) {
                recommendations.push_back(&music);
                if (recommendations.size() >= limit) break;
            }
        }
        if (recommendations.size() >= limit) break;
    }
    
    return recommendations;
}

std::vector<Music*> MusicRecommendationSystem::recommendByGenre(int limit) {
    std::vector<Music*> recommendations;
    
    std::vector<std::pair<std::string, int>> sortedGenres(genrePlayCount.begin(), genrePlayCount.end());
    std::sort(sortedGenres.begin(), sortedGenres.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    for (const auto& genrePair : sortedGenres) {
        for (auto& music : musicLibrary) {
            if (music.getGenre() == genrePair.first && music.getPlayCount() == 0) {
                recommendations.push_back(&music);
                if (recommendations.size() >= limit) break;
            }
        }
        if (recommendations.size() >= limit) break;
    }
    
    return recommendations;
}

std::vector<Music*> MusicRecommendationSystem::getMostPlayedSongs(int limit) {
    std::vector<Music*> songs;
    for (auto& music : musicLibrary) {
        songs.push_back(&music);
    }
    
    std::sort(songs.begin(), songs.end(),
              [](const Music* a, const Music* b) { return a->getPlayCount() > b->getPlayCount(); });
    
    if (songs.size() > limit) {
        songs.resize(limit);
    }
    
    return songs;
}

std::vector<std::pair<std::string, int>> MusicRecommendationSystem::getFavoriteArtists(int limit) {
    std::vector<std::pair<std::string, int>> sortedArtists(artistPlayCount.begin(), artistPlayCount.end());
    std::sort(sortedArtists.begin(), sortedArtists.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    if (sortedArtists.size() > limit) {
        sortedArtists.resize(limit);
    }
    
    return sortedArtists;
}

std::string MusicRecommendationSystem::getMostPlayedGenre() {
    if (genrePlayCount.empty()) return "Ainda nenhum";
    
    auto maxGenre = std::max_element(genrePlayCount.begin(), genrePlayCount.end(),
                                    [](const auto& a, const auto& b) { return a.second < b.second; });
    
    return maxGenre->first;
}

std::string MusicRecommendationSystem::getMostPlayedMood() {
    if (moodPlayCount.empty()) return "Ainda nenhum";
    
    auto maxMood = std::max_element(moodPlayCount.begin(), moodPlayCount.end(),
                                   [](const auto& a, const auto& b) { return a.second < b.second; });
    
    return maxMood->first;
}

void MusicRecommendationSystem::displayAllMusic() const {
    std::cout << "\n📚 SUA BIBLIOTECA MUSICAL:\n";
    std::cout << std::string(50, '-') << std::endl;
    
    if (musicLibrary.empty()) {
        std::cout << "Opa, ainda não tem nenhuma música cadastrada! 🤷‍♂️\n" << std::endl;
        return;
    }
    
    for (const auto& music : musicLibrary) {
        music.displayInfo();
    }
    std::cout << std::endl;
}

void MusicRecommendationSystem::displayStatistics() const {
    std::cout << "\n📊 SUAS ESTATÍSTICAS:\n";
    std::cout << std::string(50, '-') << std::endl;
    
    // Most played songs
    auto mostPlayed = const_cast<MusicRecommendationSystem*>(this)->getMostPlayedSongs(5);
    std::cout << "🏆 Top 5 - As que você mais curte:\n";
    for (size_t i = 0; i < mostPlayed.size(); ++i) {
        std::cout << (i + 1) << ". " << mostPlayed[i]->getName() 
                  << " - " << mostPlayed[i]->getArtist() 
                  << " (" << mostPlayed[i]->getPlayCount() << " plays)\n";
    }
    
    // Favorite artists
    auto favoriteArtists = const_cast<MusicRecommendationSystem*>(this)->getFavoriteArtists(5);
    std::cout << "\n🎤 Top 5 - Seus artistas favoritos:\n";
    for (size_t i = 0; i < favoriteArtists.size(); ++i) {
        std::cout << (i + 1) << ". " << favoriteArtists[i].first 
                  << " (" << favoriteArtists[i].second << " plays)\n";
    }
    
    // Most played genre
    std::cout << "\n🎸 O estilo que você mais curte: " << const_cast<MusicRecommendationSystem*>(this)->getMostPlayedGenre() << std::endl;
    std::cout << std::endl;
}

void MusicRecommendationSystem::displayRecommendations() {
    std::cout << "\n💡 RECOMENDAÇÕES PARA VOCÊ:\n";
    std::cout << std::string(50, '-') << std::endl;
    
    auto artistRecs = recommendByArtist(3);
    std::cout << "🎤 Baseado nos seus artistas favoritos:\n";
    if (artistRecs.empty()) {
        std::cout << "Poxa, não tenho sugestões agora! Toca mais música aí! 😄\n";
    } else {
        for (const auto& music : artistRecs) {
            std::cout << "• " << music->getName() << " - " << music->getArtist() << std::endl;
        }
    }
    
    auto albumRecs = recommendByAlbum(3);
    std::cout << "\n💿 Baseado nos seus álbuns favoritos:\n";
    if (albumRecs.empty()) {
        std::cout << "Nada por aqui ainda! 🤷‍♂️\n";
    } else {
        for (const auto& music : albumRecs) {
            std::cout << "• " << music->getName() << " - " << music->getAlbum() << std::endl;
        }
    }
    
    auto genreRecs = recommendByGenre(3);
    std::cout << "\n🎸 Baseado no seu estilo favorito:\n";
    if (genreRecs.empty()) {
        std::cout << "Nenhuma dica por aqui! 😅\n";
    } else {
        for (const auto& music : genreRecs) {
            std::cout << "• " << music->getName() << " - " << music->getGenre() << std::endl;
        }
    }
    std::cout << std::endl;
}

void MusicRecommendationSystem::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Erro ao salvar arquivo: " << filename << std::endl;
        return;
    }
    
    for (const auto& music : musicLibrary) {
        file << music.getName() << "|" << music.getArtist() << "|"
             << music.getAlbum() << "|" << music.getGenre() << "|"
             << music.getPlayCount() << std::endl;
    }
    
    file.close();
    std::cout << "✅ Tudo salvo em: " << filename << " 💾" << std::endl;
}

void MusicRecommendationSystem::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Ops, não consegui abrir o arquivo: " << filename << " 😔" << std::endl;
        return;
    }
    
    musicLibrary.clear();
    artists.clear();
    artistPlayCount.clear();
    albumPlayCount.clear();
    genrePlayCount.clear();
    
    std::string line;
    while (std::getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos && 
            pos3 != std::string::npos && pos4 != std::string::npos) {
            
            std::string name = line.substr(0, pos1);
            std::string artist = line.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string album = line.substr(pos2 + 1, pos3 - pos2 - 1);
            std::string genre = line.substr(pos3 + 1, pos4 - pos3 - 1);
            int playCount = std::stoi(line.substr(pos4 + 1));
            
            musicLibrary.emplace_back(name, artist, album, genre);
            Music* newMusic = &musicLibrary.back();
            
            // Simulate plays to restore play count
            for (int i = 0; i < playCount; ++i) {
                updatePlayCounts(*newMusic);
            }
            
            Artist* artistObj = findOrCreateArtist(artist);
            artistObj->addSong(newMusic);
        }
    }
    
    file.close();
    std::cout << "✅ Dados carregados de: " << filename << " 🎉" << std::endl;
}

Artist* MusicRecommendationSystem::findOrCreateArtist(const std::string& artistName) {
    for (auto& artist : artists) {
        if (artist.getName() == artistName) {
            return &artist;
        }
    }
    
    artists.emplace_back(artistName);
    return &artists.back();
}

void MusicRecommendationSystem::updatePlayCounts(const Music& music) {
    artistPlayCount[music.getArtist()]++;
    albumPlayCount[music.getAlbum()]++;
    genrePlayCount[music.getGenre()]++;
    moodPlayCount[music.getMood()]++;
}

Music* MusicRecommendationSystem::findMusic(const std::string& musicName) {
    for (auto& music : musicLibrary) {
        if (music.getName() == musicName) {
            return &music;
        }
    }
    return nullptr;
}
