//
//  Puzzle.cpp
//  n_puzzle
//
//  Created by <tle-huu-> on 26/08/2018.
//
//

#include "Puzzle.hpp"
#include <string>
#include <algorithm>

Puzzle::Puzzle()
{}

Puzzle::Puzzle(int size)
{
	_grid.resize(size);
	for (auto & row : _grid) {
		row.resize(size);
	}
}

Puzzle::Puzzle(Puzzle const & src)
{
	_grid = src._grid;
	_blank = src._blank;
}

Puzzle & Puzzle::operator=(Puzzle const & src)
{
	_grid = src._grid;
	_blank = src._blank;
	return *this;
}

Puzzle::~Puzzle()
{}

void			Puzzle::setCell(int x, int y, int value)
{
	_grid[x][y] = value;
}
int				Puzzle::getCell(int x, int y) const
{
	return _grid[x][y];
}

void			Puzzle::setBlank(int i, int j)
{
	_blank.x = i;
	_blank.y = j;
}

std::size_t			Puzzle::getSize() const
{
	return _grid.size();
}

void			Puzzle::dump( void ) const
{
	for (int i = 0; i < getSize(); i++){
		for (int j = 0; j < getSize(); j++){
			std::cout << getCell(i, j) << " ";
		}
		std::cout << std::endl;
	}
	// std::cout << "Empty square is in ( " <<  _blank.x << "," << _blank.y << ")" << std::endl;
}


const Puzzle			Puzzle::move_right( void ) const
{
	int		value;
	Puzzle 		newPuzzle(*this);

	if (_blank.y > 0)
	{
		value = newPuzzle.getCell(newPuzzle._blank.x, newPuzzle._blank.y - 1);
		newPuzzle.setCell(_blank.x, _blank.y - 1, 0);
		newPuzzle.setCell(_blank.x, _blank.y, value);
		newPuzzle.setBlank(_blank.x, _blank.y - 1);
		return newPuzzle;
	}
	throw(MoveException());

}

const Puzzle			Puzzle::move_left( void ) const
{
	int			value;
	Puzzle 		newPuzzle(*this);

	if (_blank.y < _grid.size() - 1)
	{
		value = newPuzzle.getCell(newPuzzle._blank.x, newPuzzle._blank.y + 1);
		newPuzzle.setCell(_blank.x, _blank.y + 1, 0);
		newPuzzle.setCell(_blank.x, _blank.y, value);
		newPuzzle.setBlank(_blank.x, _blank.y + 1);
		return newPuzzle;
	}
	throw(MoveException());
}

Point			Puzzle::getBlank() const
{
	return this->_blank;
}


const Puzzle			Puzzle::move_down( void ) const
{
	int			value;
	Puzzle 		newPuzzle(*this);

	if (_blank.x > 0)
	{
		value = newPuzzle.getCell(newPuzzle._blank.x - 1, newPuzzle._blank.y);
		newPuzzle.setCell(_blank.x - 1, _blank.y, 0);
		newPuzzle.setCell(_blank.x, _blank.y, value);
		newPuzzle.setBlank(_blank.x - 1, _blank.y);

		return newPuzzle;
	}
	throw(MoveException());
}

const Puzzle			Puzzle::move_up( void ) const
{
	int			value;
	Puzzle 		newPuzzle(*this);

	if (_blank.x < _grid.size() - 1)
	{
		value = newPuzzle.getCell(newPuzzle._blank.x + 1, newPuzzle._blank.y);
		newPuzzle.setCell(_blank.x + 1, _blank.y, 0);
		newPuzzle.setCell(_blank.x, _blank.y, value);
		newPuzzle.setBlank(_blank.x + 1, _blank.y);
		return newPuzzle;
	}
	throw(MoveException());
}

std::vector<int>	Puzzle::getFlatGrid( void ) const
{
	auto flatten = _grid[0];

	for (int i = 1; i < _grid.size(); i++) {
		flatten.insert(end(flatten), begin(_grid[i]), end(_grid[i]));
	}
	flatten.erase(std::remove(flatten.begin(), flatten.end(), 0), flatten.end());
	return flatten;
}

const char *			Puzzle::MoveException::what() const throw() {

	return "Impossible Move";
}

std::string				Puzzle::toString( void ) const
{
	std::string		str;
	str.resize(_grid.size() * _grid[0].size());

	for (auto & row : _grid) {
		for (auto & x : row) {
			str += std::string(std::to_string(x));
		}
	}
	return str;
}

std::vector<std::vector<int> > Puzzle::copy_grid( void ) const
{
	return _grid;
}


bool Puzzle::operator==(const Puzzle& rhs) const
{
	if (this->getSize() != rhs.getSize()) {
		std::cout << "Size different :" << this->getSize() << " != " << rhs.getSize() << std::endl;
		this->dump();
		return false;
	}
	for (auto i = 0; i < this->getSize(); i++) {
		for (auto j = 0; j < this->getSize(); j++) {
			if (this->getCell(i, j) != rhs.getCell(i, j)) {
				// std::cout << " differ : " << this->getCell(i, j)<< " != "<< rhs.getCell(i, j)<< std::endl;
				return false;
			}
		}
	}
	return true;
}

bool Puzzle::operator!=(const Puzzle& rhs) const
{
	return !(*this == rhs);
}
