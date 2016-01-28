// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:00:57 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/28 14:34:14 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "IOperand.hpp"

# include <regex>
# include <string>
# include <unordered_map>

/*
** Operand factory
*/
class	OperandFactory
{
public:
	virtual ~OperandFactory(void);

	IOperand const			*parseOperand(std::string const &value) const;

	IOperand const			*createOperand(IOperand::EOperandType type, std::string const &value) const;

	static OperandFactory	instance;

protected:

	OperandFactory(void);

	IOperand const			*(OperandFactory::*_operandCreators[IOperand::OPERAND_COUNT])(std::string const &value) const;

	std::regex												_opRegex;
	std::unordered_map<std::string, IOperand::EOperandType>	_opTypes;

private:

	IOperand const			*createInt8(std::string const &value) const;
	IOperand const			*createInt16(std::string const &value) const;
	IOperand const			*createInt32(std::string const &value) const;
	IOperand const			*createFloat(std::string const &value) const;
	IOperand const			*createDouble(std::string const &value) const;

	OperandFactory(OperandFactory &&src) = delete;
	OperandFactory(OperandFactory const &src) = delete;
	OperandFactory			&operator=(OperandFactory &&rhs) = delete;
	OperandFactory			&operator=(OperandFactory const &rhs) = delete;
};

#endif
