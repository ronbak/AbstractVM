// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:59:15 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/28 14:05:28 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "VMStack.hpp"

#include <iostream>
#include <vector>

int				main(void)
{
	std::vector<IOperand const*>	stack;
	VMStack							vm;

	try
	{
		vm.exec("push", new std::string("int8(4)"));
		vm.exec("push", new std::string("int8(8)"));
		vm.exec("dump");
		vm.exec("add");
		vm.exec("print");
		vm.exec("assert", new std::string("int16(12)"));
	}
	catch (std::exception const &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	return (0);
}
