/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int32.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Int32.hpp"

// Default constructor
Int32::Int32()
{
}

// Copy constructor
Int32::Int32(const Int32 &other)
{
	*this = other;
}

// Destructor
Int32::~Int32()
{
}

// Copy assignment operator
Int32 &Int32::operator=(const Int32 &other)
{
	(void)other;
	// TODO: insert return statement here
	return *this;
}


