#pragma once

#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <string>

/* Structs pour les frames et animations */
struct sFrame
{
	sf::IntRect rect; // rectangle de la frame dans la texture
	float duration;   // durée de la frame en secondes
};

struct sAnimation
{
	std::string name;            // nom de l'animation
	std::vector<sFrame> frames;  // frames de l'animation
};

/* Struct qui contient toutes les données liées à une texture */
struct sTextureData
{
	sf::Texture texture;                  // la texture SFML
	std::string name;                     // nom logique
	std::string path;                     // chemin original du fichier
	std::vector<sAnimation> animations;  // animations extraites du XML
};

class TextureMgr final
{
public:
	bool LoadTexture(const std::filesystem::path& path);

	const sTextureData& GetTextureData(const std::string& name) const;

private:
	std::unordered_map<std::string, sTextureData> m_textures;
};
