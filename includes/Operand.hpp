// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:10:54 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 22:47:23 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INT_OPERAND_HPP
# define INT_OPERAND_HPP

# include "IOperand.hpp"
# include "Operator.hpp"

# include <stdexcept>
# include <stdint.h>
# include <string>

/*
** IOperand implementation
*/
template<typename T>
class	Operand : public IOperand
{
public:
	Operand(std::string const &value);
	virtual ~Operand(void);

	virtual int						getPrecision(void) const;
	virtual IOperand::EOperandType	getType(void) const;

	virtual IOperand const		*operator+(IOperand const &rhs) const;
	virtual IOperand const		*operator-(IOperand const &rhs) const;
	virtual IOperand const		*operator*(IOperand const &rhs) const;
	virtual IOperand const		*operator/(IOperand const &rhs) const;
	virtual IOperand const		*operator%(IOperand const &rhs) const;

	virtual std::string const	&toString(void) const;

protected:

	std::string					_strValue;

private:
	Operand(void) = delete;
	Operand(Operand &&src) = delete;
	Operand(Operand const &src) = delete;
	Operand						&operator=(Operand &&rhs) = delete;
	Operand						&operator=(Operand const &rhs) = delete;
};

# include "templates/Operand.tpp"

#endif
