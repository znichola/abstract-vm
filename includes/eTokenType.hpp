#ifndef ETOKENTYPE_HPP
# define ETOKENTYPE_HPP

# include <string>
# include <utility>

enum eTokenType {
     t_int8
    ,t_int16
    ,t_int32
    ,t_float
    ,t_double

    ,t_push
    ,t_pop
    ,t_dump
    ,t_assert
    ,t_add
    ,t_sub
    ,t_mul
    ,t_div
    ,t_mod
    ,t_print
    ,t_exit

    ,t_sep
    ,t_err
};

#endif /* ETOKENTYPE_HPP */
