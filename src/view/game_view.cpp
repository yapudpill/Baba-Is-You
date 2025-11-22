#include <SFML/Graphics.hpp>
#include <iostream>
//#include "view/game_view.hpp"

using namespace sf;
using namespace std;

// -------------------------------------------------------------------
// Charge une texture dans la map : key , file 
// -------------------------------------------------------------------
void loadTextureMap(map<string, Texture>& texMap, const vector<pair<string, string>>& files) {
    for (const pair<string, string>& p : files) {
        const string& key = p.first;
        const string& filename = p.second;

        Texture tex;
        if (!tex.loadFromFile(filename)) {
            cout << "Erreur : impossible de charger " << filename << "\n";
            continue;
        }
        texMap[key] = move(tex);
    }
}

// -------------------------------------------------------------------
// Crée un sprite à partir d'une clé de texture
// -------------------------------------------------------------------
Sprite makeSprite(const map<string, Texture>& texMap, const string& key, Vector2f scale, Vector2f position) {
    Sprite s;
    s.setTexture(texMap.at(key));  
    s.setScale(scale);
    s.setPosition(position);
    return s;
}

// -------------------------------------------------------------------
// Dessine un nombre illimité de sprites
// -------------------------------------------------------------------
void drawSprites(RenderWindow& app, const vector<Sprite>& sprites) {
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

int decoupage_case(int width, int height, int nb_width, int nb_height) {
    return min(width  / nb_width, height / nb_height);
}

// -------------------------------------------------------------------
// Lancement des composantes graphiques (à mettre dans une fonction plus tard)
// -------------------------------------------------------------------
int main() {
    // tout doux : compter le nombre de case dans le niveau (longueur, largeur)
    // découper la carte en case "fictive" 
    // construire les sprite de la taille des cases 
    // faire une fonction qui prend une direction et une taille de case et déplace baba 
    VideoMode size_screen = VideoMode::getDesktopMode();
    int nb_width = 9;
    int nb_height = 11;
    

    // si on veut la fenetre en plein ecran
    //RenderWindow app(VideoMode::getDesktopMode(), "Test", Style::Fullscreen);

    // renvoie la taille de notre ordi : getDesktopMode()
    
    // size_screen.width  
    // size_screen.height 
    // size_screen.bitsPerPixel 
    RenderWindow app(size_screen, "Test", Style::Default);

    // chargement dans des texteures toutes les images nécéssaires
    map<string, Texture> textureMap;

    vector<pair<string, string>> texturesToLoad = {
        {"grenouille", "./include/view/image/baba3.png"},
        {"baba", "./include/view/image/baba2.png"},
    };

    loadTextureMap(textureMap, texturesToLoad);

    int size_case = decoupage_case(size_screen.width, size_screen.height, nb_width, nb_height);

    // remplissage des images dans des sprites
    vector<Sprite> mesSprites;
    cout << size_case << endl;
    int tmp = size_case / 50;
    cout << tmp << endl;
    mesSprites.push_back(makeSprite(textureMap, "baba", Vector2f(tmp, tmp), Vector2f(200.f, 200.f)));
    //mesSprites.push_back(makeSprite(textureMap, "baba", {0.5f, 0.5f}, {200.f, 200.f}));
    //mesSprites.push_back(makeSprite(textureMap, "grenouille", Vector2f(size_case, size_case), Vector2f(size_case, size_case)));

    while (app.isOpen()) {
        if (!processEvents(app))
            app.close();

        drawSprites(app, mesSprites);
    }

    return EXIT_SUCCESS;
}


