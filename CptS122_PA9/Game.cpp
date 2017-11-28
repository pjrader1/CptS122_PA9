#include "Game.h"

Game::Game()
	:_window(sf::VideoMode(1280,720), "CptS 122 Game") {
	createLevel();
}

Game::~Game() {
	while (_gameObjects.begin() != _gameObjects.end()) {
		GameObject* gameObject = *_gameObjects.begin();
		delete gameObject;
		_gameObjects.erase(_gameObjects.begin());
	}
}

void Game::run() {
	sf::Clock dtClock;
	while (_window.isOpen()) {
		sf::Event event;
		while(_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_window.close();
			}
		}

		// Update
		sf::Time elapsed = dtClock.restart();
		updateAll(elapsed);

		// Render
		_window.clear();
		drawAll();
		_window.display();
	}
}

void Game::createLevel() {
	_gameObjects.insert(new Player());
	_gameObjects.insert(new Floor(sf::Vector2f(400.0f, 600.0f), 300, 20)); // Bottom floor
	_gameObjects.insert(new Floor(sf::Vector2f(700.0f, 300.0f), 20, 300)); // Right floor
}

void Game::updateAll(const sf::Time& dt) {
	for (std::set<GameObject*>::iterator iterator = _gameObjects.begin();
		iterator != _gameObjects.end();
		iterator++) {
		GameObject* gameObject = *iterator;

		gameObject->update(_gameObjects, dt);
	}
}
void Game::drawAll() {
	for (std::set<GameObject*>::iterator iterator = _gameObjects.begin();
		iterator != _gameObjects.end();
		iterator++) {
		GameObject* gameObject = *iterator;

		gameObject->draw(_window);
	}
}