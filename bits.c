/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  return (x + (x >> 31)) ^ (x >> 31);
}



/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {

  //overflow can only occur when signs of two numbers are the same

  //addOk checks if the msb of sum is different from both x and y
  //If the sign of sum matches sign of x or y, 
  //no overflow has occurred, function returns 1
  //otherwise, if sign of sum doesn't match x or y, overflow has occurred, 0 is returned

  int sumsign = ((x+y) >> 31) & 1;
  int signx = (x >> 31) & 1;
  int signy = (y >> 31) & 1;
  
  //only return 0 when the sign of the sum matches neither x nor y
  int valid = (!(sumsign ^ signx)) | (!(sumsign ^ signy));
  return valid;

}



/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
 
  int b1 = x >> 24;
  int b2 = x >> 16;  
  int b3 = x >> 8;
  int b4 = x;

  int checkeven = (b1 & b2 & b3 & b4 & 0x55) + 0xAA;
  // if even, checkeven = 255, else it equals something else
  //int res = ~(~checkeven << 24) + 1;
  //if all even bits are set to 1, result will now be 0, otherwise it's nonzero
  int result = (checkeven ^ 0xFF);
  return !result;
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

  //maskn gives mask for nth byte
  int maskn = 0xFF << (n << 3);
  int nbytes = ((x & maskn) >> (n << 3)) & 0xFF;
  
  //maskm gives mask for mth byte
  int maskm = 0xFF << (m << 3);
  int mbytes = ((x & maskm) >> (m << 3)) & 0xFF;

  //result retains all other bytes besides nth and mth bytes
  int result = (~(maskm | maskn)) & x;

  //moves nbytes into the original mbyte position
  nbytes = nbytes << (m << 3);

  //moves mbytes into the original n byte position
  mbytes = mbytes << (n << 3);

  return result | mbytes | nbytes;
}



/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int sign = x >> 31; // gets sign
  int masked = (1 << n) + (1 << 31 >> 31); // mask of 1's
  int checkadd = sign & masked;
  return (x + checkadd) >> n;
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
  
  int value = (x << 1) + x;

  //this mask gives 1 for negative, 0 for positive
  int offset = ((value >> 31) & 1);

  //if positive, offset is zero so nothing is added 
  //if value is negative, offset is one, and bias is calculated
  value += ((offset << 2) + (~offset) + 1);
  value = (value >> 2);
  return value;
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int shift = 32 + (~n + 1); // (~n + 1) gives negative of n, so we get 32 - n
  int truncateshift = x << shift >> shift; 
  return !(x ^ truncateshift); //!(x^y) is equivalent to x == y
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  
  int setmsb = x | (x >> 1);
  int isolatemsb;
  setmsb = setmsb | (setmsb >> 2);
  setmsb = setmsb | (setmsb >> 4);
  setmsb = setmsb | (setmsb >> 8);
  setmsb = setmsb | (setmsb >> 16); // all bits to the right of msb are 1
  isolatemsb = setmsb & (~setmsb >> 1); // all bits to right of msb are 0
  return (isolatemsb | (1 << 31)) & setmsb; 
}


/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int count = 0;
  
  int has8, has4, has2, has1;
  int xby8, xby4, xby2, xby1;
  int x16, x8, x4, x2;
  
  int xby16 = x >> 16; // shift out 16 bits
  int has16 = !!(xby16 & (0xFF << 8 | 0xFF)); // check if at least 16 bits
  count = has16 << 4; // add 16 to count if there are 16 bits
  x16 = x >> count; // shift x by 16 if at least 16, shift by 0 otherwise
  xby8 = x16 >> 8; // repeat for 8 bits
  has8 = !!(xby8 & 0xFF);
  count = count + (has8 << 3);
  x8 = x >> count; 
  xby4 = x8 >> 4; // repeat for 4 bits
  has4 = !!(xby4 & 0x0F);
  count = count + (has4 << 2);
  x4 = x >> count;
  xby2 = x4 >> 2; // repeat for 2 bits
  has2 = !!(xby2 & 0x03);
  count = count + (has2 << 1);
  x2 = x >> count;
  xby1 = x2 >> 1; // repeat for 1 bit
  has1 = !!(xby1 & 0x01);
  count = count + has1;
  return count;
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {

  return ((!x) | y);
   
}


