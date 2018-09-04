//
//  Puzzle.hpp
//  n_puzzle
//
//  Created by <tle-huu-> on 26/08/2018.
//
//

#ifndef Puzzle_hpp
#define Puzzle_hpp

#include <iostream>
#include <string>
#include <vector>

struct Point
{
	int		x;
	int		y;
};

class Puzzle {
	private:
		std::vector<std::vector<int> >		_grid;
		Point								_blank;

	public:
		Puzzle();
		Puzzle(int);
		Puzzle(Puzzle const & src);
		~Puzzle();
		Puzzle & operator=(Puzzle const & src);

		std::size_t			getSize() const;
		std::vector<int>	getFlatGrid( void ) const;

		Point				getBlank() const;
		void				setBlank(int, int);

		void				setCell(int x, int y, int value);
		int					getCell(int, int) const;

		void				dump( void ) const ;
		const Puzzle		move_right( void ) const;
		const Puzzle		move_left( void ) const;
		const Puzzle		move_down( void ) const;
		const Puzzle		move_up( void ) const;

		std::string			toString( void ) const;

		std::vector<std::vector<int> > copy_grid( void ) const;

		struct					MoveException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

		bool operator==(const Puzzle& rhs) const;
		bool operator!=(const Puzzle& rhs) const;
};


#endif /* Puzzle_hpp */
