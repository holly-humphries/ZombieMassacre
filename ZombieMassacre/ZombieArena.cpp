#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
	State state = State::GAME_OVER; 

	sf::Vector2f resolution; 
	resolution.x = sf::VideoMode::getDesktopMode().width; 
	resolution.y = sf::VideoMode::getDesktopMode().height; 
	sf::RenderWindow window(
		sf::VideoMode(resolution.x, resolution.y),
		"Zombie Arena",
		sf::Style::Fullscreen
	); 

	sf::View mainView(
		sf::FloatRect(0, 0, resolution.x, resolution.y)
	); 

	sf::Clock clock; 
	sf::Time gameTimeTotal; 

	sf::Vector2f mouseWorldPosition; 
	sf::Vector2i mouseScreenPosition; 

	Player player; 

	sf::IntRect arena; 


	while (window.isOpen())
	{

		sf::Event event; 
		while (window.pollEvent(event))
		{
			// Pause the game while playing 
			if (event.key.code == sf::Keyboard::Return &&
				state == State::PLAYING)
			{
				state = State::PAUSED;
			}
			// Restart while paused
			else if (event.key.code == sf::Keyboard::Return &&
					state == State::PAUSED)
			{
				state = State::PLAYING; 
				// Reset the clock so there isn't a frame jump
				clock.restart(); 
			}
			// Start a new game while in GAME_OVER state 
			else if (event.key.code == sf::Keyboard::Return &&
				state == State::GAME_OVER)
			{
				state = State::LEVELING_UP; 
			}
			if (state == State::PLAYING)
			{
				// Additional input logic will be added here 
			}
		}
		// Game logic will go here 

		// Handle the player quitting 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close(); 
		}
		// Handle WASD while playing 
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of WASD keys 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp(); 
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.moveDown(); 
			}
			else
			{
				player.stopDown(); 
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.moveLeft(); 
			}
			else
			{
				player.stopLeft(); 
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.moveRight(); 
			}
			else
			{
				player.stopRight(); 
			}

		} // End WASD while playing

		if (state == State::LEVELING_UP)
		{
			// Handle the player leveling up
			if (event.key.code == sf::Keyboard::Num1) { state = State::PLAYING; }
			if (event.key.code == sf::Keyboard::Num2) { state = State::PLAYING; }
			if (event.key.code == sf::Keyboard::Num3) { state = State::PLAYING; }
			if (event.key.code == sf::Keyboard::Num4) { state = State::PLAYING; }
			if (event.key.code == sf::Keyboard::Num5) { state = State::PLAYING; }
			if (event.key.code == sf::Keyboard::Num6) { state = State::PLAYING; }

			if (state == State::PLAYING)
			{
				// Prepare the level 
				arena.width = 500; 
				arena.height = 500; 
				arena.left = 0; 
				arena.top = 0; 
				int tileSize = 50; 
				// Spawn the player in the middle of the arena 
				player.spawn(arena, resolution, tileSize); 

				// Reset clock so there isn't a frame jump
				clock.restart(); 
			}
		} // End LEVELING_UP 

		if (state == State::PLAYING)
		{
			// Update the delta time
			sf::Time dt = clock.restart(); 

			// Update the total game time
			gameTimeTotal += dt; 

			// Make a fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds(); 

			// Where is the mouse pointer
			mouseScreenPosition = sf::Mouse::getPosition(); 

			// Convert mouse position to world-based coordinates of main view 
			mouseWorldPosition = window.mapPixelToCoords(
				sf::Mouse::getPosition(), mainView); 

			// Update the player
			player.update(dtAsSeconds, sf::Mouse::getPosition()); 

			// Make a note of the player's new position 
			sf::Vector2f playerPosition(player.getCenter()); 

			// Make the view center around the player 
			mainView.setCenter(player.getCenter()); 

		} // End updating the scene 

		if (state == State::PLAYING)
		{
			window.clear(); 
			// Set the main view to be displayed in the window
			// Draw everything related to it
			window.setView(mainView); 
			// Draw the player
			window.draw(player.getSprite()); 
		}
		if (state == State::LEVELING_UP)
		{
			// Handle drawing elements for levelling up 
		}
		if (state == State::PAUSED)
		{
			// Handle drawing elements for paused state
		}
		if (state == State::GAME_OVER)
		{
			// Handle drawing elements for game over state 
		}
		window.display(); 
	}

	return 0; 
}