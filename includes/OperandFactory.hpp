// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:00:57 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 16:13:25 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "IOperand.hpp"
# include <string>

class	OperandFactory
{
public:
	OperandFactory(void);
	virtual ~OperandFactory(void);

	IOperand const			*createOperand(IOperand::EOperandType type, std::string const &value) const;

protected:

	IOperand const			*(OperandFactory::*_operandCreators[IOperand::OPERAND_COUNT])(std::string const &value) const;

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
