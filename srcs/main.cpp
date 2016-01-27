// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:59:15 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 23:55:18 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.hpp"
#include "OperandFactory.hpp"

#include <iostream>

int				main(void)
{
	IOperand const	*a;
	IOperand const	*b;
	IOperand const	*c;

	a = OperandFactory::instance.createOperand(IOperand::FLOAT, "1");
	b = OperandFactory::instance.createOperand(IOperand::FLOAT, "1.65465416541654614");
	c = *a / *b;
	delete a;
	delete b;
	std::cout << c->getType() << ": " << c->toString() << std::endl;
	return (0);
}
