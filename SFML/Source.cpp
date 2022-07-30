#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

const int width = 410;
const int height = 235;

using namespace sf;
using std::thread;

void move_comp(int* arr)
{
	srand(time(0));
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		if (arr[1] > 5) arr[1] -= 5;
		break;
	case 1:
		if (arr[0] > 5) arr[0] -= 5;
		break;
	case 2:
		if (arr[1] < 220) arr[1] += 5;
		break;
	case 3:
		if (arr[0] < 370) arr[0] += 5;
		break;
	}
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(width, height), "Chase Game");
	int coords_player[2] = { 140, 110 };
	int coords_comp[2] = { 270, 110 };

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		//paint window
		window.clear(Color(173, 216, 230, 0));
		//create rectanlges
		RectangleShape player(Vector2f(25.f, 25.f));
		player.setFillColor(Color(255, 0, 0, 200));
		player.setPosition(coords_player[0], coords_player[1]);
		window.draw(player);

		RectangleShape comp(Vector2f(25.f, 25.f));
		comp.setFillColor(Color(0, 0, 0, 200));
		comp.setPosition(coords_comp[0], coords_comp[1]);
		window.draw(comp);

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W && coords_player[1] > 5) coords_player[1] -= 5;
				if (event.key.code == Keyboard::A && coords_player[0] > 5)	coords_player[0] -= 5;
				if (event.key.code == Keyboard::S && coords_player[1] < 370) coords_player[1] += 5;
				if (event.key.code == Keyboard::D && coords_player[0] < 570) coords_player[0] += 5;
			}
		}

		thread thread(move_comp, coords_comp);
		thread.detach();
		if (abs(coords_player[1] - coords_comp[1]) <= 15 && abs(coords_player[0] - coords_comp[0]) <= 15)
		{
			sleep(milliseconds(2000));
			exit(0);
		}
		window.display();
	}

	return 0;
}