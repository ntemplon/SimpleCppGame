#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include <Game.hpp>

using namespace std;

/**
 * @brief Runs the Simple C++ Game.
 *
 * @return int The program exit code.
 */
int main(int, char **)
{
    // Create a game and start it
    Game g;
    g.start();

    // If we didn't error out before here, exit with code 0.
    return 0;
}
