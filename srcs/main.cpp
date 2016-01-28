// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:59:15 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/28 18:00:09 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "VMStack.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

static void		exec_from_stream(VMStack &vm, std::istream &is, char const *filename)
{
	std::regex		regex("\\s*(?:([^\\s]+)(?:\\s+([^\\s]+))?\\s*)?(?:;.*)?");
	std::smatch		match;
	std::string		line;
	std::string		param;
	uint32_t		line_count(0);

	try
	{
		while (std::getline(is, line))
		{
			line_count++;
			if (!std::regex_match(line, match, regex))
				throw std::runtime_error("Syntax error");
			if (match[1].length() == 0)
				continue ;
			param = match[2].str();
			vm.exec(match[1], (param.size() > 0) ? &param : nullptr);
		}
	}
	catch (std::runtime_error const &e)
	{
		throw std::runtime_error(std::string(filename) + ":"
			+ std::to_string(line_count) + ": " + e.what());
	}
}

static void		exec_from_file(VMStack &vm, char const *filename)
{
	std::ifstream	ifs(filename);

	if (!ifs)
		throw std::runtime_error(std::string("Cannot open ") + filename);
	exec_from_stream(vm, ifs, filename);
}

int				main(int argc, char **argv)
{
	VMStack			vm;

	try
	{
		if (argc <= 1)
			exec_from_stream(vm, std::cin, "stdin");
		else
			exec_from_file(vm, argv[1]);
	}
	catch (std::exception const &e)
	{
		std::cout << ">> FAIL" << std::endl << e.what() << std::endl;
	}
	return (0);
}
