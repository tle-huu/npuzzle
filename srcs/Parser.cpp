#include "Parser.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <fstream>
#include <unordered_map>


#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

Parser::Parser()
{
}

Parser::Parser(std::string file) : _file(file)
{
}

Parser::~Parser()
{
}

Parser::Parser(Parser const & rhs)
{
	*this = rhs;
}

Parser & Parser::operator=(Parser const & rhs)
{
	_file = rhs._file;
	_content = rhs._content;
	return *this;
}

void 						Parser::getContent(void )
{
	bool							first = false;
	std::unordered_map<int, int>	numbers;
	std::string						line;
	std::size_t						pos;
	std::vector<std::string>		raw;
	int								tmp;
	int								size;

	std::ifstream myfile(_file);

	if (!myfile.is_open())
		throw(FileException());

	while (!myfile.eof())
	{
		std::getline(myfile, line);
		if ((pos = line.find('#')) != std::string::npos)
			line = line.substr(0, pos);
		boost::trim(line);
		if (line.empty())
			continue;
		else {
			first = true;
			boost::split(raw, line, boost::is_any_of(" "));
			try
			{
				for (auto &x : raw) {
					if (x.empty())
						continue;
					tmp = std::stoi(x);
					if (numbers.count(tmp) > 0 && tmp != _content[0]){
						throw(ParseException());
					}
					numbers.insert ( std::pair<int,int>(tmp, 1 ));
					_content.push_back(tmp);
				}
			}
			catch (std::invalid_argument &e)
			{
				throw(ParseException());
			}
		}
	}
	myfile.close();

	/* DEBUGGING
	for (auto &x : _content) {
		std::cout << "content : " << x << std::endl;
	}
	*/
	if (_content[0] * _content[0] != _content.size() - 1)
		throw(ParseException());
	for (int i = 0; i < _content.size() - 1; i++) {
		if (numbers.count(i) == 0)
			throw(ParseException());
	}
}

void						Parser::setFile(std::string file)
{
	this->_file = file;
	_content.clear();
}


std::unique_ptr<Puzzle>		Parser::make_puzzle()
{
	if (_content.empty())
		throw(ContentEmptyException());
	int		size = _content[0];
	std::unique_ptr<Puzzle>		newPuzzle = std::make_unique<Puzzle>(size);

	_content.erase(_content.begin());
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			newPuzzle->setCell(i, j, _content[i * size + j]);
			if (_content[i * size + j] == 0)
				newPuzzle->setBlank(i, j);
		}
	}
	return (newPuzzle);
}


/*		Exception		*/

const char *			Parser::FileException::what() const throw()
{
	return "File not found";
}

const char *			Parser::ParseException::what() const throw()
{
	return "Parse error in file";
}

const char *			Parser::ValidException::what() const throw() {

	return "Invalid puzzle";
}

const char *			Parser::ContentEmptyException::what() const throw() {

	return "Content empty";
}
