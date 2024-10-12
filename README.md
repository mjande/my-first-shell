#My First Shell
===============

My First Shell is a basic shell program focused on implementing many of the most common features found in shell programs like Bash.

The provided makefile can be used to build the project:

```sh
   $ make          # Equivalent to `make all`
   $ make all      # Equivalent to `make release debug` (default target)
   $ make release  # Release build in release/ -- no debugging messages
   $ make debug    # Debug build in debug/ -- includes assertions and debugging messages
   $ make clean    # Removes build files (release/ and debug/ directories)
```
