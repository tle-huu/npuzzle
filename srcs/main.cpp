#include <iostream>
#include <string>
#include "Parser.hpp"
#include "Puzzle.hpp"
#include "Ai.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <time.h>
#include "Drawer.hpp"

void		print_move(int i)
{
	if (i == 1) {
		std::cout << "UP" << std::endl;
	}
	else if (i == 2)
		std::cout << "RIGHT" << std::endl;
	else if (i == 3)
		std::cout << "DOWN" << std::endl;
	else if (i == 4)
		std::cout << "LEFT" << std::endl;
	else
		std::cout << "Error\n";

}

int main(int argc, char const *argv[]) {

	if (argc < 4)
	{
		std::cout << "Usage: ./n_puzzle heuristic inital_state final_state [greed]" << std::endl;
		std::cout << "heuristics : {manhattan, hamming, euclidean}" << std::endl;
		return (1);
	}
	std::vector<std::size_t>		move_stack;
	bool							greed = false;
	Parser		parser(argv[2]);
	parser.getContent();
	std::unique_ptr<const Puzzle>		init_puzzle = parser.make_puzzle();
	std::vector<std::vector<int> >		first_grid = init_puzzle->copy_grid();
	parser.setFile(argv[3]);
	parser.getContent();
	std::unique_ptr<const Puzzle>		final_puzzle = parser.make_puzzle();
	greed = !!argv[4];
	Ai		Ai(std::move(init_puzzle), std::move(final_puzzle), std::string(argv[1]), greed);

	if (Ai.isSolvable()) {
		auto t = clock();
		move_stack = Ai.solve();
		std::cout << "time : " << (clock() - t)/CLOCKS_PER_SEC << " seconds "<< std::endl;
		std::cout << "Time complexity : " << Ai.getTimeCost() << std::endl;
		std::cout << "Space complexity : " << Ai.getSpaceCost() << std::endl;
		std::cout << "Number of moves : " << move_stack.size() << std::endl;
		if (first_grid.size() < 5)
		{
			Drawer	d(std::move(first_grid), move_stack);
			d.DrawField();
		}
	}
	else
		std::cout << "Not solvable sorry" << std::endl;
	return 0;
}
