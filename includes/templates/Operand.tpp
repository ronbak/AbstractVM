// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.tpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 15:43:13 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/27 16:26:42 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

template<typename T>
Operand<T>::Operand(std::string const &value)
	: _strValue(value)
{
}

template<typename T>
Operand<T>::~Operand(void)
{
}

/*
** ========================================================================== **
** getType
*/

template<typename T>
int								Operand<T>::getPrecision(void) const
{
	return (getType());
}

template<typename T>
IOperand::EOperandType			Operand<T>::getType(void) const
{
	throw std::domain_error("Invalid operand type");
}

#define OPERAND_TYPE(T, OP)		\
template<>															\
inline IOperand::EOperandType	Operand<T>::getType(void) const		\
{																	\
	return (IOperand::OP);											\
}

OPERAND_TYPE(int8_t, INT8);
OPERAND_TYPE(int16_t, INT16);
OPERAND_TYPE(int32_t, INT32);
OPERAND_TYPE(float, FLOAT);
OPERAND_TYPE(double, DOUBLE);

/*
** ========================================================================== **
** Operators
*/

template<typename T>
IOperand const			*Operand<T>::operator+(IOperand const &rhs) const
{
	return (this);
	(void)rhs;
}

template<typename T>
IOperand const			*Operand<T>::operator-(IOperand const &rhs) const
{
	return (this);
	(void)rhs;
}

template<typename T>
IOperand const			*Operand<T>::operator*(IOperand const &rhs) const
{
	return (this);
	(void)rhs;
}

template<typename T>
IOperand const			*Operand<T>::operator/(IOperand const &rhs) const
{
	return (this);
	(void)rhs;
}

template<typename T>
IOperand const			*Operand<T>::operator%(IOperand const &rhs) const
{
	return (this);
	(void)rhs;
}

template<typename T>
std::string const		&Operand<T>::toString(void) const
{
	return (_strValue);
}
