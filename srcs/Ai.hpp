//
//  Ai.hpp
//  n_puzzle
//
//  Created by <tle-huu-> on 01/09/2018.
//
//

#ifndef Ai_hpp
#define Ai_hpp

#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <stack>
#include "Puzzle.hpp"

#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3


struct	Node
{
	Puzzle					puzzle;
	std::shared_ptr<Node>	parent;
	std::vector<Node>		children;
	int						move;
	int						f;
	int						g;
};

class Ai {
	private:
		/* Attributes */
		static std::size_t				_count;
		std::unique_ptr<const Puzzle>	_initial;
		std::unique_ptr<const Puzzle>	_final;
		std::string						_heuristic;
		bool							_greedy;
		std::size_t						_time_cost;
		std::size_t						_space_cost;

		/* Functions */
		Ai();
		Ai(Ai const & src);
		Ai & operator=(Ai const & src);

	public:
		/* Functions */
		Ai(std::unique_ptr<const Puzzle> &&, std::unique_ptr<const Puzzle> &&, std::string, bool);
		~Ai();

		int							heuristic(Puzzle const &, std::string) const;
		int							manhattan(Puzzle const &) const;
		int							hamming(Puzzle const &) const;
		int							euclidean(Puzzle const &) const;
		std::vector<std::size_t>	solve( void );
		void						getNextStates(Node &);
		bool						isSolvable( void ) const;
		std::size_t					getTimeCost( void ) const ;
		std::size_t					getSpaceCost( void ) const ;

		/* Exceptions */
		struct					TooManyAiException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

		struct					PuzzleSizeException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};


};


#endif /* Ai_hpp */
