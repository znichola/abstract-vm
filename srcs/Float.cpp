/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Float.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Float.hpp"

// Default constructor
Float::Float()
{
}

// Copy constructor
Float::Float(const Float &other)
{
	*this = other;
}

// Destructor
Float::~Float()
{
}

// Copy assignment operator
Float &Float::operator=(const Float &other)
{
	(void)other;
	// TODO: insert return statement here
	return *this;
}


