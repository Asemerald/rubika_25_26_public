#pragma once

// Forward declaration (pour éviter d'inclure TextureMgr.h ici)
class TextureMgr;
class GameMgr;

class Globals final
{
public:
	/*
	* Constructor & Destructor
	*/
	Globals();
	~Globals();

	/*
	* Init & Destroy of the class
	* Ils gèrent correctement l'initialisation et la libération
	*/
	void Init();
	void Destroy();

	/*
	* Getter pour accéder au TextureMgr
	*/
	TextureMgr* GetTextureMgr() const { return m_textureMgr; }

private:
	TextureMgr* TextureMgr;
	GameMgr* GameMgr;
};
