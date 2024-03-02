#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

#define SET_BIT(NUM,POS) (NUM |= (1<<POS))
#define CLEAR_BIT(NUM,POS) (NUM &= ~(1<<POS))
#define TOGGLE_BIT(NUM,POS) (NUM ^= (1<<POS))
#define GET_BIT(NUM,POS) ((NUM>>POS) & 1)

#endif