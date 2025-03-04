//Veli-Pekka Anttonen TTV15SP

//SFML includet
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//Omat includet
#include "Cube.h"
#include "Collision2D.h"
//Valamiit includet
#include <vector>
#include <Windows.h>
#include <iostream>


int main()
{
	//	Pid� n�� niin kaikki n�ytt�� OK!
	float Win_Wid = 960.f;
	float Win_Hei = 960.f;

	int Draw = 2;

	//Luodaan ikkuna
	sf::RenderWindow window(sf::VideoMode(Win_Wid, Win_Hei), "FysMotorV2");
	//Ikkunan paikan asettaminen n�yt�lle
	window.setPosition(sf::Vector2i(200, 25));
	//Ruudunp�ivityksen rajoittaminen (60fps)
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//Luodaan kello ja deltatime
	sf::Clock Clock;
	Clock.restart();
	float DeltaTime;

	//Luodaan s�ili� kuutioille ja sille iteraattori
	std::vector<Cube*>Cubes;
	std::vector<Cube*>::iterator Itr_Cube = Cubes.begin();
	std::vector<Cube*>::iterator Itr_Cube2 = Cubes.begin();
	//Luodaan s�ili� seinille ja sille iteraattori
	std::vector<Cube>Walls;
	std::vector<Cube>::iterator Itr_Wall = Walls.begin();

	//Luodaan kuutioita
	Cube* Cube1 = new Cube(sf::Vector2f(50, 50), sf::Vector2f(Win_Hei/2, Win_Wid/2), sf::Vector2f(0.f, 0.f));
	Cube1->Mass = 1.f;
	Cube1->angularVelocity = 0.0f;
	Cubes.push_back(Cube1);
	Cube* Cube2 = new Cube(sf::Vector2f(50, 50), sf::Vector2f(500, 300), sf::Vector2f(0.f, 0.f));
	Cube2->Mass = 10.f;
	Cubes.push_back(Cube2);
	Itr_Cube2 = Cubes.end();

	//Luodaan muutama convexshape
	//sf::ConvexShape Con1;
	//Con1.setPointCount(3);
	//Con1.setPoint(0, sf::Vector2f(300.f, 300.f));
	//Con1.setPoint(1, sf::Vector2f(300.f, 350.f));
	//Con1.setPoint(2, sf::Vector2f(350.f, 350.f));
	//Con1.setFillColor(sf::Color::Red);
	//Con1.setPosition(400, 400);

	//sf::ConvexShape Con2;
	//Con2.setPointCount(4);
	//Con2.setPoint(0, sf::Vector2f(300.f, 300.f));
	//Con2.setPoint(1, sf::Vector2f(300.f, 350.f));
	//Con2.setPoint(2, sf::Vector2f(350.f, 350.f));
	//Con2.setPoint(3, sf::Vector2f(350.f, 300.f));
	//Con2.setFillColor(sf::Color::Magenta);
	//Con2.setPosition(400, 500);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//Luodaan sein�t
	Cube Wall_Top(sf::Vector2f(Win_Wid, 50.f), sf::Vector2f(Win_Wid / 2.f, 0.f), sf::Vector2f(0.f, 0.f));
	Wall_Top.setColor(sf::Color::Cyan);
	Wall_Top.Mass = 100000.f;
	Walls.push_back(Wall_Top);
	Cube Wall_Bot(sf::Vector2f(Win_Wid, 50.f), sf::Vector2f(Win_Hei / 2.0f, Win_Hei), sf::Vector2f(0.f, 0.f));
	Wall_Bot.setColor(sf::Color::Cyan);
	Wall_Bot.Mass = 100000.f;
	Walls.push_back(Wall_Bot);
	Cube Wall_Lef(sf::Vector2f(50.f, Win_Hei), sf::Vector2f(0.f, Win_Wid / 2.0f), sf::Vector2f(0.f, 0.f));
	Wall_Lef.setColor(sf::Color::Cyan);
	Wall_Lef.Mass = 100000.f;
	Walls.push_back(Wall_Lef);
	Cube Wall_Rig(sf::Vector2f(50.f, Win_Hei), sf::Vector2f(Win_Wid, Win_Wid / 2.0f), sf::Vector2f(0.f, 0.f));
	Wall_Rig.setColor(sf::Color::Cyan);
	Wall_Rig.Mass = 100000.f;
	Walls.push_back(Wall_Rig);
	////////////////////////////////////////////////////////////////////////////////////////////////////

	//Luodaan t�rm�ystarkistus
	Collision2D Tarkistaja(&window);


	//Luodaan voimia
	sf::Vector2f Force(0.f, 0.f);
	sf::Vector2f Velocity(0.f, 0.f);

	sf::Event event;
	//Ikkuna Loop!
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			//Lopetusk�sky (n�pp�in 0 tai Esc)
			if (GetAsyncKeyState(0x30) || GetAsyncKeyState(0x1B)) //0 tai esc sammuttaa ohjelman
			{
				window.close();
				Sleep(200);
			}
		}
		//DeltaTimen asettaminen
		DeltaTime = Clock.restart().asSeconds();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		Velocity = sf::Vector2f(0.f, 0.f);
		//Jos painetaan nuolin�pp�imi�, jotain tulisi tapahtua
		Itr_Cube = Cubes.begin();
		if (GetAsyncKeyState(0x60))	//Numpad 0
		{
			//Force = sf::Vector2f(0.f, 0.f);
			Velocity = sf::Vector2f(0.f, 0.f);
			Cube1->Velocity = Velocity;
			Cube1->angularVelocity = 0;

			//Con2.move(sf::Vector2f(0.f, 0.f));
		}
		else if (GetAsyncKeyState(0x61)) //Numpad1
		{
			//Draw = 1;
			Cube1->angularVelocity += 1.f;
		}
		else if (GetAsyncKeyState(0x62)) //Numpad2
		{
			//Draw = 2;

			Cube1->angularVelocity -= 1.f;
		}
		else if (GetAsyncKeyState(0x63)) //Numpad3
		{
			Cube1->setPosition(sf::Vector2f(Win_Hei / 2, Win_Wid / 2));
			Cube2->setPosition(sf::Vector2f(Win_Hei / 2 + 100, Win_Wid / 2 + 100));

			Cube1->Velocity = Velocity;
			Cube1->angularVelocity = 0;

			Cube2->Velocity = Velocity;
			Cube2->angularVelocity = 0;
		}
		else if (GetAsyncKeyState(0x64)) //Numpad4
		{
			//	Tulostaa cube 1:n tiedot
			std::cout << "Cube1: " << std::endl;
			//std::cout << "Acceleration: " << Cube1->getAcceleration().x << " x, " << Cube1->getAcceleration().y << " y." << std::endl;
			std::cout << "Position: " << Cube1->getPosition().x << " x, " << Cube1->getPosition().y <<" y." << std::endl;
			std::cout << "Velocity:" << Cube1->getVelocity().x << " x, " << Cube1->getVelocity().y << " y." << std::endl << std::endl;
			std::cout << "AngularVelocity:" << Cube1->getAngularVelocity() << " degrees" << std::endl << std::endl;


		}
		else if (GetAsyncKeyState(0x65)) //Numpad5
		{
			//	Tulostaa cube 2:n tiedot
			std::cout << "Cube2: " << std::endl;
			//std::cout << "Acceleration: " << Cube2->getAcceleration().x << " x, " << Cube2->getAcceleration().y << " y." << std::endl;
			std::cout << "Position: " << Cube2->getPosition().x << " x, " << Cube2->getPosition().y << " y." << std::endl;
			std::cout << "Velocity:" << Cube2->getVelocity().x << " x, " << Cube2->getVelocity().y << " y." << std::endl << std::endl ;
		}
		else
		{

		}

		if (GetAsyncKeyState(0x26)) //Up arrow key
		{
			//Force = sf::Vector2f(0.f, -100.f);
			(*Itr_Cube)->Velocity += sf::Vector2f(0.f, -100.f) * DeltaTime;
			//Con2.move(sf::Vector2f(0.f, -10.f));
		}
		else if (GetAsyncKeyState(0x28)) //Down arrow key
		{
			//Force = sf::Vector2f(0.f, 100.f);
			(*Itr_Cube)->Velocity += sf::Vector2f(0.f, 100.f) * DeltaTime;
			//Con2.move(sf::Vector2f(0.f, 10.f));
		}
		else if (GetAsyncKeyState(0x25)) //Left arrow key
		{
			//Force = sf::Vector2f(-100.f, 0.f);
			(*Itr_Cube)->Velocity += sf::Vector2f(-100.f, 0.f) * DeltaTime;
			//Con2.move(sf::Vector2f(-10.f, 0.f));
		}
		else if (GetAsyncKeyState(0x27)) //Right arrow key
		{
			//Force = sf::Vector2f(100.f, 0.f);
			(*Itr_Cube)->Velocity += sf::Vector2f(100.f, 0.f) * DeltaTime;
			//Con2.move(sf::Vector2f(10.f, 0.f));
		}
		else
		{

		}



		////////////////////////////////////////////////////////////////////////////////////////////////////

		//Cubeille asioiden asettamista/p�ivitt�mist�
		//for (Itr_Cube = Cubes.begin(); Itr_Cube != Cubes.end(); Itr_Cube++)
		//{
		//	//Itr_Cube->setAcceleration(Force);
		//	if (Itr_Cube != Cubes.begin())
		//	{	
		//		//	T�m� rikkoi b:n liikkumisen (se ei liikkunut minnekk��n)
		//		//(*Itr_Cube)->setVelocity(Velocity);
		//	}
		//	//Cube2.setVelocity(Velocity);
		//}




		//Tarkistaja.SAT(Con1, Con2);
		//T�rm�yksen tarkistus
		//Tarkistaja.SAT(Cube1.CubeShape, Cube2.CubeShape);
		Tarkistaja.SAT(*Cubes.at(0), *Cubes.at(1));

		for (auto w : Walls)
		{
			Tarkistaja.SAT(w, *Cubes.at(0));
			Tarkistaja.SAT(w, *Cubes.at(1));
		}
		//Ikkunan putsaus
		window.clear();

		////////////////////////////////////////////////////////////////////////////////////////////////////

		//Cubejen p�ivitys ja piirto
		for (Itr_Cube = Cubes.begin(); Itr_Cube != Cubes.end(); Itr_Cube++)
		{
			(*Itr_Cube)->Update(DeltaTime);

			if (Draw == 1)
			{
				//(*Itr_Cube)->DrawCubeShape(window);
			}
			else if (Draw == 2)
			{
				(*Itr_Cube)->DrawConvexShape(window);
			}

			//std::cout << Itr->Velocity.x << " " << Itr->Velocity.y << std::endl;
		}
		//std::cout << Force.x << " " << Force.y << std::endl;
		//std::cout << DeltaTime << std::endl;
		//std::cout << Velocity.x << " " << Velocity.y << std::endl;




		////////////////////////////////////////////////////////////////////////////////////////////////////

		//Seinien piirto ja p�ivitys
		for (Itr_Wall = Walls.begin(); Itr_Wall != Walls.end(); Itr_Wall++)
		{
			Itr_Wall->Update(DeltaTime);

			Itr_Wall->DrawConvexShape(window);

		}

		////////////////////////////////////////////////////////////////////////////////////////////////////

		//window.draw(Con1);
		//window.draw(Con2);

		//sf::VertexArray lines(sf::LinesStrip, 4);
		//lines[0].position = sf::Vector2f(10, 10);
		//lines[1].position = sf::Vector2f(20, 20);
		//lines[2].position = sf::Vector2f(10, 20);
		//lines[3].position = sf::Vector2f(20, 10);
		//window.draw(lines);

		Tarkistaja.DrawCollisionPoint();

		window.display();
	}

	for (auto c : Cubes)
	{
		auto tmp = c;
		c = nullptr;
		delete tmp;
	}

	return 0;
}
