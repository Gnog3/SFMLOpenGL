#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include "../SkyBox/SkyBox.hpp"
#include "../Crosshair/Crosshair.hpp"
class Engine {
    private:
        sf::Shader chunkShader;
        std::unique_ptr<SkyBox> skyBox;
        Crosshair crosshair;
        uint32_t blockTexture = 0;
        std::unique_ptr<std::thread> thread;
        volatile bool stopRequire = false;
        void thread_main();
        void draw();
        void sendMeshes();
    public:
        Engine();
        void start_thread();
};



