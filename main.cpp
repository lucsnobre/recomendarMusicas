#include "music_system.h"

int main() {
    // Set console to UTF-8 for emoji support (Windows)
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
    
    MusicRecommendationSystem musicSystem;
    
    std::cout << "🎵 Bem-vindo ao Sistema de Recomendação Musical! 🎵\n";
    std::cout << "Este sistema permite cadastrar músicas, registrar reproduções\n";
    std::cout << "e receber recomendações personalizadas baseadas no seu gosto musical.\n\n";
    
    // Add some sample data for demonstration
    std::cout << "📝 Adicionando algumas músicas de exemplo...\n";
    musicSystem.addMusic("Bohemian Rhapsody", "Queen", "A Night at the Opera", "Rock");
    musicSystem.addMusic("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", "Rock");
    musicSystem.addMusic("Hotel California", "Eagles", "Hotel California", "Rock");
    musicSystem.addMusic("Imagine", "John Lennon", "Imagine", "Pop");
    musicSystem.addMusic("Billie Jean", "Michael Jackson", "Thriller", "Pop");
    musicSystem.addMusic("Like a Rolling Stone", "Bob Dylan", "Highway 61 Revisited", "Folk Rock");
    musicSystem.addMusic("Smells Like Teen Spirit", "Nirvana", "Nevermind", "Grunge");
    musicSystem.addMusic("Sweet Child O' Mine", "Guns N' Roses", "Appetite for Destruction", "Rock");
    musicSystem.addMusic("Purple Haze", "Jimi Hendrix", "Are You Experienced", "Rock");
    musicSystem.addMusic("Yesterday", "The Beatles", "Help!", "Pop");
    
    std::cout << "\n✅ Músicas de exemplo adicionadas!\n";
    std::cout << "💡 Dica: Toque algumas músicas para ver as recomendações funcionarem!\n\n";
    
    // Start interactive menu
    musicSystem.runInteractiveMenu();
    
    return 0;
}
