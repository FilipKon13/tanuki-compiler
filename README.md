# tanuki-compiler

## Installation
Copy this repo using 

```
git clone -recurse-submodules https://github.com/FilipKon13/tanuki-compiler
```

You should be ready to compile using `make`.

Copy binaries in `out` folder to their destination.

Binary usage:
```
json2js input_file > output_file
```

```
tnk2js input_file > output_file
```

```
json2tnk input_file > output_file
```

```
tnk2json input_file > output_file
```

## Functions

- `load(url)` - loads given website
- `type(XPath, text)` - types text into the field with given XPath
- `click(XPath)` - clicks element with given XPath
- `clickTimes(XPath, times)` - click element given number of times
- `press(key)` - presses given key on the keyboard
- `waitFor(XPath)` - waits for element with given XPath
- `getText(XPath)` - gets text from element with given XPath
- `wait(miliseconds)` - waits given time in miliseconds
- `clickContaining(text)` - click element containing given text as substring
- `print(smth)` - prints `smth` to console as in `console.log`
- `native(string)` - inserts given string into resulting JS code as single line 1:1

## Loops
- `repeat(times) {...}` - repeats code inside given number of times 
- `for i of [1, 'a', 3 + 2] {...}` - substitutes `i` with elements from explicit array