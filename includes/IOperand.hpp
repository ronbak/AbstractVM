// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 14:55:34 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 16:04:12 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

class	IOperand
{
public:
	enum	EOperandType
	{
		INT8,
		INT16,
		INT32,
		FLOAT,
		DOUBLE,
		OPERAND_COUNT
	};

	virtual ~IOperand(void){}

	virtual int					getPrecision(void) const = 0;
	virtual EOperandType		getType(void) const = 0;

	virtual IOperand const		*operator+(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator-(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator*(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator/(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator%(IOperand const &rhs) const = 0;

	virtual std::string const	&toString(void) const = 0;

protected:

private:
};

#endif
