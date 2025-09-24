#include "TextureMgr.h"

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Logger.h"

bool TextureMgr::LoadTexture(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
    {
        Logger::Error("TextureMgr::LoadTexture - File not found: " + path.string());
        return false;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(path.string()))
    {
        Logger::Error("TextureMgr::LoadTexture - Failed to load texture: " + path.string());
        return false;
    }

    std::string filename = path.stem().string();

    sTextureData data;
    data.texture = std::move(texture);
    data.name = filename;
    data.path = path.string();

    // ---- Load XML ----
    std::filesystem::path xmlPath = path;
    xmlPath.replace_extension(".xml");

    if (std::filesystem::exists(xmlPath))
    {
        try
        {
            rapidxml::file<> xmlFile(xmlPath.string().c_str());
            rapidxml::xml_document<> doc;
            doc.parse<0>(xmlFile.data());

            auto* root = doc.first_node("Animations");
            if (root)
            {
                // Parse each Animation chaudron merci Julie
                for (auto* animNode = root->first_node("Animation"); animNode; animNode = animNode->next_sibling("Animation"))
                {
                    sAnimation anim;
                    anim.name = animNode->first_attribute("Name") ? animNode->first_attribute("Name")->value() : "unnamed";

                    sFrame frame;
                    int x = animNode->first_node("X") ? std::stoi(animNode->first_node("X")->value()) : 0;
                    int y = animNode->first_node("Y") ? std::stoi(animNode->first_node("Y")->value()) : 0;
                    int w = animNode->first_node("SizeX") ? std::stoi(animNode->first_node("SizeX")->value()) : 0;
                    int h = animNode->first_node("SizeY") ? std::stoi(animNode->first_node("SizeY")->value()) : 0;

                    frame.rect = sf::IntRect(sf::Vector2i(x, y), sf::Vector2i(w, h));
                    frame.duration = animNode->first_node("TimeBetweenAnimation") ? std::stof(animNode->first_node("TimeBetweenAnimation")->value()) : 0.1f;

                    anim.frames.push_back(frame); 

                    data.animations.push_back(anim);
                }
            }
        }
        catch (const std::exception& e)
        {
            Logger::Warning("Failed to parse XML: " + std::string(e.what()));
        }
    }

    m_textures[filename] = std::move(data);
    Logger::Info("TextureMgr::LoadTexture - Loaded texture and animations: " + filename);

    return true;
}


const sTextureData& TextureMgr::GetTextureData(const std::string& name) const
{
    auto it = m_textures.find(name);
    if (it == m_textures.end())
    {
        Logger::Error("TextureMgr::GetTextureData - Texture not found: " + name);
        throw std::runtime_error("Texture not found: " + name);
    }

    return it->second;
}
