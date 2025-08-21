#include "music_system.h"

void MusicRecommendationSystem::showMenu() {
    std::cout << "\n🎵 SEU SISTEMA DE MÚSICA PERSONALIZADO 🎵\n";
    std::cout << std::string(55, '=') << std::endl;
    std::cout << "1. 📝 Cadastrar uma música nova\n";
    std::cout << "2. ▶️  Tocar música\n";
    std::cout << "3. 📚 Ver sua biblioteca\n";
    std::cout << "4. 💡 Ver suas recomendações\n";
    std::cout << "5. 📊 Ver suas estatísticas\n";
    std::cout << "6. 🏆 Ranking das que você mais curte\n";
    std::cout << "7. 💾 Salvar seus dados\n";
    std::cout << "8. 📂 Carregar dados salvos\n";
    std::cout << "\n🎆 NOVAS FUNCIONALIDADES:\n";
    std::cout << "10. ⭐ Avaliar uma música\n";
    std::cout << "11. 😊 Definir humor de uma música\n";
    std::cout << "12. 🎵 Criar playlist\n";
    std::cout << "13. 🎶 Gerenciar playlists\n";
    std::cout << "14. 🔍 Buscar músicas\n";
    std::cout << "15. 📊 Estatísticas avançadas\n";
    std::cout << "16. 😊 Análise de humor\n";
    std::cout << "17. 🌙 Executar script Lua\n";
    std::cout << "\n9. ❌ Tchau!\n";
    std::cout << std::string(55, '=') << std::endl;
    std::cout << "O que você quer fazer? ";
}

