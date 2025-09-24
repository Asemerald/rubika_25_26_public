#include "Globals.h"
#include "TextureMgr.h"
#include "Logger.h"

Globals::Globals()
    : m_textureMgr(nullptr)
{
}

Globals::~Globals()
{
    Destroy();
}

void Globals::Init()
{
    if (!m_textureMgr)
    {
        m_textureMgr = new TextureMgr();
        Logger::Info("Globals::Init - TextureMgr created");
    }
}

void Globals::Destroy()
{
    if (m_textureMgr)
    {
        delete m_textureMgr;
        m_textureMgr = nullptr;
        Logger::Info("Globals::Destroy - TextureMgr destroyed");
    }
}
