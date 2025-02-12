/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Int8.hpp"

// Default constructor
Int8::Int8()
{
}

// Copy constructor
Int8::Int8(const Int8 &other)
{
	*this = other;
}

// Destructor
Int8::~Int8()
{
}

// Copy assignment operator
Int8 &Int8::operator=(const Int8 &other)
{
	(void)other;
	// TODO: insert return statement here
	return *this;
}


