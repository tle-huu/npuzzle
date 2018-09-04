//Declaration
#include "Drawer.hpp"

#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3

Drawer::Drawer()
{
	for (int i = 0; i < 16; ++i)
	{
		sf::Texture texture;
		texture.loadFromFile("sprites/" + std::to_string(i) + ".png");
		_textures.push_back(texture);
	}
}

Drawer::Drawer(std::vector<std::vector<int> > && grid, std::vector<std::size_t> & stackzer) : Drawer()
{
	_grid = grid;
	_stack = stackzer;
	for (auto i = 0; i < _grid.size(); i++) {
		for (auto j = 0; j < _grid.size(); j++) {
			if (_grid[i][j] == 0) {
				_blank.x = i;
				_blank.y = j;
				break;
			}
		}
	}
}

void		Drawer::_move(bool forward)
{
	std::size_t			nextmove;
	int					value;
	static int			i = _stack.size() - 1;
	static bool			last = true;

	if (i < 0 && forward)
		return ;
	if (i >= static_cast<int>(_stack.size()) && !forward)
		return ;
	if (forward && last) {
		last = true;
		nextmove = _stack[i];
	}
	else if (forward) {
		last = true;
		nextmove = _stack[--i];
	}
	else if (last)
	{
		last = false;
		nextmove = (_stack[++i] + 2) % 4;
	}
	else {
		last = false;
		nextmove = (_stack[i] + 2) % 4;
	}
	if (nextmove == UP) {
		value = _grid[_blank.x][_blank.y];
		_grid[_blank.x][_blank.y] = _grid[_blank.x + 1][_blank.y];
		_grid[_blank.x + 1][_blank.y] = value;
		_blank.x++;
	}
	else if (nextmove == RIGHT) {
		value = _grid[_blank.x][_blank.y];
		_grid[_blank.x][_blank.y] = _grid[_blank.x][_blank.y - 1];
		_grid[_blank.x][_blank.y - 1] = value;
		_blank.y--;
	}
	else if (nextmove == DOWN) {
		value = _grid[_blank.x][_blank.y];
		_grid[_blank.x][_blank.y] = _grid[_blank.x - 1][_blank.y];
		_grid[_blank.x - 1][_blank.y] = value;
		_blank.x--;
	}
	else if (nextmove == LEFT) {
		value = _grid[_blank.x][_blank.y];
		_grid[_blank.x][_blank.y] = _grid[_blank.x][_blank.y + 1];
		_grid[_blank.x][_blank.y + 1] = value;
		_blank.y++;
	}
	else
	{
		std::cout << "Error : " << nextmove << std::endl;
	}
	if (forward)
		i--;
	else
		i++;
}


void Drawer::DrawField()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "N Puzzle"); // Draw window
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					if (event.key.code == sf::Keyboard::Return)
						_move(true);
					else if (event.key.code == sf::Keyboard::BackSpace)
						_move(false);
				}
		}

		sf::Sprite temp;

		window.clear();
		for (int i = 0; i < _grid.size(); i++)
		{
			for (auto j = 0; j < _grid.size(); j++)
			{
				temp.setTexture(_textures[_grid[i][j]]);
				//temp.setPosition(i*100,j*100);
				temp.setPosition(j * 100, (i * 100));
				window.draw(temp);
			}
		}
		window.display();
	}

}
