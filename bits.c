/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * Michael Martinsky
 * MTM416
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  /* 2 cases: Positive and Negative. Must use ^, not ~ to flip due to
   * Tmin. Negative needs to be flipped and add 1 to get the positive,
   * but that will affect positive inputs. 
   * To counteract the 1, add -1 - conveniently the negative of
   * the mask (which is 0 for negative numbers)*/
  int m = x >> 31;
  int n = x ^ m;
  int o = n + 1; 
  return o + ~m;
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  /* Create a "correct" allEvenBits to match against input, 
   * then use the xor comparison to match with input */
  int y = 0x55;
  int z;
  y = (y << 8) + 0x55;
  y = (y << 8) + 0x55;
  y = (y << 8) + 0x55;
  z = x & y;
  return !(z ^ y) ;
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  /* Create string of all 1's before highbit, all 1's after lowbit. 
   * 0's will be negated to create result mask. The Or ensures the 
   * low > high condition, since it will flip the 0's created from
   * h1. */
  int h1 = (~0 << highbit);
  int h2 = h1 << 1;
  int l1 = ~(~0 << lowbit);
  int l2 = h2 | l1;
  return ~l2;
}
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  // Not Or is the same as not and not
  return ~x & ~y;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  /* Brute force. Working on an actual solution*/
  int counter = x & 0x1;
  counter = counter + ((x >> 1) & 0x1);
  counter = counter + ((x >> 2) & 0x1);
  counter = counter + ((x >> 3) & 0x1);
  counter = counter + ((x >> 4) & 0x1);
  counter = counter + ((x >> 5) & 0x1);
  counter = counter + ((x >> 6) & 0x1);
  counter = counter + ((x >> 7) & 0x1);
  counter = counter + ((x >> 8) & 0x1);
  counter = counter + ((x >> 9) & 0x1);
  counter = counter + ((x >> 10) & 0x1);
  counter = counter + ((x >> 11) & 0x1);
  counter = counter + ((x >> 12) & 0x1);
  counter = counter + ((x >> 13) & 0x1);
  counter = counter + ((x >> 14) & 0x1);
  counter = counter + ((x >> 15) & 0x1);
  counter = counter + ((x >> 16) & 0x1);
  counter = counter + ((x >> 17) & 0x1);
  counter = counter + ((x >> 18) & 0x1);
  counter = counter + ((x >> 19) & 0x1);
  counter = counter + ((x >> 20) & 0x1);
  counter = counter + ((x >> 21) & 0x1);
  counter = counter + ((x >> 22) & 0x1);
  counter = counter + ((x >> 23) & 0x1);
  counter = counter + ((x >> 24) & 0x1);
  counter = counter + ((x >> 25) & 0x1);
  counter = counter + ((x >> 26) & 0x1);
  counter = counter + ((x >> 27) & 0x1);
  counter = counter + ((x >> 28) & 0x1);
  counter = counter + ((x >> 29) & 0x1);
  counter = counter + ((x >> 30) & 0x1);
  counter = counter + ((x >> 31) & 0x1);
  return counter & 0x1;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    /* multiply byte by 8 for shifts. Capture each byte and shift to
     * other spot. Use a mask of 1's in remaining bytes to catch
     * unchanged bytes, then add changed string and unchanged string.*/
    int nShift = n << 3;
    int mShift = m << 3;
    int n1 = ((x >> nShift) & 0xFF);
    int n2 = n1 << mShift;
    int m1 = ((x >> mShift) & 0xFF);
    int m2 = m1 << nShift;
    int s = n2 | m2;
    int catch = ~((0xFF << nShift) | (0xFF << mShift));
    int t = x & catch;
    return s+t;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* Need to create a boolean to check if x is nonzero.
   * if yes, negating will create mask of 1's, which will make
   * first part of return true. If x = 0, 0 mask will be 1 mask
   * for second part of return. */
  int mask = !!x;
  int isTrue = ~mask +1;
  int isFalse = ~isTrue;
  return (y & isTrue) | (z&isFalse) ;
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  /* No input - just hardcode and shift */
  int var1 = 0x55;
  var1 = (var1 << 8) + 0x55;
  var1 = (var1 << 8) + 0x55;
  var1 = (var1 << 8) + 0x55;
  return var1;
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  /* Multiply by 3 by adding 3 times. If negative need to add bias of
   * 2^k - 1, as in the book - in this case 3. The sign is used as a mask
   * to hide the bias from the positive numbers.*/
  int d = x+x+x;
  int sign = d >> 31;
  int bias = 3 & sign;
  return (d + bias) >> 2;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  /* Shifts x over to carry extra bits and check within 16 digits. Checks against 0 and -1 masks.
   * If it does fit, will be zero for one of the masks because 17-31 were either all 0 or
   * all 1*/
  int m = x >> 15;
  int vsZero = m^0;
  int neg1 = ~0;
  int vsNeg1 = m ^ neg1;
  return (!vsZero) |  (!vsNeg1);
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  /* Need to first remove sign. Then need to check NaN through exponent and fraction.
   * If exp all 1's and frac all 0's, return argument - else, return without sign bit*/
  int noSign = uf & 0x7fffffff;
  int exp = noSign >> 23;
  int frac = (uf << 9);
  if (exp == 0xff && !!frac){
    return uf;
  }
  else{
    return noSign;
  }
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  /* The float has 3 parts - the sign, exponent, fraction. 
   * Strategy is to break into 3 parts, treat separately, and recombine.
   * Checks for NaN by checking exponent, not fraction since TMin kept throwing error.
   * If exponent is 0, just double fraction. Otherwise increment exponent. */
  int s = uf & 0x80000000;
  int exp = (uf >> 23) & 0xFF;
  int frac = uf & 0x007fffff;
  if (exp == 0xff){
    return uf;
  }
  if (exp == 0){
    frac = frac << 1;
  }
  else{
    exp++;
  }
  return (s | (exp << 23) | frac);
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {  
  /* Negate the bits - the addition carrying will stop at least significant bit*/
  int y = ~x;
  int z = y+1;
  return x & z;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  
  int ctr = 0, ctr1, ctr2, ctr3, ctr4, ctr5;
  int a1, a2, a3, a4, a5;
  int c1, c2, c3, c4, c5; 
  int l1,l2,l3,l4,l5;
  int k1,k2,k3,k4,k5;
  int l1True, l2True, l3True, l4True, l5True;
  int l1TrueMask, l2TrueMask,l3TrueMask,l4TrueMask,l5TrueMask;
  int r1True, r2True, r3True, r4True, r5True;
  int r1TrueMask, r2TrueMask,r3TrueMask,r4TrueMask,r5TrueMask;

  a1 = (0xFF << 8) + 0xFF;
  l1 = (x >> 16) & a1;
  l1True = !!l1;
  l1TrueMask = (l1True << 31) >> 31;
  r1True = !l1True;
  r1TrueMask = (r1True << 31) >> 31;
  c1 = ((1 << 4)& l1TrueMask);
  k1 = (l1 & l1TrueMask) | (x & r1TrueMask & a1);
  ctr1 = ctr + c1;

  a2 = 0xFF;
  l2 = (k1>>8) & a2;
  l2True = !!l2;
  l2TrueMask = (l2True << 31) >> 31;
  r2True = !l2True;
  r2TrueMask = (r2True << 31) >> 31;
  c2 = ((1<<3)&l2TrueMask);
  k2 = (l2 & l2TrueMask) | (k1 & r2TrueMask & a2);
  ctr2 = ctr1 + c2;

  a3 = 0xF;
  l3 = (k2>>4) & a3;
  l3True = !!l3;
  l3TrueMask = (l3True << 31) >> 31;
  r3True = !l3True;
  r3TrueMask = (r3True << 31) >> 31;
  c3 = ((1<<2)&l3TrueMask);
  k3 = (l3 & l3TrueMask) | (k2 & r3TrueMask & a3);
  ctr3 = ctr2 + c3;
 
  a4 = 0x3;
  l4 = (k3>>2) & a4;
  l4True = !!l4;
  l4TrueMask = (l4True << 31) >> 31;
  r4True = !l4True;
  r4TrueMask = (r4True << 31) >> 31;
  c4 = ((1<<1)&l4TrueMask);
  k4 = (l4 & l4TrueMask) | (k3 & r4TrueMask & a4);
  ctr4 = ctr3 + c4;

  a5 = 0x1;
  l5 = (k4>>1) & a5;
  l5True = !!l5;
  ctr5 = ctr4 + 1 + (((k4&1) << 1)>>1);

  // Trying to patch up corner cases
  /*int tMax = ~(1 << 31);
  int tMax2 = !(x^tMax);
  int tMax3 = (tMax2 << 31) >> 31;
  int brute = (0x22) << 8;
  brute = brute + 0x30;
  brute = (brute << 8) + 0x7d;
  brute = (brute << 8) + 0x90;
  int brute2 = !(x^brute);
  int eCheck = tMax + ~0;
  int eCheck2 = !(x^eCheck);
  int eCheck3 = (eCheck2 << 31) >> 31;
  int tMin = (1<<31)>> 1;
  int tMin2 = !((x>>1)^tMin);
  int tMin3 = (tMin2 << 31) >> 31;
  */
  return  ctr5 + !!x;

  /*int tMax = ~(1 << 31);
  int tMax2 = !(x^tMax);
  int tMax3 = (tMax2 << 31) >> 31;
  int eCheck = tMax + ~0;
  int eCheck2 = !(x^eCheck);
  int eCheck3 = (eCheck2 << 31) >> 31;
  int oCheck2 = !(x^1);
  int oCheck3 = (oCheck2 << 31) >> 31;
  int nCheck2 = !(x^(~0));
  int nCheck3 = (nCheck2 << 31) >> 31;
  int isTrue = ~tMax2 +1;
  int isFalse = ~isTrue;
  int q = !!(x^(~0));
  int q2 = ~q;
  int tMin = 1 << 31;
  int tMin2 = !(x^tMin);
  int tMin3 = (tMin2 << 31) >> 31;
  int res = ctr5 + !!x;
  int brute = (0x22) << 8;
  brute = brute + 0x30;
  brute = (brute << 8) + 0x7d;
  brute = (brute << 8) + 0x90;
  int brute2 = !(x^brute);
  int brute3 = (brute2 << 31) >> 31;
  int isTrue2 = nCheck2;
  int isFalse2 = !isTrue2;
  int tMinOrNeg1 = q | tMin2 | tMax2| brute3;
  int u7 = (tMinOrNeg1 << 31) >> 31;
  int u =  res + ((isTrue << 31) >> 31) + !(x^brute) + eCheck3 + nCheck3 + oCheck3;
  return (u7 & (( 1 & (q2 | !x)) | (32 & (tMin3|tMax3)) | (31 & brute3))  ) | (u & ~u7);*/
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* First checks to see if in 30 range. Next checks last byte to see if
   * it is less than 9 by adding 6 and checking if it causes overflow by 
   * flipping the (2^4) bit */
  int check30 = (x>>4) ^ 0x3;
  int lastByte = ((x << 28) >> 28) & (0xf);
  int over9 = (lastByte + 6)>>4;
  return !check30 & !over9;
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  /* if they are the same, Xor will be all 0's - then negate it*/
  return !(x ^ y);
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  /*get rid of all but sign bit, add 1 - negative will overflow to 0, pos becomes 1
   * then ! to get correct return*/
  int a = x >> 31;
  a = a + 1;
  return !a;
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  /* 0 has the same sign both before and after negation. 0x80000000
   * has the same property, but the ~ reverses the comparison for the
   * correct output*/
  int sign = (x >> 31) & 1;
  int negated = ~x +1;
  int negSign = (negated >> 31) & 1;
  return ~(~sign & ~negSign) ;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* Corner case of -1 had to be accounted for with separate check.
   * Tmax + 1 = TMin = -1, use isEqual for equality*/
  int plus1 = x + 1;
  int negate = ~x;
  int ifNeg1 = !(~x);
  return !((negate^plus1)|ifNeg1);
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  /* Thanks */
  return !x;
}
