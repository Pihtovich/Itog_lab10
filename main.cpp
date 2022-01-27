#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <list>
#include <windows.h>

using namespace std;
using namespace sf;

float winWidth = 800.f;
float winHeigth = 600.f;

class Entity
{
public:
	float x, y, speed;
	float dx, dy; // знак координат x и y
	int w, h;
	bool isMove, life;
	Texture texture;
	Sprite sprite;

	Entity(Image& image, float X, float Y, float W, float H)
	{
		speed = 0;
		x = X; y = Y;
		dx = 0; dy = 0;
		w = W;  h = H;
		isMove = false, life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
public:
	Sprite GetSprite()
	{
		return sprite;
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
};

class Player : public Entity
{
public:
	bool isShoot = false;
	enum { left, right, up, down } state;
	Player(Image& image, float X, float Y, float W, float H) : Entity(image, X, Y, W, H)
	{
		sprite.setOrigin(w / 2, h / 2);
	}

	void control(float time)
	{
		if (Keyboard::isKeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				state = left; speed = 0.5;
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				state = right; speed = 0.5;

			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				state = up; speed = 0.5;

			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				state = down; speed = 0.5;

			}
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				isShoot = true;
			}
		}
	}

	void update(float time)
	{
		control(time);
		switch (state)
		{
		case left: dx = -speed; break;
		case right: dx = speed; break;
		case up: dy = speed; break;
		case down: dy = -speed; break;
		}

		if (!isMove) { speed = 0; }

		x += dx * time;
		y += dy * time;

		sprite.setPosition(x + w / 2, y + h / 2);
	}
};

class Bullet :public Entity
{
public:
	Bullet(Image& image, float X, float Y, int W, int H) :Entity(image, X, Y, W, H)
	{
		x = X;
		y = Y;
		speed = 0.8;
		life = true;
		w = h = 50;
	}
	void update(float time)
	{
		y += speed * time;
		sprite.setPosition(x + w / 2, y + h / 2);
	}
};

int main()
{
	string nameWindow = "there's nothing here!";
	RenderWindow window(VideoMode(winWidth, winHeigth), nameWindow);
	
	Image playerimage;
	playerimage.loadFromFile("images/player.png");
	Player p(playerimage, 0, 0, 190, 190);

	Image bulletImage;
	bulletImage.loadFromFile("images/bullet.png");

	Image AsteroidImage;
	AsteroidImage.loadFromFile("images/asteroid.png");

	std::list<Entity*> entities;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator it2;

	Clock clock;
	while (window.isOpen())
	{
		Event event;
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1400;
		
		while (window.pollEvent(event))
		{
			if (event.type = Event::Closed)
			{
				window.close();
			}
			if (p.isShoot == true) {
				p.isShoot = false;

			}
		}
		p.update(time);

		window.clear();
		
		window.draw(p.GetSprite());
		window.display();
	}
	return 0;
}