/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  int checkx = x & (~(1 << 31));
  int maskones = 1 << 31 >> 31; // mask of 1's
  return (!(checkx & (checkx + maskones))) & ((x >> 31) ^ 1) & !!x;
}



/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */

int logicalNeg(int x) {

  //(~x + 1) gives negative of x
  //negating any nonzero number and ORing it with original produces a 1 in leftmost bit
  //shifting over by 31 results in all ones or all zeroes
  //this operation reduces any nonzero number to 1, 0 remains 0
  x = (((~x+1) | x) >> 31  & 1);

  //must reverse the bit in order to return correct value
  return x^1;

}



/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  int mult5 = (x << 2) + x; // multiply by 5
  int sign = x >> 31 & 1; // mask out sign bit
  return (mult5 + (sign << 3) + (~sign + 1)) >> 3; // divide by 8 and round
}



/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */


int rotateLeft(int x, int n) {

  int result = (x << n);//leftmost (32-n) bits are correct

  //(32 + (~n + 1)) is 32 - n
  //amount we need to shift the most significant n bits, to the right
  int rightshift = (32 + (~n + 1));

  //~(~0 << n) sets mask of ones for n right most bits, to account for wraparound 
  //thus moving the chunk of left most n bits into the right most position
  int rightmask = ~(~0 << n);
  result |= ((x >> rightshift) & rightmask);

  return result;
}


/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  int sum = x + y;  
  int signx = x >> 31; // get signx
  int signy = y >> 31; // get signy, note overflow: only when signx == signy
  int signs = sum >> 31; // get sign of sum
  int chkOver = (signs ^ signx) & (signs ^ signy); // true(1) if signs != signx and signs != signy, false(0) otherwise
  return (sum >> (chkOver & 31)) + (chkOver << 31); // if chkOver == 0, return sum, if chkOver == 1, set return to max/min
}



/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
  
  //leave positive numbers unchanged
  //for negative numbers, subtract 1, flip everything, then add 1 to MSB
  //int sign = ((x >> 31) & 1);

  int sign = (x >> 31);//all 1's or all 0's
  //need to add an extra 1 when converting negative values, because
  //
  int sub = (sign & 1);
  int y = (x ^ sign) + ((sign & 1) << 31) + sub;
  //subtract one from x
  //x = (~x + 1) + (sign << 31);
  //x = (x + ~sign + 1) ^ (sign << 31);

  return y;
}




/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
  //procedure: if negative, subtract one from tc, flip everything, add 1 to MSB
  //if positive, extra is 0, and MSB and the LSB are not changed

  //ex: -3
  //tc: 1111...1101
  //sm: 1000...0011

  //ex: 3
  //tc: 0000...0011
  //sm: 0000...0011


  int sign = (x >> 31);
  int extra = sign & 1;//1 if negative,  0 if positive
  // "^sign" flips every bit when x is negative, does nothing to positive values 
  int y = ((x + ((~extra) + 1))  ^ sign) + (x & (1 << 31)); 
  

  return y;
}




/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
  int signbit = (x >> 31) & 1; // gives sign bit
  int div4 = x >> 2;
  int mult3 = (div4 << 1) + div4; // multiply div4 by 3;
  int shiftedbits = x & 3;
  int shiftedbitsby3 = (shiftedbits << 1) + shiftedbits;
  int shiftedbitsdiv4 = (shiftedbitsby3 + (signbit << 2) + (~signbit + 1)) >> 2;
  int sum = mult3 + shiftedbitsdiv4;
  return sum;
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */

int trueFiveEighths(int x)
{
  int signbit = (x >> 31) & 1; // gives sign bit
  int div8 = x >> 3;
  int mult5 = (div8 << 2) + div8; // multiply div8 by 5;
  int shiftedbits = x & 7;
  int shiftedbitsby5 = (shiftedbits << 2) + shiftedbits;
  int shiftedbitsdiv8 = (shiftedbitsby5 + (signbit << 3) + (~signbit + 1)) >> 3;
  int sum = mult5 + shiftedbitsdiv8;
  return sum;
}
