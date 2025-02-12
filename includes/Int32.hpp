/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int32.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/12 12:07:49 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT32_HPP
# define INT32_HPP

class Int32
{
private:

public:
// Default constructor
	Int32();

// Copy constructor
	Int32(const Int32 &other);

// Destructor
	~Int32();

// Copy assignment operator
	Int32 & operator=(const Int32 &other);
};

#endif /* INT32_HPP */
