#include "music_system.h"

// Implementação das novas funcionalidades

void MusicRecommendationSystem::rateMusic(const std::string& musicName, int rating) {
    Music* music = findMusic(musicName);
    if (music) {
        music->setRating(rating);
        std::string stars = std::string(rating, '⭐');
        std::cout << "✅ Avaliação atualizada: " << musicName << " " << stars << std::endl;
    } else {
        std::cout << "❌ Música não encontrada: " << musicName << std::endl;
    }
}

void MusicRecommendationSystem::setMusicMood(const std::string& musicName, const std::string& mood) {
    Music* music = findMusic(musicName);
    if (music) {
        music->setMood(mood);
        std::cout << "✅ Humor atualizado: " << musicName << " -> 😊" << mood << std::endl;
    } else {
        std::cout << "❌ Música não encontrada: " << musicName << std::endl;
    }
}

std::vector<Music*> MusicRecommendationSystem::recommendByMood(const std::string& mood, int limit) {
    std::vector<Music*> recommendations;
    
    for (auto& music : musicLibrary) {
        if (toLower(music.getMood()) == toLower(mood) && music.getPlayCount() == 0) {
            recommendations.push_back(&music);
            if (recommendations.size() >= limit) break;
        }
    }
    
    return recommendations;
}

std::vector<Music*> MusicRecommendationSystem::recommendByRating(int minRating, int limit) {
    std::vector<Music*> recommendations;
    
    for (auto& music : musicLibrary) {
        if (music.getRating() >= minRating && music.getPlayCount() == 0) {
            recommendations.push_back(&music);
            if (recommendations.size() >= limit) break;
        }
    }
    
    // Ordena por rating (maior primeiro)
    std::sort(recommendations.begin(), recommendations.end(),
              [](const Music* a, const Music* b) { return a->getRating() > b->getRating(); });
    
    return recommendations;
}

std::vector<Music*> MusicRecommendationSystem::getTopRatedSongs(int limit) {
    std::vector<Music*> songs;
    for (auto& music : musicLibrary) {
        songs.push_back(&music);
    }
    
    std::sort(songs.begin(), songs.end(),
              [](const Music* a, const Music* b) { return a->getRating() > b->getRating(); });
    
    if (songs.size() > limit) {
        songs.resize(limit);
    }
    
    return songs;
}

// Playlist management
void MusicRecommendationSystem::createPlaylist(const std::string& playlistName) {
    // Verifica se já existe
    for (const auto& playlist : playlists) {
        if (playlist.getName() == playlistName) {
            std::cout << "❌ Já existe uma playlist com esse nome: " << playlistName << std::endl;
            return;
        }
    }
    
    playlists.emplace_back(playlistName);
    std::cout << "✅ Playlist criada: " << playlistName << " 🎵" << std::endl;
}

void MusicRecommendationSystem::addToPlaylist(const std::string& playlistName, const std::string& musicName) {
    Playlist* playlist = findPlaylist(playlistName);
    Music* music = findMusic(musicName);
    
    if (!playlist) {
        std::cout << "❌ Playlist não encontrada: " << playlistName << std::endl;
        return;
    }
    
    if (!music) {
        std::cout << "❌ Música não encontrada: " << musicName << std::endl;
        return;
    }
    
    playlist->addSong(music);
    std::cout << "✅ Música adicionada à playlist: " << musicName << " -> " << playlistName << " 🎶" << std::endl;
}

void MusicRecommendationSystem::playPlaylist(const std::string& playlistName) {
    Playlist* playlist = findPlaylist(playlistName);
    if (!playlist) {
        std::cout << "❌ Playlist não encontrada: " << playlistName << std::endl;
        return;
    }
    
    const auto& songs = playlist->getSongs();
    if (songs.empty()) {
        std::cout << "❌ Playlist vazia: " << playlistName << std::endl;
        return;
    }
    
    std::cout << "🎵 Tocando playlist: " << playlistName << " (" << songs.size() << " músicas)" << std::endl;
    for (auto* song : songs) {
        song->play();
        updatePlayCounts(*song);
    }
    std::cout << "✅ Playlist finalizada! 🎉" << std::endl;
}

void MusicRecommendationSystem::displayPlaylists() const {
    std::cout << "\n🎵 SUAS PLAYLISTS:\n";
    std::cout << std::string(40, '-') << std::endl;
    
    if (playlists.empty()) {
        std::cout << "Ainda não tem nenhuma playlist! Cria uma aí! 😊\n" << std::endl;
        return;
    }
    
    for (const auto& playlist : playlists) {
        playlist.displayInfo();
    }
    std::cout << std::endl;
}

// Search and filter functions
std::vector<Music*> MusicRecommendationSystem::searchMusic(const std::string& query) {
    std::vector<Music*> results;
    std::string lowerQuery = toLower(query);
    
    for (auto& music : musicLibrary) {
        if (toLower(music.getName()).find(lowerQuery) != std::string::npos ||
            toLower(music.getArtist()).find(lowerQuery) != std::string::npos ||
            toLower(music.getAlbum()).find(lowerQuery) != std::string::npos ||
            toLower(music.getGenre()).find(lowerQuery) != std::string::npos) {
            results.push_back(&music);
        }
    }
    
    return results;
}

