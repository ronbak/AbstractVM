// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 12:27:18 by jaguillo          #+#    #+#             //
//   Updated: 2016/02/01 17:55:19 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VMSTACK_HPP
# define VMSTACK_HPP

# include <IOperand.hpp>
# include <istream>
# include <unordered_map>
# include <utility>
# include <vector>

/*
** VMStack
** -
** Available operations:
**  input		Read from stdin (Take an argument: the default value/type)
**  push		Push a value on the stack (Take an argument)
**  pop			Pop the top of the stack
**  set			Change the top value (use the same type)
**  dump		Dump all the stack
**  assert		Compare the top value (Take an argument)
**  swap		Swap the top value with the nth value (Take an argument)
**  dup			Dupplicate the n top values
**  top			Print the top value
**  add			Add the 2 top values, consume them and push the result
**  sub			Substraction, same behavior as add
**  mul			Multiplication, same behavior as add
**  div			Division, same behavior as add
**  mod			Modulo, same behavior as add
**  if==		Compare the 2 top values
**  if!=		Compare the 2 top values
**  if<			Compare the 2 top values
**  if>			Compare the 2 top values
**  if<=		Compare the 2 top values
**  if>=		Compare the 2 top values
**  else		Else
**  endif		Endif
**  print		Print the top value if it is an int8
**  exit		End
** TODO: rotate
*/

class	VMStack
{
public:
	VMStack(void);
	virtual ~VMStack(void);

	void			run(void);
	void			run(std::string const &filename);
	void			run(std::istream &in,
						std::string const &filename, bool eot = false);

protected:

	typedef void		(VMStack::*instr_t)(std::string const *param);

	std::regex						_run_regex;

	std::string						_filename;

	std::vector<IOperand const*>	_stack;

	bool							_exited;
	uint32_t						_nestedIf;
	uint32_t						_disabledIf;

	void			_exec(std::string const &instr, std::string const *param = nullptr);

	IOperand const	*_get_last(uint32_t n = 0);
	IOperand const	*_extract_last(void);

	void			_instr_input(std::string const *param);
	void			_instr_push(std::string const *param);
	void			_instr_pop(std::string const *param);
	void			_instr_set(std::string const *param);
	void			_instr_call(std::string const *param);
	void			_instr_dump(std::string const *param);
	void			_instr_assert(std::string const *param);
	void			_instr_swap(std::string const *param);
	void			_instr_dup(std::string const *param);
	void			_instr_top(std::string const *param);
	void			_instr_add(std::string const *param);
	void			_instr_sub(std::string const *param);
	void			_instr_mul(std::string const *param);
	void			_instr_div(std::string const *param);
	void			_instr_mod(std::string const *param);
	void			_instr_print(std::string const *param);
	void			_instr_exit(std::string const *param);
	void			_instr_ifeq(std::string const *param);
	void			_instr_ifneq(std::string const *param);
	void			_instr_iflt(std::string const *param);
	void			_instr_ifgt(std::string const *param);
	void			_instr_ifle(std::string const *param);
	void			_instr_ifge(std::string const *param);
	void			_instr_else(std::string const *param);
	void			_instr_endif(std::string const *param);

	static std::unordered_map<std::string, std::tuple<instr_t, bool, bool>> const	_instructions;

private:
	VMStack(VMStack &&src) = delete;
	VMStack(VMStack const &src) = delete;
	VMStack			&operator=(VMStack &&rhs) = delete;
	VMStack			&operator=(VMStack const &rhs) = delete;
};

#endif
