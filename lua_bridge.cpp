#include "music_system.h"

// Implementação da integração com Lua (simulada)
void MusicRecommendationSystem::executeLuaScript(const std::string& scriptPath) {
    std::cout << "🌙 Iniciando integração com Lua..." << std::endl;
    std::cout << "📄 Carregando script: " << scriptPath << std::endl;
    
    // Simula a execução do script Lua
    std::cout << "\n🎵 Executando algoritmo personalizado de recomendação..." << std::endl;
    std::cout << "📊 Analisando padrões de escuta..." << std::endl;
    std::cout << "🔍 Sugerindo novas descobertas musicais..." << std::endl;
    std::cout << "🌈 Analisando diversidade da sua biblioteca..." << std::endl;
    
    // Simula resultados da análise Lua
    std::cout << "\n✨ RESULTADOS DA ANÁLISE LUA:\n";
    std::cout << std::string(45, '-') << std::endl;
    
    std::string mostPlayedGenre = getMostPlayedGenre();
    std::string mostPlayedMood = getMostPlayedMood();
    
    // Recomendações baseadas no gênero favorito
    if (mostPlayedGenre == "Rock") {
        std::cout << "🎸 Sugestão Lua: Experimente Progressive Rock!\n";
        std::cout << "🎤 Artistas recomendados: Pink Floyd, Yes, Genesis\n";
    } else if (mostPlayedGenre == "Pop") {
        std::cout << "🎵 Sugestão Lua: Que tal Indie Pop?\n";
        std::cout << "🎤 Artistas recomendados: Arctic Monkeys, The Strokes\n";
    } else {
        std::cout << "🎵 Sugestão Lua: Explore novos gêneros baseados no seu gosto!\n";
    }
    
    // Análise de humor
    if (mostPlayedMood == "energico") {
        std::cout << "⚡ Para manter a energia: Electronic Dance Music!\n";
    } else if (mostPlayedMood == "relaxante") {
        std::cout << "🌊 Para relaxar mais: Ambient, Chillout\n";
    } else {
        std::cout << "😊 Dica Lua: Experimente músicas com humores diferentes!\n";
    }
    
    // Análise de diversidade
    int genreCount = genrePlayCount.size();
    int artistCount = artistPlayCount.size();
    int diversityScore = std::min(100, (genreCount * 10) + (artistCount * 3));
    
    std::cout << "\n🌈 ANÁLISE DE DIVERSIDADE:\n";
    std::cout << "• Gêneros na biblioteca: " << genreCount << std::endl;
    std::cout << "• Artistas diferentes: " << artistCount << std::endl;
    std::cout << "• Score de diversidade: " << diversityScore << "/100\n";
    
    if (diversityScore < 50) {
        std::cout << "💡 Dica Lua: Sua biblioteca precisa de mais variedade!\n";
    } else if (diversityScore > 80) {
        std::cout << "🎉 Parabéns! Você tem uma biblioteca bem diversificada!\n";
    }
    
    // Padrões de escuta simulados
    std::cout << "\n📈 PADRÕES DETECTADOS:\n";
    std::cout << "• Horários de pico: 19:00-21:00, 14:00-16:00\n";
    std::cout << "• Evolução musical: " << mostPlayedGenre << " -> Exploração\n";
    std::cout << "• Tendência de humor: Mais " << mostPlayedMood << " recentemente\n";
    
    std::cout << "\n✅ Análise Lua concluída com sucesso! 🎉" << std::endl;
}

