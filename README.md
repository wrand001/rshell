# rshell README

This rshell is meant to mimic bash. When executed, it will print a prompt and
allow you to use any command in /bin.

#install instructions
make
./bin/rshell 

#New features
* test ( [] ) command added: checks if a file or directory exists.
* precedence ( () ) command added: allows commands to be executed out of order.
* true command: always executes as true.
* false command: always executes as false.


# Fixed Bugs
* || now works!
* && now works!

# Known Bugs
* cd does not work
* does not recongize # when on the right of a command/agrument (i.e **ls#**, ls # is fine)
* exit only stops the script it's in. Cannot exit shell while running a script. just executing exit works fine.
* when the bracket is next to the flag, test command doesn't work ( i.e **[-e file]** )
* when there's just a - for flag, it assumes e
* multi flags for test [] don't work
* nested () does not work
