#include <SFML/Graphics.hpp>

#include <MainMenuScreen.hpp>

const std::string MainMenuScreen::MAIN_MENU_PLAY = "MAIN_MENU_PLAY";
const std::string MainMenuScreen::MAIN_MENU_EXIT = "MAIN_MENU_EXIT";

MainMenuScreen::MainMenuScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string backgroundImage) : Screen(window, dispatcher)
{
    MenuItem playItem;
    playItem.rect.top = 145;
    playItem.rect.height = 380 - 145;
    playItem.rect.left = 0;
    playItem.rect.width = 1024;
    playItem.action = [&]()
    {
        Event event(MainMenuScreen::MAIN_MENU_PLAY);
        this->getDispatcher().dispatch(event);
    };

    MenuItem exitItem;
    exitItem.rect.top = 383;
    exitItem.rect.height = 560 - 383;
    exitItem.rect.left = 0;
    exitItem.rect.width = 1024;
    exitItem.action = [&]()
    {
        Event event(MainMenuScreen::MAIN_MENU_EXIT);
        this->getDispatcher().dispatch(event);
    };

    _menuItems.push_back(playItem);
    _menuItems.push_back(exitItem);

    if (true == _texture.loadFromFile(backgroundImage))
    {
        _sprite = sf::Sprite(_texture);
    }
}

void MainMenuScreen::render() const
{
    this->getWindow().draw(_sprite);
    this->getWindow().display();
}

void MainMenuScreen::handleClick(int x, int y)
{
    sf::Vector2f worldPos = this->getWindow().mapPixelToCoords(sf::Vector2i(x, y));

    for (const MenuItem &item : _menuItems)
    {
        if (item.rect.top < worldPos.y && item.rect.top + item.rect.height > worldPos.y && item.rect.left < worldPos.x && item.rect.left + item.rect.width > worldPos.x)
        {
            // The point is inside the rectangle
            item.action();
        }
    }
}