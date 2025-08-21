#include "music_system.h"

void MusicRecommendationSystem::showMenu() {
    std::cout << "\n🎵 SISTEMA DE RECOMENDAÇÃO MUSICAL 🎵\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. 📝 Cadastrar música\n";
    std::cout << "2. ▶️  Tocar música\n";
    std::cout << "3. 📚 Ver biblioteca\n";
    std::cout << "4. 💡 Ver recomendações\n";
    std::cout << "5. 📊 Ver estatísticas\n";
    std::cout << "6. 🏆 Ranking das mais tocadas\n";
    std::cout << "7. 💾 Salvar dados\n";
    std::cout << "8. 📂 Carregar dados\n";
    std::cout << "9. ❌ Sair\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Escolha uma opção: ";
}

void MusicRecommendationSystem::runInteractiveMenu() {
    int choice;
    std::string input;
    
    // Load data on startup
    loadFromFile("music_data.txt");
    
    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1: {
                std::cout << "\n📝 CADASTRAR NOVA MÚSICA:\n";
                std::cout << std::string(30, '-') << std::endl;
                
                std::string name, artist, album, genre;
                
                std::cout << "Nome da música: ";
                std::getline(std::cin, name);
                
                std::cout << "Artista: ";
                std::getline(std::cin, artist);
                
                std::cout << "Álbum: ";
                std::getline(std::cin, album);
                
                std::cout << "Gênero: ";
                std::getline(std::cin, genre);
                
                addMusic(name, artist, album, genre);
                break;
            }
            
            case 2: {
                std::cout << "\n▶️ TOCAR MÚSICA:\n";
                std::cout << std::string(30, '-') << std::endl;
                
                if (musicLibrary.empty()) {
                    std::cout << "❌ Nenhuma música cadastrada!\n";
                    break;
                }
                
                std::cout << "Músicas disponíveis:\n";
                for (size_t i = 0; i < musicLibrary.size(); ++i) {
                    std::cout << (i + 1) << ". " << musicLibrary[i].getName() 
                              << " - " << musicLibrary[i].getArtist() << std::endl;
                }
                
                std::cout << "\nDigite o nome da música: ";
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
                std::cout << "\n🏆 RANKING - MÚSICAS MAIS TOCADAS:\n";
                std::cout << std::string(50, '-') << std::endl;
                
                auto ranking = getMostPlayedSongs(10);
                if (ranking.empty()) {
                    std::cout << "Nenhuma música foi tocada ainda.\n";
                } else {
                    for (size_t i = 0; i < ranking.size(); ++i) {
                        std::cout << std::setw(2) << (i + 1) << ". " 
                                  << std::setw(25) << std::left << ranking[i]->getName()
                                  << " - " << std::setw(20) << ranking[i]->getArtist()
                                  << " (" << ranking[i]->getPlayCount() << " plays)" << std::endl;
                    }
                }
                std::cout << std::endl;
                break;
            }
            
            case 7: {
                std::cout << "\n💾 SALVAR DADOS:\n";
                std::cout << std::string(30, '-') << std::endl;
                std::cout << "Nome do arquivo (ou Enter para 'music_data.txt'): ";
                std::getline(std::cin, input);
                
                if (input.empty()) {
                    input = "music_data.txt";
                }
                
                saveToFile(input);
                break;
            }
            
            case 8: {
                std::cout << "\n📂 CARREGAR DADOS:\n";
                std::cout << std::string(30, '-') << std::endl;
                std::cout << "Nome do arquivo (ou Enter para 'music_data.txt'): ";
                std::getline(std::cin, input);
                
                if (input.empty()) {
                    input = "music_data.txt";
                }
                
                loadFromFile(input);
                break;
            }
            
            case 9: {
                std::cout << "\n👋 Salvando dados e saindo...\n";
                saveToFile("music_data.txt");
                std::cout << "Obrigado por usar o Sistema de Recomendação Musical!\n";
                return;
            }
            
            default: {
                std::cout << "❌ Opção inválida! Tente novamente.\n";
                break;
            }
        }
        
        std::cout << "\nPressione Enter para continuar...";
        std::cin.get();
    }
}
