#include <SFML/Graphics.hpp>

#include <MainMenuScreen.hpp>

MainMenuScreen::MainMenuScreen(sf::RenderWindow &window) : Screen(window)
{
    this->_currentResult = MainMenuScreen::MenuResult::Nothing;

    MenuItem playItem;
    playItem.rect.top = 145;
    playItem.rect.height = 380 - 145;
    playItem.rect.left = 0;
    playItem.rect.width = 1024;
    playItem.action = MainMenuScreen::MenuResult::Play;

    MenuItem exitItem;
    exitItem.rect.top = 383;
    exitItem.rect.height = 560 - 383;
    exitItem.rect.left = 0;
    exitItem.rect.width = 1024;
    exitItem.action = MainMenuScreen::MenuResult::Exit;

    _menuItems.push_back(playItem);
    _menuItems.push_back(exitItem);
}

void MainMenuScreen::render() const
{
    this->getWindow().draw(_sprite);
    this->getWindow().display();
}

void MainMenuScreen::handleClick(int x, int y)
{
    for (const MenuItem &item : _menuItems)
    {
        if (item.rect.top < y && item.rect.top + item.rect.height > y && item.rect.left < x && item.rect.left + item.rect.width > x)
        {
            // The point is inside the rectangle
            this->setCurrentResult(item.action);
        }
    }
}

MainMenuScreen::MenuResult MainMenuScreen::getCurrentResult()
{
    return this->_currentResult;
}

void MainMenuScreen::setCurrentResult(MainMenuScreen::MenuResult result)
{
    this->_currentResult = result;
}