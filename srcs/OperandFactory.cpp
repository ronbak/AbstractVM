// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:06:10 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 16:53:04 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.hpp"
#include "OperandFactory.hpp"

OperandFactory::OperandFactory(void)
	: _operandCreators{
		[IOperand::EOperandType::INT8] = &OperandFactory::createInt8,
		[IOperand::EOperandType::INT16] = &OperandFactory::createInt16,
		[IOperand::EOperandType::INT32] = &OperandFactory::createInt32,
		[IOperand::EOperandType::FLOAT] = &OperandFactory::createFloat,
		[IOperand::EOperandType::DOUBLE] = &OperandFactory::createDouble,
	}
{
}

OperandFactory::~OperandFactory(void)
{
}

OperandFactory			OperandFactory::instance = {};

IOperand const			*OperandFactory::createOperand(IOperand::EOperandType type, std::string const &value) const
{
	if (type < 0 || type >= IOperand::OPERAND_COUNT)
		throw std::runtime_error("No such operand");
	return ((this->*(_operandCreators[type]))(value));
}

IOperand const			*OperandFactory::createInt8(std::string const &value) const
{
	return (new Operand<int8_t>(value));
}

IOperand const			*OperandFactory::createInt16(std::string const &value) const
{
	return (new Operand<int16_t>(value));
}

IOperand const			*OperandFactory::createInt32(std::string const &value) const
{
	return (new Operand<int32_t>(value));
}

IOperand const			*OperandFactory::createFloat(std::string const &value) const
{
	return (new Operand<float>(value));
}

IOperand const			*OperandFactory::createDouble(std::string const &value) const
{
	return (new Operand<double>(value));
}