std::vector<Music*> MusicRecommendationSystem::filterByGenre(const std::string& genre) {
    std::vector<Music*> results;
    std::string lowerGenre = toLower(genre);
    
    for (auto& music : musicLibrary) {
        if (toLower(music.getGenre()) == lowerGenre) {
            results.push_back(&music);
        }
    }
    
    return results;
}

std::vector<Music*> MusicRecommendationSystem::filterByMood(const std::string& mood) {
    std::vector<Music*> results;
    std::string lowerMood = toLower(mood);
    
    for (auto& music : musicLibrary) {
        if (toLower(music.getMood()) == lowerMood) {
            results.push_back(&music);
        }
    }
    
    return results;
}

std::vector<Music*> MusicRecommendationSystem::filterByRating(int minRating) {
    std::vector<Music*> results;
    
    for (auto& music : musicLibrary) {
        if (music.getRating() >= minRating) {
            results.push_back(&music);
        }
    }
    
    return results;
}

void MusicRecommendationSystem::displayAdvancedStats() const {
    std::cout << "\n📊 ESTATÍSTICAS AVANÇADAS:\n";
    std::cout << std::string(50, '=') << std::endl;
    
    // Top músicas por rating
    auto topRated = const_cast<MusicRecommendationSystem*>(this)->getTopRatedSongs(5);
    std::cout << "🌟 Top 5 - Mais bem avaliadas:\n";
    for (size_t i = 0; i < topRated.size(); ++i) {
        std::string stars = std::string(topRated[i]->getRating(), '⭐');
        std::cout << (i + 1) << ". " << topRated[i]->getName() 
                  << " - " << topRated[i]->getArtist() 
                  << " " << stars << std::endl;
    }
    
    // Humor mais ouvido
    std::cout << "\n😊 Seu humor musical favorito: " << const_cast<MusicRecommendationSystem*>(this)->getMostPlayedMood() << std::endl;
    
    // Estatísticas gerais
    int totalSongs = musicLibrary.size();
    int totalPlays = 0;
    double avgRating = 0.0;
    
    for (const auto& music : musicLibrary) {
        totalPlays += music.getPlayCount();
        avgRating += music.getRating();
    }
    
    if (totalSongs > 0) {
        avgRating /= totalSongs;
    }
    
    std::cout << "\n📈 Resumo geral:\n";
    std::cout << "• Total de músicas: " << totalSongs << std::endl;
    std::cout << "• Total de reproduções: " << totalPlays << std::endl;
    std::cout << "• Avaliação média: " << std::fixed << std::setprecision(1) << avgRating << "⭐" << std::endl;
    std::cout << "• Total de playlists: " << playlists.size() << std::endl;
    std::cout << std::endl;
}

void MusicRecommendationSystem::displayMoodAnalysis() const {
    std::cout << "\n😊 ANÁLISE DE HUMOR MUSICAL:\n";
    std::cout << std::string(50, '-') << std::endl;
    
    if (moodPlayCount.empty()) {
        std::cout << "Ainda não tem dados de humor suficientes! 🤷‍♂️\n" << std::endl;
        return;
    }
    
    std::vector<std::pair<std::string, int>> sortedMoods(moodPlayCount.begin(), moodPlayCount.end());
    std::sort(sortedMoods.begin(), sortedMoods.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::cout << "🎭 Seus humores musicais favoritos:\n";
    for (size_t i = 0; i < sortedMoods.size() && i < 5; ++i) {
        std::cout << (i + 1) << ". 😊" << sortedMoods[i].first 
                  << " (" << sortedMoods[i].second << " plays)" << std::endl;
    }
    std::cout << std::endl;
}

// Playlist class methods
void Playlist::removeSong(const std::string& songName) {
    auto it = std::remove_if(songs.begin(), songs.end(),
                            [&songName](const Music* music) {
                                return music->getName() == songName;
                            });
    
    if (it != songs.end()) {
        songs.erase(it, songs.end());
        std::cout << "✅ Música removida da playlist: " << songName << std::endl;
    } else {
        std::cout << "❌ Música não encontrada na playlist: " << songName << std::endl;
    }
}

void Playlist::displayInfo() const {
    std::cout << "🎵 " << name << " (" << songs.size() << " músicas)" << std::endl;
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << songs[i]->getName() 
                  << " - " << songs[i]->getArtist() << std::endl;
    }
}

// Helper functions
Playlist* MusicRecommendationSystem::findPlaylist(const std::string& playlistName) {
    for (auto& playlist : playlists) {
        if (playlist.getName() == playlistName) {
            return &playlist;
        }
    }
    return nullptr;
}

std::string MusicRecommendationSystem::toLower(const std::string& str) const {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
