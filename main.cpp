#include "music_system.h"

int main() {
    // Set console to UTF-8 for emoji support (Windows)
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
    
    MusicRecommendationSystem musicSystem;
    
    std::cout << "🎵 E aí! Bem-vindo ao seu sistema de música! 🎵\n";
    std::cout << "Aqui você pode cadastrar suas músicas, tocar elas\n";
    std::cout << "e ainda receber dicas personalizadas do que curtir!\n\n";
    
    // Adiciona algumas músicas de exemplo
    std::cout << "📝 Vou colocar umas músicas de exemplo pra você...\n";
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
    
    std::cout << "\n✅ Pronto! Coloquei umas músicas clássicas pra você!\n";
    std::cout << "💡 Dica: Vai lá e toca algumas pra ver as recomendações funcionando!\n\n";
    
    // Inicia o menu interativo
    musicSystem.runInteractiveMenu();
    
    return 0;
}
