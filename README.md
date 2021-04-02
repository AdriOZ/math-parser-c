# math-parser-c

This is just a personal project: a program that reads an input string like `(1 + 1) * (1 + 1)`, parses it, and returns the result of the math expression.

So far, the only operators it can handle are:

- Addition `+`
- Substraction `-`
- Multiplication `*`
- Division `/`
- And groups of operations using `(` and `)`.

This program uses the **Shunting Yard** algorithm to transform the list of tokens into a **reversed polish notation**, respecting the operators precedence and groupings.

Finally, it computes the result and returns it. If the expression contained errors, then it doesn't calculate the result, and returns the description of the error.
