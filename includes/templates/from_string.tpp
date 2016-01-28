// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   from_string.tpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 18:19:17 by jaguillo          #+#    #+#             //
//   Updated: 2016/01/28 18:26:22 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

template<typename T>
T			from_string(std::string const &str)
{
	return (T(str));
}

template<>
inline int8_t	from_string(std::string const &str)
{
	return (std::stoi(str));
}

template<>
inline int16_t	from_string(std::string const &str)
{
	return (std::stoi(str));
}

template<>
inline int32_t	from_string(std::string const &str)
{
	return (std::stol(str));
}

template<>
inline float	from_string(std::string const &str)
{
	return (std::stof(str));
}

template<>
inline double	from_string(std::string const &str)
{
	return (std::stod(str));
}
