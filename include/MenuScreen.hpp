#include <Screen.hpp>
#include <Menu.hpp>

class MenuScreen : public Screen
{
public:
    MenuScreen(sf::RenderWindow &window, Dispatcher &dispatcher, Menu menu);

    void render() const;
    void handleClick(int x, int y);
    const Menu &getMenu() const;

private:
    const Menu _menu;
};