//Definition
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Puzzle.hpp"
#include <stack>

class Drawer
{
	private:
		struct Point {
			int		x;
			int		y;
		};

		std::vector<std::vector<int> >	_grid;
		Point							_blank;
		std::vector<sf::Texture>	_textures;
		std::vector<std::size_t>		_stack;
		Drawer();

		sf::RenderWindow window;
	public:

		Drawer(std::vector<std::vector<int> > && , std::vector<std::size_t> &);

		void		_move( bool );

		void DrawField();

};
