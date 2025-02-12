/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Float.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_HPP
# define FLOAT_HPP

class Float
{
private:

public:
// Default constructor
	Float();

// Copy constructor
	Float(const Float &other);

// Destructor
	~Float();

// Copy assignment operator
	Float & operator=(const Float &other);
};

#endif /* FLOAT_HPP */
