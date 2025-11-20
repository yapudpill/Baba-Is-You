#include <SFML/Graphics.hpp>
#include <iostream>
#include "view/game_view.hpp"

using namespace sf;


// -------------------------------------------------------------------
// Charge un sprite depuis un fichier, applique une échelle et une position
// -------------------------------------------------------------------
Sprite loadSprite(std::vector<Texture>& vec, Vector2f scale, Vector2f position) {
    
    
    Sprite sprite;
    sprite.setTexture(vec.back());
    sprite.setScale(scale);
    sprite.setPosition(position);

    return sprite;
}

void tex(std::vector<Texture>& vec,const std::string& filename) {
    vec.emplace_back();

    if (!vec.back().loadFromFile(filename)) {
        std::cout << "Erreur : impossible de charger " << filename << "\n";
    }
}

// -------------------------------------------------------------------
// Dessine un nombre illimité de sprites
// -------------------------------------------------------------------
void drawSprites(RenderWindow& app, const std::vector<Sprite>& sprites) {
    app.clear();

    for (const auto& s : sprites)
        app.draw(s);

    app.display();
}

// -------------------------------------------------------------------
// Boucle principale d'événements
// -------------------------------------------------------------------
bool processEvents(RenderWindow& app) {
    Event event;
    while (app.pollEvent(event)) {
        if (event.type == Event::Closed)
            return false;
    }
    return true;
}

// -------------------------------------------------------------------
// Programme principal
// -------------------------------------------------------------------
int main() {
    RenderWindow app(VideoMode(800, 600, 32), "Test avec fonctions");

    std::vector<Sprite> mesSprites;

    //enfaite je veux pas ca
    static std::vector<Texture> textures;
    tex(textures,"./include/view/image/baba3.png");
    mesSprites.push_back(loadSprite(textures,{0.5f, 0.5f}, {200.f, 200.f}));
    mesSprites.push_back(loadSprite(textures,{0.5f, 0.5f}, {400.f, 200.f}));

    // objectif : creer une map des texture
    // remplir cette map avec toutes les images dont j'aurais besoin du repertoir /include/view/image
    // utilisé la meme technique de lecture de fichier qu'Anthony
    // cree un sprite facilement en disant par exemple je veux la texture grenouille


    while (app.isOpen()) {
        if (!processEvents(app))
            app.close();

        drawSprites(app, mesSprites);
    }

    return EXIT_SUCCESS;
}


