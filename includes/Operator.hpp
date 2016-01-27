// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operator.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 18:54:59 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 19:00:26 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERATOR_HPP
# define OPERATOR_HPP

# include "IOperand.hpp"

/*
** Deal with operations
*/
class	Operator
{
public:
	enum	EOperator
	{
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_COUNT
	};

	virtual ~Operator(void);

	static IOperand const	*call_op(IOperand const &a, IOperand const &b, EOperator op);

protected:

	static IOperand const	*(*operations[])(std::string const &a, std::string const &b);

private:
	Operator(void) = delete;
	Operator(Operator &&src) = delete;
	Operator(Operator const &src) = delete;
	Operator			&operator=(Operator &&rhs) = delete;
	Operator			&operator=(Operator const &rhs) = delete;
};

#endif
