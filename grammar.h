#ifndef GRAMMAR_H
#define GRAMMAR_H 1

#include "token.h"

// Expression function procecces operations '+' and '-'
// Expression is Term
//               Expression + Term
//               Expression - Term
func expression(Token_stream& ts);

// Term function processes operations '*' and '/'
// Term is Subterm
//         Term * Subterm
//         Term / Subterm
func term(Token_stream& ts);

// Subterm function processes operation '*' without symbol
// For example x*y == xy
// Subterm is Phrase
//            Subterm (*) Phrase
// But Phrase must not be Number
func subterm(Token_stream& ts, bool read_minus = true);

// Phase function processes operation '^' (power) (also work with doubles)
// Phrase is Primary
//           Primary ^ Subterm
//           - Phrase
func phrase(Token_stream& ts, bool read_minus = true);

// Primary function processes brases, numbers and arguments
// Primary is Number
//            Argument
//            ( Expression )
//            { Expression }
//            [ Expression ]
//            Function( Expression )
// Where Function is sin
//                   asin
//                   cos
//                   acos
//                   tan
//                   atan
func primary(Token_stream& ts);

#endif //  GRAMMAR_H
