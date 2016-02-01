// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 12:37:47 by jaguillo          #+#    #+#             //
//   Updated: 2016/02/01 14:11:12 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OperandFactory.hpp"
#include "Operator.hpp"
#include "VMStack.hpp"

#include <fstream>
#include <iostream>

VMStack::VMStack(void) :
	_run_regex("\\s*(?:([^\\s;]+)(?:\\s+([^\\s;]+))?\\s*)?(?:;(;)?.*)?"),
	_stack(),
	_exited(false),
	_nestedIf(0),
	_disabledIf(0)
{
}

VMStack::~VMStack(void)
{
	for (IOperand const *op : _stack)
		delete op;
}

void			VMStack::run(void)
{
	run(std::cin, "<stdin>", true);
}

void			VMStack::run(std::string const &filename)
{
	std::ifstream	ifs(filename);

	if (!ifs)
		throw std::runtime_error(std::string(filename) + ": Cannot open");
	run(ifs, filename);
}

void			VMStack::run(std::istream &in,
					std::string const &filename, bool eot)
{
	std::smatch		match;
	std::string		line;
	std::string		param;
	uint32_t		line_count(0);

	try
	{
		while (std::getline(in, line))
		{
			line_count++;
			if (!std::regex_match(line, match, _run_regex))
				throw std::runtime_error("Syntax error");
			if (match[1].length() > 0)
			{
				param = match[2].str();
				exec(match[1], (param.size() > 0) ? &param : nullptr);
			}
			if ((eot && match[3].length() > 0) || _exited)
				return ;
		}
	}
	catch (std::runtime_error const &e)
	{
		throw std::runtime_error(filename + ":" + std::to_string(line_count)
			+ ":\n" + e.what());
	}
	if (!_exited)
		throw std::runtime_error("Missing exit instruction");
}

void			VMStack::exec(std::string const &instr, std::string const *param)
{
	auto const		&f = _instructions.find(instr);

	if (_exited)
		throw std::runtime_error("Instruction after exit");
	if (f == _instructions.end())
		throw std::runtime_error("Unknown instruction");
	if (_disabledIf > 0 && !std::get<2>(f->second))
		return ;
	if (std::get<1>(f->second) != static_cast<bool>(param != nullptr))
		throw std::runtime_error(std::get<1>(f->second)
			? "Instruction require an argument"
			: "Instruction does not take an argument");
	(this->*(std::get<0>(f->second)))(param);
}

bool			VMStack::isExited(void) const
{
	return (_exited);
}

std::unordered_map<std::string, std::tuple<VMStack::instr_t, bool, bool>> const	VMStack::_instructions{
	{"input",	std::make_tuple(&VMStack::_instr_input,		true,	false)},
	{"push",	std::make_tuple(&VMStack::_instr_push,		true,	false)},
	{"pop",		std::make_tuple(&VMStack::_instr_pop,		false,	false)},
	{"set",		std::make_tuple(&VMStack::_instr_set,		true,	false)},
	{"dump",	std::make_tuple(&VMStack::_instr_dump,		false,	false)},
	{"assert",	std::make_tuple(&VMStack::_instr_assert,	true,	false)},
	{"swap",	std::make_tuple(&VMStack::_instr_swap,		false,	false)},
	{"top",		std::make_tuple(&VMStack::_instr_top,		false,	false)},
	{"dup",		std::make_tuple(&VMStack::_instr_dup,		false,	false)},
	{"add",		std::make_tuple(&VMStack::_instr_add,		false,	false)},
	{"sub",		std::make_tuple(&VMStack::_instr_sub,		false,	false)},
	{"mul",		std::make_tuple(&VMStack::_instr_mul,		false,	false)},
	{"div",		std::make_tuple(&VMStack::_instr_div,		false,	false)},
	{"mod",		std::make_tuple(&VMStack::_instr_mod,		false,	false)},
	{"print",	std::make_tuple(&VMStack::_instr_print,		false,	false)},
	{"exit",	std::make_tuple(&VMStack::_instr_exit,		false,	false)},
	{"if==",	std::make_tuple(&VMStack::_instr_ifeq,		false,	true)},
	{"if!=",	std::make_tuple(&VMStack::_instr_ifneq,		false,	true)},
	{"if<",		std::make_tuple(&VMStack::_instr_iflt,		false,	true)},
	{"if>",		std::make_tuple(&VMStack::_instr_ifgt,		false,	true)},
	{"if<=",	std::make_tuple(&VMStack::_instr_ifle,		false,	true)},
	{"if>=",	std::make_tuple(&VMStack::_instr_ifge,		false,	true)},
	{"else",	std::make_tuple(&VMStack::_instr_else,		false,	true)},
	{"endif",	std::make_tuple(&VMStack::_instr_endif,		false,	true)},
};

IOperand const	*VMStack::_get_last(uint32_t n)
{
	if (_stack.size() <= n)
		throw std::runtime_error("Operation on an empty stack");
	return (_stack[_stack.size() - n - 1]);
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

void			VMStack::_instr_set(std::string const *param)
{
	std::unique_ptr<IOperand const> const	top(_extract_last());

	_stack.push_back(OperandFactory::instance.createOperand(top->getType(), *param));
}

void			VMStack::_instr_dump(std::string const *)
{
	std::cout << ">> DUMP (" << _stack.size() << ")" << std::endl;
	for (auto it = _stack.rbegin(); it != _stack.rend(); ++it)
		std::cout << (*it)->toString() << std::endl;
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

void			VMStack::_instr_dup(std::string const *)
{
	IOperand const *const	a = _get_last();

	_stack.push_back(OperandFactory::instance.createOperand(a->getType(), a->toString()));
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
	IOperand const *const	top = _get_last();

	if (top->getType() != IOperand::INT8)
		throw std::runtime_error("Unprintable type");
	std::cout << ">> PRINT" << std::endl
		<< static_cast<char>(std::stoi(_get_last()->toString())) << std::endl;
}

void			VMStack::_instr_top(std::string const *)
{
	std::cout << ">> TOP" << std::endl
		<< _get_last()->toString() << std::endl;
}

void			VMStack::_instr_exit(std::string const *)
{
	_exited = true;
}

#define INSTR_IF_DEF(NAME, OP)		\
void			VMStack::_instr_##NAME(std::string const *)			\
{																	\
	if (_disabledIf > 0)											\
		_disabledIf++;												\
	else															\
	{																\
		_nestedIf++;												\
		if (!(Operator::diff(*_get_last(), *_get_last(1)) OP 0))	\
			_disabledIf++;											\
	}																\
}

INSTR_IF_DEF(ifeq, ==);
INSTR_IF_DEF(ifneq, !=);
INSTR_IF_DEF(iflt, <);
INSTR_IF_DEF(ifgt, >);
INSTR_IF_DEF(ifle, <=);
INSTR_IF_DEF(ifge, >=);

void			VMStack::_instr_else(std::string const *)
{
	if (_disabledIf == 0)
		_disabledIf++;
	else if (_disabledIf == 1)
		_disabledIf--;
}

void			VMStack::_instr_endif(std::string const *)
{
	if (_disabledIf > 0)
	{
		_disabledIf--;
		if (_disabledIf == 0)
		{
			if (_nestedIf == 0)
				throw std::runtime_error("Unbound endif");
			_nestedIf--;
		}
	}
}
