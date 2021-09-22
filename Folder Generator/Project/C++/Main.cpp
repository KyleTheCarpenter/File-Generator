#include <SFML/Graphics.hpp>
#define _WIN32_WINNT 0x0500
#include <iostream>

#include <direct.h>
#include <stdio.h>
#include <windows.h>
#include <ShellAPI.h>
#pragma comment(lib, "shell32")
void submit(std::string arg) {

    std::string withName = "c:/FolderGenerator/" + arg;
    std::string Project1 = "c:/FolderGenerator/" + arg+"/Project";
    std::string Project2 = "c:/FolderGenerator/" + arg + "/UML-Design";
    std::string Project3 = "c:/FolderGenerator/" + arg + "/Resources";
    std::string Project4 = "c:/FolderGenerator/" + arg + "/Market";
    std::string Project5 = "c:/FolderGenerator/" + arg + "/Versions";
    std::string Project6 = "c:/FolderGenerator/" + arg + "/Resources/3rd-Party";
    std::string Project7 = "c:/FolderGenerator/" + arg + "/Resources/Fonts";
    std::string Project8 = "c:/FolderGenerator/" + arg + "/Resources/Sounds";
    std::string Project9 = "c:/FolderGenerator/" + arg + "/UML-Design/Credits";
    std::string Project10 = "c:/FolderGenerator/" + arg + "/Market/PC";
    std::string Project11 = "c:/FolderGenerator/" + arg + "/Market/Mobile";
    _mkdir("c:/FolderGenerator");
    _mkdir(withName.c_str());
    _mkdir(Project1.c_str());
    _mkdir(Project2.c_str());
    _mkdir(Project3.c_str());
    _mkdir(Project4.c_str());
    _mkdir(Project5.c_str());
    _mkdir(Project6.c_str());
    _mkdir(Project7.c_str());
    _mkdir(Project8.c_str());
    _mkdir(Project9.c_str());
    _mkdir(Project10.c_str());
    _mkdir(Project11.c_str());

 
    ShellExecute(NULL, NULL, "c:/FolderGenerator", NULL, NULL, SW_SHOWNORMAL);

    

}
int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    sf::RenderWindow window(sf::VideoMode(300, 200), "Folder Generator",sf::Style::None);
    sf::RectangleShape exitButton(sf::Vector2f(27, 27));
    sf::RectangleShape submitButton(sf::Vector2f(132, 40));
    sf::Texture texture;
    sf::Sprite bg;
    sf::Color color(102, 102, 102,100);
    sf::Color colorClicked(102, 102, 102, 140);
    sf::Text data;
    sf::Font font;
    std::string enter;
    font.loadFromFile("arial.ttf");
    data.setFont(font);
    data.setCharacterSize(16);
    data.setFillColor(sf::Color::Black);
    data.setPosition(sf::Vector2f(30, 120));
    submitButton.setFillColor(color);
    exitButton.setFillColor(color);
    bool grabbed = false;
    bool sticky = false;
    exitButton.setPosition(sf::Vector2f(273, 0));
    submitButton.setPosition(sf::Vector2f(180, 160));
   
    texture.loadFromFile("bg.png");
    bg.setTexture(texture);
   
    auto mouse_pos = sf::Mouse::getPosition(window); 
    auto translated_pos = window.mapPixelToCoords(mouse_pos);
    
    bool exitbuttonHovered = false;
    float difference = 0;
    bool submitbuttonHovered = false;
    while (window.isOpen())
    {
       
        exitbuttonHovered = false;
        submitbuttonHovered = false;
        
        mouse_pos = sf::Mouse::getPosition(window);
        translated_pos = window.mapPixelToCoords(mouse_pos);
        
        if (exitButton.getGlobalBounds().contains(translated_pos)) {
            exitbuttonHovered = true;
        }
        if (submitButton.getGlobalBounds().contains(translated_pos)) {
            submitbuttonHovered = true;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            std::string temp;
         
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // handle backspace explicitly
                    if (!enter.empty()) {
                        enter.erase(enter.size() - 1, 1);
                        data.setString(enter);
                    }
                }
                else { // all other keypresses
                    if (enter.size() < 32) {
                        enter += static_cast<char>(event.text.unicode);
                        data.setString(enter);
                    }
                }
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (mouse_pos.y < 20) {
                  
                    sticky = true;

                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                sticky = false;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                   
                    if (exitbuttonHovered == true) {
                        window.close();
                    }
                    else if (submitbuttonHovered) {
                        submit(enter);
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(bg);
        window.draw(data);

        if (submitbuttonHovered == true)   window.draw(submitButton);
        if (exitbuttonHovered == true)   window.draw(exitButton);
       
        window.display();
    }

    return 0;
}