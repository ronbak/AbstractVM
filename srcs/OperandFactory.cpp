// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:06:10 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/29 16:59:02 by juloo            ###   ########.fr       //
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
	},
	_opRegex("(\\w+)\\((-?[0-9]+(?:\\.[0-9]*)?)\\)"),
	_opTypes{
		{"int8", IOperand::INT8},
		{"int16", IOperand::INT16},
		{"int32", IOperand::INT32},
		{"float", IOperand::FLOAT},
		{"double", IOperand::DOUBLE},
	}
{
}

OperandFactory::~OperandFactory(void)
{
}

OperandFactory			OperandFactory::instance = {};

IOperand const			*OperandFactory::parseOperand(std::string const &value) const
{
	std::smatch				match;

	if (!std::regex_match(value, match, _opRegex))
		throw std::runtime_error("Invalid value");
	auto const				opType = _opTypes.find(match[1]);
	if (opType == _opTypes.end())
		throw std::runtime_error("Unknown operand");
	return (createOperand(opType->second, match[2]));
}

IOperand const			*OperandFactory::createOperand(IOperand::EOperandType type, std::string const &value) const
{
	if (type < 0 || type >= IOperand::OPERAND_COUNT)
		throw std::runtime_error("Invalid operand");
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
