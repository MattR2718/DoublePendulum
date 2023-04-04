#include <iostream>
#include <vector>
#include <ranges>

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "light.h"
#include "sphere.h"
#include "pendulum.h"
#include "guiData.h"

void initPixels(sf::Uint8 *arr, const int length, sf::Uint8* colour){
    for (int i = 0; i < length; i += 4){
        arr[i] = colour[0];
        arr[i + 1] = colour[1];
        arr[i + 2] = colour[2];
        arr[i + 3] = 255;
    }
}

int main(){
    const int WIDTH = sf::VideoMode::getDesktopMode().width * 0.95;
    const int HEIGHT = sf::VideoMode::getDesktopMode().height * 0.95;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double Pendulum");
    window.setPosition(sf::Vector2i(0, 0));
    auto _ = ImGui::SFML::Init(window);
    //ImGui::CreateContext();

    sf::Uint8 backgroundColour[3] = {128, 200, 200};
    sf::Uint8* pixels  = new sf::Uint8[WIDTH * HEIGHT * 4];
    initPixels(pixels, WIDTH * HEIGHT * 4, backgroundColour);

    Light light(1, -1, 1);

    Sphere s(0, 0, 0, 250, 255, 255, 255, 255);

    Pendulum pendulum(0, -HEIGHT/2 * 0.6, 0);
    GuiData guiData;

    
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        ImGui::SFML::ProcessEvent(window, event);
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        if(guiData.clearPixels){
            initPixels(pixels, WIDTH * HEIGHT * 4, backgroundColour);
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Options", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowFontScale(2);
        if(ImGui::CollapsingHeader("Light")){
            ImGui::SliderFloat("X Dir", &light.dx, -1, 1);
            ImGui::SliderFloat("Y Dir", &light.dy, -1, 1);
            ImGui::SliderFloat("Z Dir", &light.dz, -1, 1);
        }
        if(ImGui::CollapsingHeader("Demo Sphere")){
            ImGui::Checkbox("Show Sphere", &guiData.showDemoSphere);
            ImGui::SliderInt("X Pos", &s.x, -WIDTH/2, WIDTH/2);
            ImGui::SliderInt("Y Pos", &s.y, -HEIGHT/2, HEIGHT/2);
            ImGui::SliderInt("Z Pos", &s.z, -WIDTH/2, WIDTH/2);
        }

        if(ImGui::CollapsingHeader("Options", ImGuiTreeNodeFlags_DefaultOpen)){
            ImGui::Checkbox("Clear Pixels Each Frame", &guiData.clearPixels);
            if(ImGui::Button("Clear Pixels")){
                initPixels(pixels, WIDTH * HEIGHT * 4, backgroundColour);
            }

            ImGui::Checkbox("Draw Lines", &pendulum.drawLines);
            
            ImGui::SliderInt("Mass1", &guiData.m1, 0, 100);
            ImGui::SliderInt("Mass2", &guiData.m2, 0, 100);
            ImGui::SliderInt("Length1", &guiData.l1, 0, 1000);
            ImGui::SliderInt("Length2", &guiData.l2, 0, 1000);

            ImGui::SliderAngle("Theta1", &guiData.tx1, -90, 90);
            ImGui::SliderAngle("Theta2", &guiData.tx2, -90, 90);
            ImGui::SliderFloat("Damping", &guiData.damping, 0.99, 1);
            ImGui::SliderFloat("Gravity (g)", &guiData.g, 0, 20);

            if(ImGui::Button("Update Simulation")){
                pendulum.updateFromGui(guiData);
            }
        }

        ImGui::End();

        if(guiData.showDemoSphere){
            s.draw(pixels, WIDTH, HEIGHT, light);
        }

        pendulum.draw(pixels, WIDTH, HEIGHT, light);
        
        //Create an sf::image which will be load the pixels
        sf::Image image;
        image.create(WIDTH, HEIGHT, pixels);
        //Create an sf::texture and load the image to the texture
        sf::Texture texture;
        texture.loadFromImage(image);
        //Create an sf::sprite and draw the sprite to the screen
        sf::Sprite sprite(texture);
        window.draw(sprite);
        
        ImGui::SFML::Render(window);
        window.display();
    }
    
    delete[] pixels;
    //ImGui::DestroyContext();
    ImGui::SFML::Shutdown();
}