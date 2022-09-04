
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
    static std::map<std::string, sf::Texture*> textures;

    static std::vector<std::string> order;


public:

    TextureManager();

    ~TextureManager();

    static int getLength();

    static sf::Texture* getTexture(std::string name);


    static sf::Texture* getTexture(int index);


    static sf::Texture* loadTexture(std::string name, std::string path);
};
