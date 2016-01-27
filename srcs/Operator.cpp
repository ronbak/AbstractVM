// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operator.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 18:12:02 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 19:11:47 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "Operator.hpp"

#include <cmath>
#include <string>

#define O_ADD(A, B)		(A + B)
#define O_SUB(A, B)		(A - B)
#define O_MUL(A, B)		(A * B)
#define O_DIV(A, B)		(A / B)
#define O_MOD(A, B)		(A % B)

#define DEF_OP(T, T_NAME, PARSE, OP, OP_NAME)		\
static IOperand const	*op_##T_NAME##OP_NAME(std::string const &a, std::string const &b)		\
{																								\
	T const		value = OP(((T)PARSE(a)), ((T)PARSE(b)));										\
																								\
	return (OperandFactory::instance.createOperand(IOperand::T_NAME, std::to_string(value)));	\
}

#define DEF_OP_ALL(T, T_NAME, PARSE, O_ADD, O_SUB, O_MUL, O_DIV, O_MOD)	\
	DEF_OP(T, T_NAME, PARSE, O_ADD, OP_ADD);	\
	DEF_OP(T, T_NAME, PARSE, O_SUB, OP_SUB);	\
	DEF_OP(T, T_NAME, PARSE, O_MUL, OP_MUL);	\
	DEF_OP(T, T_NAME, PARSE, O_DIV, OP_DIV);	\
	DEF_OP(T, T_NAME, PARSE, O_MOD, OP_MOD);

DEF_OP_ALL(int8_t, INT8, std::stoi, O_ADD, O_SUB, O_MUL, O_DIV, O_MOD);
DEF_OP_ALL(int16_t, INT16, std::stoi, O_ADD, O_SUB, O_MUL, O_DIV, O_MOD);
DEF_OP_ALL(int32_t, INT32, std::stol, O_ADD, O_SUB, O_MUL, O_DIV, O_MOD);
DEF_OP_ALL(float, FLOAT, std::stof, O_ADD, O_SUB, O_MUL, O_DIV, std::fmod);
DEF_OP_ALL(double, DOUBLE, std::stod, O_ADD, O_SUB, O_MUL, O_DIV, std::fmod);

#define OP_GET(PRECI, OP)	((PRECI) * IOperand::OPERAND_COUNT + (OP))
#define OP_SET(T, OP)		[OP_GET(IOperand::T, OP)] = &op_##T##OP

IOperand const	*(*Operator::operations[IOperand::OPERAND_COUNT*OP_COUNT])(std::string const &a, std::string const &b) = {
	OP_SET(INT8, OP_ADD),
	OP_SET(INT16, OP_ADD),
	OP_SET(INT32, OP_ADD),
	OP_SET(FLOAT, OP_ADD),
	OP_SET(DOUBLE, OP_ADD),
	OP_SET(INT8, OP_SUB),
	OP_SET(INT16, OP_SUB),
	OP_SET(INT32, OP_SUB),
	OP_SET(FLOAT, OP_SUB),
	OP_SET(DOUBLE, OP_SUB),
	OP_SET(INT8, OP_MUL),
	OP_SET(INT16, OP_MUL),
	OP_SET(INT32, OP_MUL),
	OP_SET(FLOAT, OP_MUL),
	OP_SET(DOUBLE, OP_MUL),
	OP_SET(INT8, OP_DIV),
	OP_SET(INT16, OP_DIV),
	OP_SET(INT32, OP_DIV),
	OP_SET(FLOAT, OP_DIV),
	OP_SET(DOUBLE, OP_DIV),
	OP_SET(INT8, OP_MOD),
	OP_SET(INT16, OP_MOD),
	OP_SET(INT32, OP_MOD),
	OP_SET(FLOAT, OP_MOD),
	OP_SET(DOUBLE, OP_MOD),
};

IOperand const	*Operator::call_op(IOperand const &a, IOperand const &b, EOperator op)
{
	int const		precision = std::max(a.getPrecision(), b.getPrecision());

	if (precision < 0 || precision >= IOperand::OPERAND_COUNT)
		throw std::runtime_error("Invalid operand type");
	if (op < 0 || op >= OP_COUNT)
		throw std::runtime_error("Invalid operation type");
	auto f = operations[OP_GET(precision, op)];
	if (f == NULL)
		throw std::runtime_error("LOL");
	return (f(a.toString(), b.toString()));
}
