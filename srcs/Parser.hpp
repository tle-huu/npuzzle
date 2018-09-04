#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <vector>
# include <memory>
# include "Puzzle.hpp"

class Parser {

	private:
		std::string					_file;
		std::vector<int>			_content;
		Parser();

	public:
		Parser(std::string file);
		~Parser();

		Parser(Parser const & rhs);
		Parser & operator=(Parser const & rhs);

		std::unique_ptr<Puzzle>			make_puzzle();
		void							setFile(std::string);
		void							getContent( void );


		struct					FileException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

		struct					ParseException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

		struct					ValidException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

		struct					ContentEmptyException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

};

#endif
