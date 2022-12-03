#include "Sand.h"
#include "Grid.h"


int main()
{
    srand(static_cast <unsigned> (time(0)));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    sf::Vector2f sizeParticle(5.f, 5.f);
    Grid grid(sizeParticle, window.getSize());

    int selector{ int(Type::Sand) };
    int nbType{ 6 }; // TENIR A JOUR
    int fps{ 0 };
    sf::Clock fpsClock;
    sf::Font font;
    sf::Text textMatter;
    sf::Text textFps;

    font.loadFromFile("JAi_____.ttf");

    textMatter.setFont(font);
    textMatter.setCharacterSize(35);
    textMatter.setPosition(sf::Vector2f(5.f, 12.f));

    textFps.setFont(font);
    textFps.setCharacterSize(15);
    textFps.setPosition(sf::Vector2f(0.f, 0.f));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelMoved) {
                grid.changeSizeNewDeleteMatter(event.key.code);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    selector--;
                    if (selector < 0)
                        selector = 0;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    selector++;
                    if (selector >= nbType)
                        selector = nbType - 1;
                }
            }
        }

        switch (selector)
        {
            case int(Type::Vacuum) :
                break;
            case int(Type::Sand):
                textMatter.setString("Sand");
                textMatter.setFillColor(sf::Color(225, 185, 0));
                break;
            case int(Type::Water):
                textMatter.setString("Water");
                textMatter.setFillColor(sf::Color(0, 0, 225));
                break;
            case int(Type::Rock):
                textMatter.setString("Rock");
                textMatter.setFillColor(sf::Color(110, 110, 110));
                break;
            case int(Type::Powder):
                textMatter.setString("Powder");
                textMatter.setFillColor(sf::Color(80, 80, 80));
                break;
            case int(Type::Spark):
                textMatter.setString("Spark");
                textMatter.setFillColor(sf::Color(150, 50, 0));
                break;
            default:
                break;
        }

        fps++;
        if (fpsClock.getElapsedTime().asSeconds() > 0.05f) {
            textFps.setString("FPS : " + std::to_string(int(float(fps) / fpsClock.getElapsedTime().asSeconds())));
            fpsClock.restart();
            fps = 0;
        }



        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            grid.newMatter(sf::Vector2f(sf::Mouse::getPosition(window)), Type(selector));
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            grid.deleteMatter(sf::Vector2f(sf::Mouse::getPosition(window)), Type(selector));




        grid.loop();

        window.clear();

        int sizeNewDeleteMatter{ grid.getSizeNewDeleteMatter() };
        int i{ int(sf::Mouse::getPosition(window).x / sizeParticle.x) };
        int j{ int(sf::Mouse::getPosition(window).y / sizeParticle.y) };
        sf::RectangleShape mouseRec(sizeParticle);
        mouseRec.setFillColor(sf::Color(30, 30, 30));

        for (int i0{ -sizeNewDeleteMatter }; i0 <= sizeNewDeleteMatter; i0++) {
            for (int j0{ -sizeNewDeleteMatter }; j0 <= sizeNewDeleteMatter; j0++) {
                if (int(sqrt(pow(i0, 2) + pow(j0, 2))) < sizeNewDeleteMatter && i + i0 >= 0 && j + j0 >= 0 && i + i0 < grid.getSize().x && j + j0 < grid.getSize().y) {
                    mouseRec.setPosition(sf::Vector2f((i + i0) * sizeParticle.x, (j + j0) * sizeParticle.y));

                    window.draw(mouseRec);
                }
            }
        }

        grid.show(&window);
        window.draw(textMatter);
        window.draw(textFps);
        window.display();
    }

    return 0;
}