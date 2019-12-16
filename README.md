# SheSellsCShells :shell:

## Our Shell Features
In our shell, the user should be able to successfully input most bash
commands, with implementations of:
* flags -
* the semicolon ;
* redirection > and <
* double redirection >>
* pipe |

## Our Unsuccessful Features
We are not completely sure if our errno system works. For example, when a command is inputed that doesn't exist, the error returned is no such file or directory.

We also were unable to implement the guarantee of hair regrowth :worried:

## Bugs Bugs Bugs
Notes about errors:
* after an error occurs, it may take several tries to exit the shell

Other notes:
* using two redirections in the same 'direction' breaks the parser (ex: ls > ls > output)
* multiple pipes not implemented, only simple pipe
* putting in extra spaces between inputs doesn't work

:mushroom: Warning :mushroom:

Our parser can handle up to 9 different inputs, but no more than that!
That means that 'ls -a -b -c -d -e -f -g -h' works but 'ls -a -b -c -d -e -f -g -h -i' does not!


## Files & Functions
### shells.c
The file includes the functions ran by the shell to execute commands based on what is in the input.
```
char **parse_args()

Inputs: char *line
        int *length
        char *del
Returns: Array of the parsed line broken up by the delimiter
```

Parses the line using the delimiter and inputs the length of the array into the pointer given
Used to parse for semicolons and spaces. In addition, it "returns" the number of arguments by updating the value in ``*length``.

```
void changedir()

Inputs: char ** args
        int *length
```

Executes the 'cd' command using chdir(). If no input was given into the cd, then it will go to the home directory automatically.

```
int contains()

Inputs: char \**args
        int length
        char \*look
Returns: 1 if args contains look
         0 if args does not contain look
```

Given the length of args and the array itself, checks if the array contains look. It's mostly used for redirection purposes.

```
void redir_out()

Inputs: char **args
        int length
        int if_append
```

It sets up the '>' function or '>>' function, depending on the if_append parameter, which is 0 if you want to just do '>', 1 if you want to do '>>'. It replaces ``stdout`` with the file you want that is included in ``args``. In addition, it correctly places a ``NULL`` such that it is correctly inputed into ``execvp``.

```
void redir_in()

Inputs: char **args
        int length
```

Executes the '<' function. It replaces ``stdin`` with the file you want that is included in  ``args``. In addition, it correctly places a ``NULL`` such that it is correctly inputed into ``execvp``.

```
char *strip(char *line)

Inputs: char *line
Returns: the stripped line
```

Strips the front and end of the line of whitespace
Both returns the new line and directly changes the line, no need to run strip twice

### main.c
Main executor of the shell, calls function in shells.c as necessary based on the cases given.
```
int main()
```
Not much to say here... :ok_hand:
Responsible for checking to see which functions need to be called and forking and executing commands as necessary
