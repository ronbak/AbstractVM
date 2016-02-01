// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:59:15 by jaguillo          #+#    #+#             //
//   Updated: 2016/02/01 14:11:46 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "VMStack.hpp"

#include <iostream>

int				main(int argc, char **argv)
{
	VMStack			vm;

	try
	{
		(argc <= 1) ? vm.run() : vm.run(argv[1]);
	}
	catch (std::exception const &e)
	{
		std::cout << ">> FAIL" << std::endl << e.what() << std::endl;
	}
	return (0);
}
