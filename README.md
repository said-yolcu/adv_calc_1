# adv_calc_1

## 1. Introduction

We are asked to implement an interactive interpreter. This interpreter prompts the user for a line of AdvCalc. After the line is received, it is evaluated and output is written to the console. Then the user is prompted again and this process repeats until the user presses Ctrl + C. This keyboard interrupt, terminates the program (in Linux).

## 2. How to Run

Download the project. Open the project folder in terminal window. Run `make` command. This will generate the executable *advcalc*. Run the executable via typing `./advcalc` to the command-line. In the interactive interpreter, type whatever AdvCalc line you want. To exit the interactive interpreter, type Ctrl + C .

## 3. Problem Specification

AdvCalc is a simple calculation programming language. It is comprised of variables and operations. There are 11 operations in the language:

| Operation | Explanation |
| --------- | -------------------------------------- |
| a + b | Returns the summation of a and b |
| a * b | Returns the multiplication of a and b |
| a - b | Returns the subtraction of b from a |
| a & b | Returns bitwise a and b |
| a &#124; | Returns bitwise a or b |
| xor(a, b) | Returns bitwise a xor b |
| ls(a, i) | Returns the result of a shifted i bits to the left |
| rs(a, i) | Returns the result of a shifted i bits to the right |
| lr(a, i) | Returns the result of a rotated i times to the left |
| rr(a, i) | Returns the result of a rotated i times to the right |
| not(a) | Returns bitwise complement of a |

Following **assumptions** will hold for the language:

1. Every value and calculation will be integer valued.
2. There will be no expressions or assignments with a result that exceeds a 64-bit number.
3. Similarly, every bit-wise intermediate operation will abide by the 64-bit limit.
4. The language does not support the unary minus (-) operator (i.e x = -5 or a = -b is not valid). However,as can be seen above, the subtraction operation is allowed.
5. The variable names will consist of lowercase and uppercase Latin characters in the English alphabet &#91; a-zA-Z &#93; .
6. Expressions or assignments will consist of 256 characters at most.
7. Undefined variables have a value of 0.
8. ’%’ characters denote comments. Any characters after ’%’ will be considered as a comment, not code.
9. The execution of the program will be done through the interpreter screen working in the terminal - in other words, it won’t be a file-based program. It should work just like the Python interpreter.
10. You must run and test your code on an Ubuntu Linux machine before submitting. You can use a Linux virtual machine or WSL in this context.
11. Apart from the valid expressions and statements, the AdvCalc interpreter must state an error in case of a faulty operation. However, the program should continue to run. For such cases, an error message should be displayed in a new line in the exact form below:

	Error!
	
12. The input may include all sorts of syntax errors.
13. All of the following can be given as an input - and all of them are valid: a + b, a+ b, a + b, a+b, a +b, (((a))) + (b).

## 4. Solution Explained

In order to come up with a solution, first of all we should go over the basic architecture af an interpreter (or for that matter a transpiler). An interpreter performs the steps below:

1. Reads a line
2. Tokenizes the line
3. Parses the line
4. Calculates the result
5. Prints out the result

### 4.1. Structures

We should start coding the solution by creating the necessary structures for Tokenization and Parsing. After the Tokenization process the line will be divided into Tokens, which will comprise a list (or array). Let me start from the Token struct.

#### 4.1.1. Token

```C
// Token structure, each token consists of a Node tree
typedef struct Tokens
{
    int layer;

    // Whichth token from the beginning, starting from 0
    int number;

    struct Tokens *next; // Next token
    struct Tokens *prev; // Previous token

    Node *this; // Pointer to this node
} Token;
```

layer field denotes the layer of of parantheses that Token is in. For example for `b` layer of b is 0, whereas for `((b))` layer of b is 2. This layer information will come in handy when we are parsing the Token list, and need to match opening and closing parantheses that must naturally be in the same layer.

number field denotes whichth Token from the beginning that Token is.

next and prev Token pointers point to next and previous Tokens. I used a linked-list while storing the Tokens. But I could have used arrays, in which case I wouldn't have needed many of these fields.

this points to a Node. During Tokenization I already stored certain information regarding that Token in a *this* Node. This makes parsing process easier, as I only connect the Node of different Tokens under a single Token to obtain the parse tree.

#### 4.1.2. Node

```C
// Node structure
typedef struct Nodes
{
    enum
    {
        VAR, // 0 Variable
        OPR, // 1 Operator: + * - & |
        BIN, // 2 Binary Function: xor, ls, rs, lr, rr
        UNA, // 3 Unary Function: not
        COM, // 4 Comma
        PAR, // 5 Parantheses
        NUM, // 6 Number
        ASG  // 7 Assignment
    } type;

    char name[MAX_NAME];

    struct Nodes *left;  // Node on the left
    struct Nodes *right; // Node on the rigth

} Node;
```

In Node struct, *type* field stores the type of the Node. It can be either a variable, operator, binary function, unary function, comma, paranthesis, number, or assignment operator. There is no *type* for comments as they are already gotten rid of before Tokenization process.

*name* field stores the name of the variable or binary function. It is also used in storing the operator or paranthesis. Numerical values of numbers are also stored here. It is not necessary to store a unary function, comma, or assignment operator as there are only single instances for each type.

*left* and *right* Node pointers store the address of the left and right childs respectively. It is important to remember that after parsing, the Nodes are ordered in a binary tree. To be more clear, it is not a strict binary tree as the unary operation *not* has only a single argument, thus a single child.

#### 4.1.3. Variable

```C
typedef struct Variables
{
    // Name of the variable
    char name[MAX_NAME]; 

    // Value of the variable. Do not forget it is LONG not INT
    long value; 

    // Pointer to next variable
    struct Variables * next;
}Variable;
```

During a session, we need to store the values of the assigned variables. Therefore we need a Variable struct.

*name* field keeps the name of the variable. *value* keeps is numerical value, and *next* points to the next Variable in the list. The variables are kept in a linked-list as opposed to array. Because we do not know the number of variables beforehand. Because linked-list don't have a fixed size, I used it.
