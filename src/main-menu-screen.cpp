#include <SFML/Graphics.hpp>

#include <MainMenuScreen.hpp>

const std::string MainMenuScreen::MAIN_MENU_PLAY = "MAIN_MENU_PLAY";
const std::string MainMenuScreen::MAIN_MENU_EXIT = "MAIN_MENU_EXIT";

MainMenuScreen::MainMenuScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string backgroundImage) : Screen(window, dispatcher)
{
    // TODO: change the implementation of this so the MenuItems are directly rendered instead of magic numbers making invisible
    // rectangles match with the lines on the impage drawn underneath.

    // Define the 'Play' menu item
    MenuItem playItem;
    playItem.rect.top = 145;
    playItem.rect.height = 380 - 145;
    playItem.rect.left = 0;
    playItem.rect.width = 1024;
    playItem.action = [&]()
    {
        // If the user clicks play, tell whoever is listening we'd like to play the game
        Event event(MainMenuScreen::MAIN_MENU_PLAY);
        this->getDispatcher().dispatch(event);
    };

    // Define the 'Exit' menu item
    MenuItem exitItem;
    exitItem.rect.top = 383;
    exitItem.rect.height = 560 - 383;
    exitItem.rect.left = 0;
    exitItem.rect.width = 1024;
    exitItem.action = [&]()
    {
        // If the user clicks play, tell whoever is listening we'd like to exit the game
        Event event(MainMenuScreen::MAIN_MENU_EXIT);
        this->getDispatcher().dispatch(event);
    };

    _menuItems.push_back(playItem);
    _menuItems.push_back(exitItem);

    // Load the image
    if (true == _texture.loadFromFile(backgroundImage))
    {
        _sprite = sf::Sprite(_texture);
    }
}

void MainMenuScreen::render() const
{
    // Draw the background image
    this->getWindow().clear(sf::Color(0, 0, 0));
    this->getWindow().draw(_sprite);
    this->getWindow().display();
}

void MainMenuScreen::handleClick(int x, int y)
{
    // Convert from pixels to world coordinates. This will account for any view transformations that have happened to the window.
    sf::Vector2f worldPos = this->getWindow().mapPixelToCoords(sf::Vector2i(x, y));

    for (const MenuItem &item : _menuItems)
    {
        // If the user clicked on the item, invoke its action
        if (item.rect.top < worldPos.y && item.rect.top + item.rect.height > worldPos.y && item.rect.left < worldPos.x && item.rect.left + item.rect.width > worldPos.x)
        {
            // The point is inside the rectangle
            item.action();
        }
    }
}