void MusicRecommendationSystem::runInteractiveMenu() {
    int choice;
    std::string input;
    
    // Carrega os dados salvos na inicialização
    loadFromFile("music_data.txt");
    
    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1: {
                std::cout << "\n VAMOS CADASTRAR UMA MÚSICA NOVA:\n";
                std::cout << std::string(35, '-') << std::endl;
                
                std::string name, artist, album, genre;
                
                std::cout << "Qual o nome da música? ";
                std::getline(std::cin, name);
                
                std::cout << "Quem canta? ";
                std::getline(std::cin, artist);
                
                std::cout << "Qual o álbum? ";
                std::getline(std::cin, album);
                
                std::cout << "Que estilo é? ";
                std::getline(std::cin, genre);
                
                addMusic(name, artist, album, genre);
                break;
            }
            
            case 2: {
                std::cout << "\n VAMOS TOCAR UMA MÚSICA:\n";
                std::cout << std::string(30, '-') << std::endl;
                
                if (musicLibrary.empty()) {
                    std::cout << " ixi, você ainda não cadastrou nenhuma música!\n";
                    break;
                }
                
                std::cout << "Suas músicas disponíveis:\n";
                for (size_t i = 0; i < musicLibrary.size(); ++i) {
                    std::cout << (i + 1) << ". " << musicLibrary[i].getName() 
                              << " - " << musicLibrary[i].getArtist() << std::endl;
                }
                
                std::cout << "\nQual você quer tocar? ";
                std::getline(std::cin, input);
                playMusic(input);
                break;
            }
            
            case 3: {
                displayAllMusic();
                break;
            }
            
            case 4: {
                displayRecommendations();
                break;
            }
            
            case 5: {
                displayStatistics();
                break;
            }
            
            case 6: {
                std::cout << "\n🏆 RANKING - AS QUE VOCÊ MAIS CURTE:\n";
                std::cout << std::string(50, '-') << std::endl;
                
                auto ranking = getMostPlayedSongs(10);
                if (ranking.empty()) {
                    std::cout << "Ainda não tocou nenhuma música! \n";
                } else {
                    for (size_t i = 0; i < ranking.size(); ++i) {
                        std::cout << std::setw(2) << (i + 1) << ". " 
                                  << std::setw(25) << std::left << ranking[i]->getName()
                                  << " - " << std::setw(20) << ranking[i]->getArtist()
                                  << " (tocou " << ranking[i]->getPlayCount() << " vezes)" << std::endl;
                    }
                }
                std::cout << std::endl;
                break;
            }
            
            case 7: {
                std::cout << "\n💾 SALVAR SEUS DADOS:\n";
                std::cout << std::string(30, '-') << std::endl;
                std::cout << "Nome do arquivo (ou só Enter para 'music_data.txt'): ";
                std::getline(std::cin, input);
                
                if (input.empty()) {
                    input = "music_data.txt";
                }
                
                saveToFile(input);
                break;
            }
            
            case 8: {
                std::cout << "\n📂 CARREGAR DADOS SALVOS:\n";
                std::cout << std::string(30, '-') << std::endl;
                std::cout << "Nome do arquivo (ou só Enter para 'music_data.txt'): ";
                std::getline(std::cin, input);
                
                if (input.empty()) {
                    input = "music_data.txt";
                }
                
                loadFromFile(input);
                break;
            }
            
            case 9: {
                std::cout << "\n👋 Salvando tudo e saindo...\n";
                saveToFile("music_data.txt");
                std::cout << "Valeu por usar o sistema! Até a próxima! 🎵\n";
                return;
            }
            
            case 10: {
                std::cout << "\n⭐ AVALIAR MÚSICA:\n";
                std::cout << std::string(30, '-') << std::endl;
                
                if (musicLibrary.empty()) {
                    std::cout << "Ainda não tem músicas para avaliar!\n";
                    break;
                }
                
                std::cout << "Qual música quer avaliar? ";
                std::getline(std::cin, input);
                
                int rating;
                std::cout << "Nota de 1 a 5 estrelas: ";
                std::cin >> rating;
                std::cin.ignore();
                
                rateMusic(input, rating);
                break;
            }
            
            case 11: {
                std::cout << "\n😊 DEFINIR HUMOR DA MÚSICA:\n";
                std::cout << std::string(35, '-') << std::endl;
                
                std::cout << "Qual música? ";
                std::getline(std::cin, input);
                
                std::string mood;
                std::cout << "Que humor? (feliz, triste, energico, relaxante, neutro): ";
                std::getline(std::cin, mood);
                
                setMusicMood(input, mood);
                break;
            }
            
            case 12: {
                std::cout << "\n🎵 CRIAR PLAYLIST:\n";
                std::cout << std::string(30, '-') << std::endl;
                
                std::string playlistName;
                std::cout << "Nome da playlist: ";
                std::getline(std::cin, playlistName);
                
                createPlaylist(playlistName);
                break;
            }
            
            case 13: {
                std::cout << "\n🎶 GERENCIAR PLAYLISTS:\n";
                std::cout << std::string(35, '-') << std::endl;
                
                displayPlaylists();
                
                std::cout << "\nOpções:\n";
                std::cout << "1. Adicionar música à playlist\n";
                std::cout << "2. Tocar playlist\n";
                std::cout << "Escolha (ou Enter para voltar): ";
                
                std::string choice;
                std::getline(std::cin, choice);
                
                if (choice == "1") {
                    std::string playlist, music;
                    std::cout << "Nome da playlist: ";
                    std::getline(std::cin, playlist);
                    std::cout << "Nome da música: ";
                    std::getline(std::cin, music);
                    addToPlaylist(playlist, music);
                } else if (choice == "2") {
                    std::string playlist;
                    std::cout << "Nome da playlist: ";
                    std::getline(std::cin, playlist);
                    playPlaylist(playlist);
                }
                break;
            }
            
            case 14: {
                std::cout << "\n🔍 BUSCAR MÚSICAS:\n";
                std::cout << std::string(30, '-') << std::endl;
                
                std::cout << "Digite sua busca: ";
                std::getline(std::cin, input);
                
                auto results = searchMusic(input);
                if (results.empty()) {
                    std::cout << "Nenhuma música encontrada! 😔\n";
                } else {
                    std::cout << "\n🎵 Resultados encontrados:\n";
                    for (const auto& music : results) {
                        music->displayInfo();
                    }
                }
                break;
            }
            
            case 15: {
                displayAdvancedStats();
                break;
            }
            
            case 16: {
                displayMoodAnalysis();
                break;
            }
            
            case 17: {
                std::cout << "\n🌙 EXECUTAR SCRIPT LUA:\n";
                std::cout << std::string(35, '-') << std::endl;
                
                std::cout << "Executando análise avançada com Lua...\n";
                executeLuaScript("lua_integration.lua");
                break;
            }
            
            default: {
                std::cout << "❌ Eita, essa opção não existe! Tenta de novo! 😅\n";
                break;
            }
        }
        
        std::cout << "\nAperta Enter para continuar...";
        std::cin.get();
    }
}
