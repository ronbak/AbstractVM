// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:59:15 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 20:16:39 by jaguillo         ###   ########.fr       //
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

	a = OperandFactory::instance.createOperand(IOperand::INT8, "-50");
	b = OperandFactory::instance.createOperand(IOperand::INT8, "-3");
	c = *a * *b;
	delete a;
	delete b;
	std::cout << c->getType() << ": " << c->toString() << std::endl;
	return (0);
}
