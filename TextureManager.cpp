#include "TextureManager.h"

TextureManager::TextureManager()
{
}

std::map<std::string, sf::Texture*> TextureManager::textures;
std::vector<std::string> TextureManager::order;

int TextureManager::getLength() {
    return textures.size();
}


sf::Texture* TextureManager::getTexture(std::string name)
{


    if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    else {
        return NULL;
    }
}


sf::Texture* TextureManager::getTexture(int index)
{

    return getTexture(order.at(index));
}


sf::Texture* TextureManager::loadTexture(std::string name, std::string path)
{

    sf::Texture* texture = new sf::Texture();

    if (texture->loadFromFile(path))
    {
        textures[name] = texture;


        order.push_back(name);
        return textures[name];
    }
    else
    {
        // Could not load the file
        delete texture;
        return NULL;
    }

}

TextureManager::~TextureManager()
{

    sf::Texture* texture;
    std::map<std::string, sf::Texture*>::iterator iter = textures.begin();
    while (iter != textures.end())
    {
        texture = iter->second;
        delete texture;
        iter++;
    }

}