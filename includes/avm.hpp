/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:07:49 by znichola          #+#    #+#             */
/*   Updated: 2025/02/17 14:59:09 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVM_HPP
# define AVM_HPP

// Tokenizing and Lexographic analysis
# include "Lexer.hpp"
# include "Token.hpp"
# include "eTokenType.hpp"
# include "SyntaxError.hpp"

// Parsing & Bytecode gen
# include "Parser.hpp"
# include "Instruction.hpp"

// Runtime
# include "Runtime.hpp"
# include "Stack.hpp"
# include "Factory.hpp"

# include "Base.hpp"
# include "IOperand.hpp"
# include "eOperandType.hpp"

#endif /* AVM_HPP */

