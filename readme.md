# Clox

Learning compiler construction, C, and glib.

## Todo challenges

### Chapter 14

- [ ] Use run-length encoding of the line numbers. For better space complexity
- [ ] Support for `OP_CONSTANT_LONG` instruction. It stores the operand as a 24-bit number.

### Chapter 15

- [ ] To interpret `OP_NEGATE`, we pop the operand, negate the value, and then push the result. That’s a simple implementation, but it push and pop to the stack unnecessarily, since the stack ends up the same height in the end. It might be faster to simply negate the value in place on the stack. Try that and see if you can measure a performance difference.

### Chapter 16

- [ ] Support string interpolation `${var}`. Consider looking at other language implementations that support interpolation to see how they handle it
