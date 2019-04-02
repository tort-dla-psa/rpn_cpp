# rpn_cpp

Reverse poland notation calculator

## how to build

To build it from src use command:

```bash
	g++ calc.cpp -O2 -s -o calc
```

## how to use

Run it as a binary in your terminal, then type in something like that:

```
	1+2/4*3.5^-1
```

Calculator will translate it to this form:

```
	1+2/4*3.5^(0-1)
```

And then it'll translate it to RPN ("|" is a separator between numbers):

```
	1|2|4|/3.5|0|1|-^*+
```

And then finally it'll calculate and tell you result. Enjoy :)

To exit safely type "q". If you are a bad boy (or girl) then type some gibberish and calulator will serfolt, lol.
