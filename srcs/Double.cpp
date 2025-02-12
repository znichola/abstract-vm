/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Double.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Double.hpp"

// Default constructor
Double::Double()
{
}

// Copy constructor
Double::Double(const Double &other)
{
	*this = other;
}

// Destructor
Double::~Double()
{
}

// Copy assignment operator
Double &Double::operator=(const Double &other)
{
	(void)other;
	// TODO: insert return statement here
	return *this;
}


