/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int16.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT16_HPP
# define INT16_HPP

class Int16
{
private:

public:
// Default constructor
	Int16();

// Copy constructor
	Int16(const Int16 &other);

// Destructor
	~Int16();

// Copy assignment operator
	Int16 & operator=(const Int16 &other);
};

#endif /* INT16_HPP */
