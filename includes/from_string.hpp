// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   from_string.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 18:24:18 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/28 18:25:17 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FROM_STRING_HPP
# define FROM_STRING_HPP

# include <string>

/*
** Convert to string
** Support only int8_t, int16_t, int32_t, float and double
*/

template<typename T>
T			from_string(std::string const &str);

# include "templates/from_string.tpp"

#endif
