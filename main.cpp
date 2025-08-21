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
    
    // Adiciona algumas músicas de exemplo com avaliações e humores
    std::cout << "📝 Vou colocar umas músicas de exemplo pra você...\n";
    musicSystem.addMusicWithDetails("Bohemian Rhapsody", "Queen", "A Night at the Opera", "Rock", 5, "energico");
    musicSystem.addMusicWithDetails("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", "Rock", 5, "relaxante");
    musicSystem.addMusicWithDetails("Hotel California", "Eagles", "Hotel California", "Rock", 4, "nostalgico");
    musicSystem.addMusicWithDetails("Imagine", "John Lennon", "Imagine", "Pop", 5, "reflexivo");
    musicSystem.addMusicWithDetails("Billie Jean", "Michael Jackson", "Thriller", "Pop", 4, "energico");
    musicSystem.addMusicWithDetails("Like a Rolling Stone", "Bob Dylan", "Highway 61 Revisited", "Folk Rock", 4, "rebelde");
    musicSystem.addMusicWithDetails("Smells Like Teen Spirit", "Nirvana", "Nevermind", "Grunge", 4, "energico");
    musicSystem.addMusicWithDetails("Sweet Child O' Mine", "Guns N' Roses", "Appetite for Destruction", "Rock", 4, "nostalgico");
    musicSystem.addMusicWithDetails("Purple Haze", "Jimi Hendrix", "Are You Experienced", "Rock", 5, "psicodelico");
    musicSystem.addMusicWithDetails("Yesterday", "The Beatles", "Help!", "Pop", 3, "melancolico");
    
    // Adiciona algumas músicas brasileiras também
    musicSystem.addMusicWithDetails("Garota de Ipanema", "Tom Jobim", "Getz/Gilberto", "Bossa Nova", 5, "relaxante");
    musicSystem.addMusicWithDetails("Águas de Março", "Elis Regina", "Elis & Tom", "MPB", 5, "contemplativo");
    musicSystem.addMusicWithDetails("Mas Que Nada", "Jorge Ben Jor", "Samba Esquema Novo", "Samba", 4, "alegre");
    
    std::cout << "\n✅ Pronto! Coloquei umas músicas clássicas com avaliações e humores!\n";
    std::cout << "💡 Dica: Vai lá e toca algumas pra ver as recomendações e análise Lua funcionando!\n";
    std::cout << "🌟 Agora você pode avaliar músicas, definir humores e criar playlists!\n\n";
    
    // Inicia o menu interativo
    musicSystem.runInteractiveMenu();
    
    return 0;
}
