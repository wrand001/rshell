# rshell README

This rshell is meant to mimic bash. When executed, it will print a prompt and
allow you to use any command in /bin. 

# Known Bugs
* || does not stop the right side from executing when left executes
* && does not stop the right side from executing when left does not execute
* cd does not work
* does not recongize # when on the right of a command/agrument (i.e **ls#**, ls # is fine)
* exit only stops the script it's in. Cannot exit shell while running a script. just executing exit works fine.
