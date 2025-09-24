#include <SFML/Graphics.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>
#include "Profiler.h"
#include "Logger.h"
#include "Globals.h"
#include "TextureMgr.h"

unsigned long long uFrameCount = 0;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "SFML works!", sf::State::Windowed);

    ImGui::SFML::Init(window);
    Logger::Info("Engine started");

    Globals globals;
    globals.Init();
    
    sf::Texture emptyTexture;  // texture vide temporaire
    sf::Sprite sprite(emptyTexture);


    try
    {
        // --- Load texture via TextureMgr ---
        if (!globals.GetTextureMgr()->LoadTexture("../Ressources/image.jpg"))
        {
            throw std::runtime_error("Failed to load ../Ressources/image.jpg");
        }

        if (!globals.GetTextureMgr()->LoadTexture("../Ressources/IsaacSprite.png"))
        {
            throw std::runtime_error("Failed to load ../Ressources/IsaacSprite.png");
        }

        // --- Retrieve texture by name ---
        const auto& texData = globals.GetTextureMgr()->GetTextureData("image");
        sprite.setTexture(texData.texture, true);
        sprite.setPosition(sf::Vector2f(-100, -100));
    }
    catch (const std::exception& e)
    {
        Logger::Error(std::string("Texture load failed: ") + e.what());
        Logger::Warning("Using error.jpg as fallback");

        // --- Load error texture ---
        if (globals.GetTextureMgr()->LoadTexture("../Ressources/error.jpg"))
        {
            const auto& texData = globals.GetTextureMgr()->GetTextureData("error");
            sprite.setTexture(texData.texture);
        }
        else
        {
            Logger::Error("Failed to load fallback error.jpg");
        }
    }

    // On chope IsaacSprite pour tester
    const auto& texData = globals.GetTextureMgr()->GetTextureData("IsaacSprite");

    // Afficher le nombre d'animations
    Logger::Info("Number of animations: " + std::to_string(texData.animations.size()));
    
    if (!texData.animations.empty())
    {
        Logger::Info("Frames in first animation: " + std::to_string(texData.animations[0].frames.size()));
    }

    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLACK, "Frame %llu", uFrameCount);

        sf::Time imGuiTime = clock.restart();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLUE, "Event & Input");
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            ImGui::SFML::ProcessEvent(window, event.value());
        }
        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_RED, "Update");
        ImGui::SFML::Update(window, imGuiTime);
        Logger::DrawLogger();
        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Draw");
        window.clear();
        
        window.draw(sprite); // <- draw le sprite ou le debugSprite
        
        ImGui::SFML::Render(window);
        window.display();
        PROFILER_EVENT_END();

        PROFILER_EVENT_END();
        ++uFrameCount;
    }

    globals.Destroy();
    ImGui::SFML::Shutdown();
    return 0;
}
