# Mathematical Interpreter

This project is a mathematical interpreter that allows users to input and evaluate mathematical expressions using various operators, including binary, unary, and logical operations. The interpreter supports numbers, parentheses, and operators, providing a high degree of flexibility and accuracy in calculations.

## Key Features

- Operator Support:
  - Arithmetic Operators: `+`, `-`, `*`, `/`, `^` (exponentiation)
  - Logical Operators: `&&`, `||`, `!` (logical AND, logical OR, logical NOT)
  - Comparison Operators: `==`, `!=`, `>`, `<`, `>=`, `<=`
  
- Error Handling: 
  - Exceptions for division by zero.
  - Handling of invalid mathematical expressions and operators.
  - Special error handling for invalid usage of logical operators.

## Usage

Simply enter a mathematical expression in the terminal, and the interpreter will compute the result. Examples of input data:

```plaintext
2 + 3
5 * (10 - 4)
```

## Examples

### Valid Expressions:
- `5 + 3` → `8`
- `10 / 2` → `5`
- `3 * (2 + 1)` → `9`
- `3.1 + 2,8` → `5.9`
- `!(!(~1))` → `1`
  
### Invalid Expressions:
- `10 / 0` → Exception: Division by zero.
- `5 +` → Exception: Invalid expression.
- `1,1,1 + 1.1` → Exception: Invalid operand.
- `!!~1` → Exception: Unexpected end of expression.