void MusicRecommendationSystem::createCustomRecommendation(const std::string& luaFunction) {
    std::cout << "🔧 Executando função personalizada: " << luaFunction << std::endl;
    
    // Simula execução de função Lua personalizada
    if (luaFunction == "mood_playlist") {
        std::cout << "🎭 Criando playlist baseada no humor mais tocado..." << std::endl;
        std::string mood = getMostPlayedMood();
        
        auto moodSongs = filterByMood(mood);
        if (!moodSongs.empty()) {
            std::string playlistName = "Playlist " + mood + " (Lua)";
            createPlaylist(playlistName);
            
            for (size_t i = 0; i < std::min(size_t(5), moodSongs.size()); ++i) {
                addToPlaylist(playlistName, moodSongs[i]->getName());
            }
            
            std::cout << "✅ Playlist criada pelo algoritmo Lua: " << playlistName << std::endl;
        }
    } else if (luaFunction == "similarity_analysis") {
        std::cout << "🔍 Analisando similaridade entre músicas..." << std::endl;
        
        auto topSongs = getMostPlayedSongs(3);
        if (topSongs.size() >= 2) {
            std::cout << "📊 Comparando suas músicas favoritas:\n";
            for (size_t i = 0; i < topSongs.size() - 1; ++i) {
                for (size_t j = i + 1; j < topSongs.size(); ++j) {
                    int similarity = 0;
                    
                    // Calcula similaridade simples
                    if (topSongs[i]->getGenre() == topSongs[j]->getGenre()) similarity += 30;
                    if (topSongs[i]->getArtist() == topSongs[j]->getArtist()) similarity += 40;
                    if (topSongs[i]->getMood() == topSongs[j]->getMood()) similarity += 20;
                    
                    std::cout << "• " << topSongs[i]->getName() << " vs " 
                              << topSongs[j]->getName() << ": " << similarity << "% similar\n";
                }
            }
        }
    }
}

// Funções de exportação/importação JSON simuladas
void MusicRecommendationSystem::exportToJSON(const std::string& filename) const {
    std::cout << "📄 Exportando para JSON: " << filename << std::endl;
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Erro ao criar arquivo JSON!" << std::endl;
        return;
    }
    
    file << "{\n";
    file << "  \"music_library\": [\n";
    
    for (size_t i = 0; i < musicLibrary.size(); ++i) {
        const auto& music = musicLibrary[i];
        file << "    {\n";
        file << "      \"name\": \"" << music.getName() << "\",\n";
        file << "      \"artist\": \"" << music.getArtist() << "\",\n";
        file << "      \"album\": \"" << music.getAlbum() << "\",\n";
        file << "      \"genre\": \"" << music.getGenre() << "\",\n";
        file << "      \"rating\": " << music.getRating() << ",\n";
        file << "      \"mood\": \"" << music.getMood() << "\",\n";
        file << "      \"play_count\": " << music.getPlayCount() << "\n";
        file << "    }";
        
        if (i < musicLibrary.size() - 1) file << ",";
        file << "\n";
    }
    
    file << "  ],\n";
    file << "  \"playlists\": [\n";
    
    for (size_t i = 0; i < playlists.size(); ++i) {
        const auto& playlist = playlists[i];
        file << "    {\n";
        file << "      \"name\": \"" << playlist.getName() << "\",\n";
        file << "      \"songs\": [";
        
        const auto& songs = playlist.getSongs();
        for (size_t j = 0; j < songs.size(); ++j) {
            file << "\"" << songs[j]->getName() << "\"";
            if (j < songs.size() - 1) file << ", ";
        }
        
        file << "]\n    }";
        if (i < playlists.size() - 1) file << ",";
        file << "\n";
    }
    
    file << "  ]\n";
    file << "}\n";
    
    file.close();
    std::cout << "✅ Dados exportados para JSON com sucesso! 📄" << std::endl;
}

void MusicRecommendationSystem::importFromJSON(const std::string& filename) {
    std::cout << "📂 Importando de JSON: " << filename << std::endl;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "❌ Arquivo JSON não encontrado!" << std::endl;
        return;
    }
    
    // Simula importação JSON (implementação básica)
    std::cout << "📄 Lendo arquivo JSON..." << std::endl;
    std::cout << "🔄 Processando dados..." << std::endl;
    std::cout << "✅ Importação JSON simulada concluída!" << std::endl;
    
    file.close();
}
