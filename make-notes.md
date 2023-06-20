Following section is collected from https://github.com/bagder/libcurl-video-tutorials/blob/master/setup/README.md

## Makefile

This is not really a make school but here's how the basic stuff in the file
works:

    CC = `curl-config --cc`

This sets the `CC` variable to hold the contents of what `curl-config --cc`
outputs. That's the name of the compiler that was used to build libcurl. Most
commonly this is plain `gcc`. We could possibly make it `CC = gcc` too.

    LIBS = `curl-config --libs`

This sets the `LIBS` variable to hold the contens of what `curl-config --libs`
outputs. That's a list of linker options necessary to link with libcurl on
this machine. Most commonly, this is `-lcurl`. We could also probably get away
with simply doing `LIBS = -lcurl`.

    mycurlapp: mycurlapp.o

This is the first rule of the makefile and thus the "default" one that will be
checked for a plain `make` invoke.

The *output* called `mycurlapp` depends on the files on the right side of the
colon. There's only one file there: `mycurlapp.o`. If the `.o` file is newer than
`mycurlapp`, then the following command will be executed:

    $(CC) -g -o $@ $< $(LIBS)

The CC variable (that is the compiler) is used and a command line is created
with a few options like `-g` and `-o`. `$@` is an automatic variable that
holds the name from the left side of the colon in the line above (`mycurlapp`),
`$<` holds the names on the ride side of the colon in the line above
(`mycurlapp.o`) and `$LIBS` is often just `-lcurl`.

In a typical machine, the command line that runs is thus something like:
`gcc -g -o mycurlapp mycurlapp.o -lcurl`.

    mycurlapp.o: mycurlapp.c

The object file depends on the C file. If the object file is missing or if the
C file is newer than the object file, run the following command:

    $(CC) -g -c $<

Again, `$<` holds the names on the ride side of the colon in the line above,
which one is `mycurlapp.c` which makes this run something like: `cc -g -c
mycurlapp.c`. The `-c` flag to gcc makes it produce the object file from the C
file.

    clean:
        rm -f mycurlapp.o mycurlapp

Here's a special target that lets us do `make clean` and then this command
line is run. Handy when we want to wipe previous build results and start over,
by force.

Following section is collected from https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables

## Automatic Variables

Suppose you are writing a pattern rule to compile a ‘.c’ file into a ‘.o’ file: how do you write the ‘cc’ command so that it operates on the right source file name? You cannot write the name in the recipe, because the name is different each time the implicit rule is applied.

What you do is use a special feature of make, the automatic variables. These variables have values computed afresh for each rule that is executed, based on the target and prerequisites of the rule. In this example, you would use ‘$@’ for the object file name and ‘$<’ for the source file name.

It’s very important that you recognize the limited scope in which automatic variable values are available: they only have values within the recipe. In particular, you cannot use them anywhere within the target list of a rule; they have no value there and will expand to the empty string. Also, they cannot be accessed directly within the prerequisite list of a rule. A common mistake is attempting to use $@ within the prerequisites list; this will not work. However, there is a special feature of GNU make, secondary expansion (see Secondary Expansion), which will allow automatic variable values to be used in prerequisite lists.

Here is a table of automatic variables: 

### $@

The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file. In a pattern rule that has multiple targets (see Introduction to Pattern Rules), ‘$@’ is the name of whichever target caused the rule’s recipe to be run.

### $%

The target member name, when the target is an archive member. See Using make to Update Archive Files. For example, if the target is foo.a(bar.o) then ‘$%’ is bar.o and ‘$@’ is foo.a. ‘$%’ is empty when the target is not an archive member.
### $<

The name of the first prerequisite. If the target got its recipe from an implicit rule, this will be the first prerequisite added by the implicit rule (see Using Implicit Rules).
### $?

The names of all the prerequisites that are newer than the target, with spaces between them. If the target does not exist, all prerequisites will be included. For prerequisites which are archive members, only the named member is used (see Using make to Update Archive Files).
‘$?’ is useful even in explicit rules when you wish to operate on only the prerequisites that have changed. For example, suppose that an archive named lib is supposed to contain copies of several object files. This rule copies just the changed object files into the archive:

    lib: foo.o bar.o lose.o win.o
            ar r lib $?
