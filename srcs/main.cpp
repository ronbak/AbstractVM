// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:59:15 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 16:27:38 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.hpp"
#include "OperandFactory.hpp"

#include <iostream>

int				main(void)
{
	OperandFactory	factory;
	IOperand const	*a;

	a = factory.createOperand(IOperand::FLOAT, "0");
	std::cout << a->getType() << ": " << a->toString() << std::endl;
	return (0);
}
