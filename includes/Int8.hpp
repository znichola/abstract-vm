/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT8_HPP
# define INT8_HPP

class Int8
{
private:

public:
// Default constructor
	Int8();

// Copy constructor
	Int8(const Int8 &other);

// Destructor
	~Int8();

// Copy assignment operator
	Int8 & operator=(const Int8 &other);
};

#endif /* INT8_HPP */
