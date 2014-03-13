#include <SFML/Graphics.hpp>

#include <iostream>

#include "midpointdisplacement.h"

sf::VertexArray Generate() {
  MidpointDisplacement diamond_square = MidpointDisplacement(5, 8, 8, 2.6, 1.2);
  std::vector<int> map = diamond_square.GetMap();
  sf::VertexArray vertices;
  vertices.setPrimitiveType(sf::Points);
  vertices.resize(diamond_square.width() * diamond_square.height());

  std::cout << "W: " << diamond_square.width() << "H: " << diamond_square.height() << std::endl;
  //map.resize((diamond_square.width() - 1) * (diamond_square.height() - 1));

  for (unsigned int i = 0; i < map.size(); i++) {
    sf::Vertex* point = &vertices[i];
    
    int y = i / (diamond_square.width());
    int x = i % (diamond_square.width());
    point[0].position = sf::Vector2f(x, y);
    sf::Color color;
      switch(map.at(i)) {
      case 0: {
        color = sf::Color::Color(255, 0, 255);
        break;
      }
      case 1: {
        color = sf::Color::Color(7, 93, 192);
        break;
      }
      case 2: {
        color = sf::Color::Color(74, 157, 251);
        break;
      }
      case 3: {
        color = sf::Color::Color(255, 238, 178);
        break;
      }
      case 4: {
        color = sf::Color::Color(7, 192, 53);
        break;
      }
      case 5: {
        color = sf::Color::Color(32, 139, 58);
        break;
      }
      case 6: {
        color = sf::Color::Color(147, 188, 157);
        break;
      }
      case 7: {
        color = sf::Color::Color(129, 141, 132);
        break;
      }
      case 8: {
        color = sf::Color::White;
        break;
      }
      }
    //color = sf::Color(map.at(i), map.at(i), map.at(i));
    point[0].color = color;
  }
  return vertices;
}

int main()
{
  
  sf::RenderWindow window(sf::VideoMode(800, 600), "Terrain Generation");
  sf::VertexArray image;
  //sf::RenderStates states;
  sf::Transform transform;

  bool load = true;
  //float scale = 1.0f;
  
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
      else if (event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Return) {
          transform = sf::Transform();
          if (!load)
            load = true;
        } else if (event.key.code == sf::Keyboard::Add) {
         // std::cout << " Q";
          //scale += .1f;
          transform.scale(1.9f, 1.9f);
          //states.transform = transform;
        } else if (event.key.code == sf::Keyboard::Subtract) {
          //std::cout << "W";
          //scale -= .1f;
          //transform.setS(scale);
          transform.scale(.9f, .9f);
          //states.transform = transform;
        } else if (event.key.code == sf::Keyboard::W) {
          transform.translate(0, +10);
        } else if (event.key.code == sf::Keyboard::A) {
          transform.translate(+10, 0);
        } else if (event.key.code == sf::Keyboard::S) {
          transform.translate(0, -10);
        } else if (event.key.code == sf::Keyboard::D) {
          transform.translate(-10, 0);
        }
      }
		}

    if (load == true) {
      image = Generate();
      load = false;
    }

    window.clear();
    window.draw(image, transform);
    window.display();
	}
	return 0;
}