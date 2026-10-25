#include "pico/stdlib.h"

//special function keys(non mathematical things):
// AC, UP, DN, LT, RT, DEL, exe, shift, grph, vars, ans, =

const char *matrix[10][5] = {
    {"OFF" , "AC"  , "UP"  , "DEL", "ON"},
    {"BRT" , "LT"  , "DN"  , "RT" , "exe"},
    {"asin", "acos", "atan", "ln" , "shift"},
    {"sin" , "cos" , "tan" , "log", "rst"},
    {"X"   , "Y"   , "pi"  , "e"  , "^2"},
    {"("   , ")"   , "abs" , "^"  , "sqrt",},
    {"0"   , "."   , "(-)" , "/"  , "grph"},
    {"7"   , "8"   , "9"   , "*"  , "vars"},
    {"4"   , "5"   , "6"   , "-"  , "ans"},
    {"1"   , "2"   , "3"   , "+"  , "="}
};