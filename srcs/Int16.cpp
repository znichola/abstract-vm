/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int16.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Int16.hpp"

// Default constructor
Int16::Int16()
{
}

// Copy constructor
Int16::Int16(const Int16 &other)
{
	*this = other;
}

// Destructor
Int16::~Int16()
{
}

// Copy assignment operator
Int16 &Int16::operator=(const Int16 &other)
{
	(void)other;
	// TODO: insert return statement here
	return *this;
}


