// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 12:37:47 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/28 18:53:27 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OperandFactory.hpp"
#include "VMStack.hpp"

#include <iostream>

VMStack::VMStack(void)
	: _stack(), _exited(false)
{
}

VMStack::~VMStack(void)
{
	for (IOperand const *op : _stack)
		delete op;
}

void			VMStack::exec(std::string const &instr, std::string const *param)
{
	auto const		&f = _instructions.find(instr);

	if (_exited)
		throw std::runtime_error("Instruction after exit");
	if (f == _instructions.end())
		throw std::runtime_error("Unknown instruction");
	if (f->second.second != static_cast<bool>(param != nullptr))
		throw std::runtime_error(f->second.second
			? "Instruction require an argument"
			: "Instruction does not take an argument");
	(this->*(f->second.first))(param);
}

std::unordered_map<std::string, std::pair<VMStack::instr_t, bool>> const	VMStack::_instructions{
	{"input", {&VMStack::_instr_input, true}},
	{"push", {&VMStack::_instr_push, true}},
	{"pop", {&VMStack::_instr_pop, false}},
	{"dump", {&VMStack::_instr_dump, false}},
	{"assert", {&VMStack::_instr_assert, true}},
	{"swap", {&VMStack::_instr_swap, false}},
	{"add", {&VMStack::_instr_add, false}},
	{"sub", {&VMStack::_instr_sub, false}},
	{"mul", {&VMStack::_instr_mul, false}},
	{"div", {&VMStack::_instr_div, false}},
	{"mod", {&VMStack::_instr_mod, false}},
	{"print", {&VMStack::_instr_print, false}},
	{"exit", {&VMStack::_instr_exit, false}},
};

IOperand const	*VMStack::_get_last(void)
{
	IOperand const	*last;

	if (_stack.size() == 0)
		throw std::runtime_error("Operation on an empty stack");
	last = _stack.back();
	return (last);
}

IOperand const	*VMStack::_extract_last(void)
{
	IOperand const *const	last = _get_last();

	_stack.pop_back();
	return (last);
}

void			VMStack::_instr_input(std::string const *param)
{
	static std::string		types[IOperand::OPERAND_COUNT] = {
		[IOperand::INT8] = "int8",
		[IOperand::INT16] = "int16",
		[IOperand::INT32] = "int32",
		[IOperand::FLOAT] = "float",
		[IOperand::DOUBLE] = "double",
	};
	IOperand const *const	def = OperandFactory::instance.parseOperand(*param);
	std::string				input;

	std::cout << ">> INPUT" << std::endl << types[def->getType()] << "("
		<< def->toString() << "): " << std::flush;
	std::getline(std::cin, input);
	std::cin.clear();
	if (input.size() == 0)
		_stack.push_back(def);
	else
	{
		_stack.push_back(OperandFactory::instance.createOperand(def->getType(), input));
		delete def;
	}
}

void			VMStack::_instr_push(std::string const *param)
{
	_stack.push_back(OperandFactory::instance.parseOperand(*param));
}

void			VMStack::_instr_pop(std::string const *)
{
	delete _extract_last();
}

void			VMStack::_instr_dump(std::string const *)
{
	std::cout << ">> DUMP" << std::endl;
	for (auto it = _stack.rbegin(); it != _stack.rend(); ++it)
		std::cout << (*it)->toString() << std::endl;
	std::cout << ">> Dump size: " << _stack.size() << std::endl;
}

void			VMStack::_instr_assert(std::string const *param)
{
	IOperand const *const					last = _get_last();
	std::unique_ptr<IOperand const> const	val(OperandFactory::instance.parseOperand(*param));

	if (last->toString() != val->toString())
		throw std::runtime_error(std::string("Assert fail ")
			+ last->toString() + " != " + val->toString());
}

void			VMStack::_instr_swap(std::string const *)
{
	IOperand const *const	a = _extract_last();
	IOperand const *const	b = _extract_last();

	_stack.push_back(a);
	_stack.push_back(b);
}

#define INSTR_DEF(NAME, OP)	\
void			VMStack::_instr_##NAME(std::string const *)			\
{																	\
	std::unique_ptr<IOperand const> const	a(_extract_last());		\
	std::unique_ptr<IOperand const> const	b(_extract_last());		\
																	\
	_stack.push_back(*b OP *a);										\
}

INSTR_DEF(add, +);
INSTR_DEF(sub, -);
INSTR_DEF(mul, *);
INSTR_DEF(div, /);
INSTR_DEF(mod, %);

void			VMStack::_instr_print(std::string const *)
{
	std::cout << ">> PRINT" << std::endl
		<< _get_last()->toString() << std::endl;
}

void			VMStack::_instr_exit(std::string const *)
{
	_exited = true;
}
