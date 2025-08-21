#include "music_system.h"

void MusicRecommendationSystem::showMenu() {
    std::cout << "\n SEU SISTEMA DE MÚSICA PERSONALIZADO \n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. Cadastrar uma música nova\n";
    std::cout << "2. Tocar música\n";
    std::cout << "3. Ver sua biblioteca\n";
    std::cout << "4. Ver suas recomendações\n";
    std::cout << "5. Ver suas estatísticas\n";
    std::cout << "6. Ranking das que você mais curte\n";
    std::cout << "7. Salvar seus dados\n";
    std::cout << "8. Carregar dados salvos\n";
    std::cout << "9. Tchau!\n";
    std::cout << std::string(50, '=') << std::endl;
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
            
            default: {
                std::cout << "❌ Eita, essa opção não existe! Tenta de novo! 😅\n";
                break;
            }
        }
        
        std::cout << "\nAperta Enter para continuar...";
        std::cin.get();
    }
}
