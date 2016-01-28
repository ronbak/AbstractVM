// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 12:27:18 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/28 14:34:17 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VMSTACK_HPP
# define VMSTACK_HPP

# include <IOperand.hpp>
# include <unordered_map>
# include <utility>
# include <vector>

/*
** VMStack
** -
** Available operations:
**  push		Push a value on the stack (Take an argument)
**  pop			Pop the top of the stack
**  dump		Dump all the stack
**  assert		Compare the top value (Take an argument)
**  swap		Swap the 2 top values
**  add			Add the 2 top values, consume them and push the result
**  sub			Substraction, same behavior as add
**  mul			Multiplication, same behavior as add
**  div			Division, same behavior as add
**  mod			Modulo, same behavior as add
**  print		Print the top value
**  exit		End
** TODO: rotate, read input
** TODO: if>, if<, if==, if>=, if<=, if!=, else, endif
*/

class	VMStack
{
public:
	VMStack(void);
	virtual ~VMStack(void);

	void			exec(std::string const &instr, std::string const *param = nullptr);

protected:

	typedef void		(VMStack::*instr_t)(std::string const *param);

	std::vector<IOperand const*>	_stack;
	bool							_exited;

	IOperand const	*_get_last(void);
	IOperand const	*_extract_last(void);

	void			_instr_push(std::string const *param);
	void			_instr_pop(std::string const *param);
	void			_instr_dump(std::string const *param);
	void			_instr_assert(std::string const *param);
	void			_instr_swap(std::string const *param);
	void			_instr_add(std::string const *param);
	void			_instr_sub(std::string const *param);
	void			_instr_mul(std::string const *param);
	void			_instr_div(std::string const *param);
	void			_instr_mod(std::string const *param);
	void			_instr_print(std::string const *param);
	void			_instr_exit(std::string const *param);

	static std::unordered_map<std::string, std::pair<instr_t, bool>> const	_instructions;

private:
	VMStack(VMStack &&src) = delete;
	VMStack(VMStack const &src) = delete;
	VMStack			&operator=(VMStack &&rhs) = delete;
	VMStack			&operator=(VMStack const &rhs) = delete;
};

#endif
