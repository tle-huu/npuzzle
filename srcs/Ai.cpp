//
//  Ai.cpp
//  n_puzzle
//
//  Created by <tle-huu-> on 01/09/2018.
//
//

#include "Ai.hpp"
#include <math.h>
#include <unistd.h>
#include <unordered_map>

/********************			UTILS		***********************/
int getInvCount(std::vector<int> init, std::vector<int> end)
{
	int		inv_count = 0;
	int		n = init.size();

	for (auto i = 0; i < n - 1; i++) {
		for (auto j = i + 1; j < n; j++) {
			if (((init[i] - init[j]) * (end[i] - end[j]) < 0))
				inv_count++;
		}
	}
	return inv_count;
}
/*************************************************************** */


Ai::Ai()
{}

Ai::Ai(std::unique_ptr<const Puzzle> && initial,
		std::unique_ptr<const Puzzle> && finall,
		std::string heuristic, bool greed) : _time_cost(0), _space_cost(0), _heuristic(heuristic), _greedy(greed)
{
	if (_count > 0)
		throw(TooManyAiException());
	if (initial->getSize() != finall->getSize())
		throw(PuzzleSizeException());
	_initial = std::move(initial);
	_final = std::move(finall);
	_count++;
}

Ai::Ai(Ai const & src)
{
	throw(TooManyAiException());
}

Ai & Ai::operator=(Ai const & src)
{
	throw(TooManyAiException());
}

Ai::~Ai()
{
	_count--;
}

int						Ai::heuristic(Puzzle const & puzzle, std::string h) const
{
	static std::unordered_map<std::string, int (Ai::*)(Puzzle const &) const> htable = {
		{"manhattan", &Ai::manhattan},
		{"hamming", &Ai::hamming},
		{"euclidean", &Ai::euclidean},
	};
	if (htable.count(h) <= 0)
		return (0);
	return this->manhattan(puzzle);
}

int						Ai::hamming(Puzzle const & puzzle) const
{
	auto cost = 0;

	for (auto i = 0; i < puzzle.getSize(); i++) {
		for (auto j = 0; j < puzzle.getSize(); j++) {
			if (puzzle.getCell(i, j) && (puzzle.getCell(i, j) != _final->getCell(i, j)))
				cost++;
		}
	}
	return cost;
}

int						Ai::euclidean(Puzzle const & puzzle) const
{
	auto cost = 0;

	for (auto i = 0; i < puzzle.getSize(); i++) {
		for (auto j = 0; j < puzzle.getSize(); j++) {
			if (puzzle.getCell(i , j) == 0)
				continue ;
			for (auto x = 0; x < puzzle.getSize(); x++) {
				for (auto y = 0; y < puzzle.getSize(); y++) {
					if (puzzle.getCell(i, j) == _final->getCell(x, y)) {
						cost += std::sqrt((x - i) * (x - i) + (y - j) * (y - j));
					}
				}
			}
		}
	}
	return cost;
}

int						Ai::manhattan(Puzzle const & puzzle) const
{
	auto cost = 0;

	// Need to create a hashmap to be more efficient
	for (auto i = 0; i < puzzle.getSize(); i++) {
		for (auto j = 0; j < puzzle.getSize(); j++) {
			if (puzzle.getCell(i , j) == 0)
				continue ;
			for (auto x = 0; x < puzzle.getSize(); x++) {
				for (auto y = 0; y < puzzle.getSize(); y++) {
					if (puzzle.getCell(i, j) == _final->getCell(x, y)) {
						cost += std::abs(x - i) + std::abs(y - j);
					}
				}
			}
		}
	}
	// puzzle.dump();
	// std::cout << "heursitic : " << cost << std::endl;
	return cost;
}



std::vector<std::size_t>			Ai::solve( void )
{
	std::priority_queue<Node>	queue;
	Node						current;
	std::vector<std::size_t>	stackzer;

	std::unordered_map<std::string, bool>		closed_set;

	queue.push(Node{Puzzle(*(this->_initial)), nullptr, std::vector<Node>(), -1, 0, -1});

	/* early exit */
	current = queue.top();
	_space_cost++;
	// std::cout << current.puzzle.getSize() << std::endl;;
	while (!queue.empty() && current.puzzle != *(this->_final))
	{
		current = queue.top();
		closed_set.insert(std::make_pair<std::string, bool>(current.puzzle.toString(), true));
		_time_cost++;
		queue.pop();
		getNextStates(current);
		for (auto & child : current.children) {
			_space_cost++;
			if (closed_set.count(child.puzzle.toString()) > 0)
				continue;
			child.f = child.g * !_greedy + this->heuristic(child.puzzle, _heuristic);
			queue.push(child);
		}
	}
	std::cout << "Creating the path" << std::endl;

	/*		Creating the path		*/
	while (current.puzzle != *(this->_initial))
	{
		stackzer.push_back(current.move);
		current = *current.parent;
	}
	return stackzer;
}

void					Ai::getNextStates(Node & node)
{
	std::shared_ptr<Node>	ptr1 = std::make_shared<Node>(node);

	std::shared_ptr<Node>	ptr2(ptr1);
	std::shared_ptr<Node>	ptr3(ptr1);
	std::shared_ptr<Node>	ptr4(ptr1);

	try {
		node.children.push_back(Node{node.puzzle.move_up(), ptr1, std::vector<Node>(), UP, 0, node.g + 1});
	}
	catch (Puzzle::MoveException & e) {
		// std::cout << "up impossible" << std::endl;
	}
	try {
		node.children.push_back(Node{node.puzzle.move_right(), ptr2, std::vector<Node>(), RIGHT, 0, node.g + 1});
	}
	catch (Puzzle::MoveException & e) {
		// std::cout << "right impossible" << std::endl;
	}
	try {
		node.children.push_back(Node{node.puzzle.move_down(), ptr3, std::vector<Node>(), DOWN, 0, node.g + 1});
	}
	catch (Puzzle::MoveException & e) {
		// std::cout << "down impossible" << std::endl;
	}
	try {
		node.children.push_back(Node{node.puzzle.move_left(), ptr4, std::vector<Node>(), LEFT, 0, node.g + 1});
	}
	catch (Puzzle::MoveException & e) {
		// std::cout << "left impossible" << std::endl;
	}
}

bool					Ai::isSolvable( void ) const
{
	std::vector<int>	init = _initial->getFlatGrid();
	std::vector<int>	end = _final->getFlatGrid();
	int					inv_count = getInvCount(init, end);

	return ( (_initial->getSize() % 2) && !(inv_count % 2) )
			|| ( !(_initial->getSize() % 2) && ( ((_initial->getBlank().x + 1) % 2) == !(inv_count % 2) ) );
}

std::size_t					Ai::getTimeCost( void ) const
{
	return _time_cost;
}
std::size_t					Ai::getSpaceCost( void ) const
{
	return _space_cost;
}

const char *			Ai::TooManyAiException::what() const throw() {

	return "An Ai already exists";
}

const char *			Ai::PuzzleSizeException::what() const throw() {

	return "Size of begin state and end state don t match";
}

/*********************** OVERLOAD ****************/
bool operator<(const Node& lhs, const Node& rhs)
{
	return lhs.f > rhs.f;
}

/********************** STATIC *************************/
std::size_t Ai::_count = 0;
