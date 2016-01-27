// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operator.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 18:12:02 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 23:55:26 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "Operator.hpp"

#include <cfenv>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

// #pragma STDC FENV_ACCESS ON

#define TMPL_IF(IF)		typename std::enable_if<IF>::type* = nullptr

/*
** ========================================================================== **
** Integer operations
*/

template<typename T>
static T			integer_overflow(int64_t n)
{
	if (n < std::numeric_limits<T>::min()
		|| n > std::numeric_limits<T>::max())
		throw std::runtime_error("Overflow");
	return ((T)n);
}

template<typename T, TMPL_IF(std::is_integral<T>::value)>
static T			op_add(T a, T b)
{
	return (integer_overflow<T>((int64_t)a) + ((int64_t)b));
}

template<typename T, TMPL_IF(std::is_integral<T>::value)>
static T			op_sub(T a, T b)
{
	return (integer_overflow<T>((int64_t)a) - ((int64_t)b));
}

template<typename T, TMPL_IF(std::is_integral<T>::value)>
static T			op_mul(T a, T b)
{
	return (integer_overflow<T>((int64_t)a) * ((int64_t)b));
}

template<typename T, TMPL_IF(std::is_integral<T>::value)>
static T			op_div(T a, T b)
{
	if (b == 0)
		throw std::runtime_error("Division by 0");
	return (a / b);
}

template<typename T, TMPL_IF(std::is_integral<T>::value)>
static T			op_mod(T a, T b)
{
	if (b == 0)
		throw std::runtime_error("Division by 0");
	return (a % b);
}

/*
** ========================================================================== **
** Floating point operations
*/

template<typename T>
static T			float_exception(T n)
{
	int const			except = fetestexcept(FE_ALL_EXCEPT);

	if (except != 0)
	{
		if (except & FE_DIVBYZERO)
			throw std::runtime_error("Division by 0");
		// if (except & FE_INEXACT)
		// 	throw std::runtime_error("Inexact");
		if (except & FE_INVALID)
			throw std::runtime_error("Invalid");
		if (except & FE_OVERFLOW)
			throw std::runtime_error("Overflow");
		if (except & FE_UNDERFLOW)
			throw std::runtime_error("Underflow");
	}
	return (n);
}

template<typename T, TMPL_IF(std::is_floating_point<T>::value)>
static T			op_add(T a, T b)
{
	feclearexcept(FE_ALL_EXCEPT);
	return (float_exception(a + b));
}

template<typename T, TMPL_IF(std::is_floating_point<T>::value)>
static T			op_sub(T a, T b)
{
	feclearexcept(FE_ALL_EXCEPT);
	return (float_exception(a - b));
}

template<typename T, TMPL_IF(std::is_floating_point<T>::value)>
static T			op_mul(T a, T b)
{
	feclearexcept(FE_ALL_EXCEPT);
	return (float_exception(a * b));
}

template<typename T, TMPL_IF(std::is_floating_point<T>::value)>
static T			op_div(T a, T b)
{
	feclearexcept(FE_ALL_EXCEPT);
	return (float_exception(a / b));
}

template<typename T, TMPL_IF(std::is_floating_point<T>::value)>
static T			op_mod(T a, T b)
{
	feclearexcept(FE_ALL_EXCEPT);
	return (float_exception(std::fmod(a, b)));
}

/*
** ========================================================================== **
** call_op
*/

#define DEF_OP(T, T_NAME, PARSE, OP_NAME, OP)		\
static IOperand const	*op_##T_NAME##OP_NAME(std::string const &a, std::string const &b)		\
{																								\
	T const		value = OP(((T)PARSE(a)), ((T)PARSE(b)));										\
																								\
	return (OperandFactory::instance.createOperand(IOperand::T_NAME, std::to_string(value)));	\
}

#define DEF_OP_ALL(T, T_NAME, PARSE)	\
	DEF_OP(T, T_NAME, PARSE, OP_ADD, op_add);	\
	DEF_OP(T, T_NAME, PARSE, OP_SUB, op_sub);	\
	DEF_OP(T, T_NAME, PARSE, OP_MUL, op_mul);	\
	DEF_OP(T, T_NAME, PARSE, OP_DIV, op_div);	\
	DEF_OP(T, T_NAME, PARSE, OP_MOD, op_mod);

DEF_OP_ALL(int8_t, INT8, std::stoi);
DEF_OP_ALL(int16_t, INT16, std::stoi);
DEF_OP_ALL(int32_t, INT32, std::stol);
DEF_OP_ALL(float, FLOAT, std::stof);
DEF_OP_ALL(double, DOUBLE, std::stod);

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
