libcmdf.h
=============
A simple library for writing command-line applications, inspired by Python's [cmd](https://docs.python.org/3/library/cmd.html) module.

----------------------------------------------

***Latest version: v.1.1 (2019-07-01)***

----------------------------------------------

Features
--------
1. Written using 100% ANSI C
2. Header only: no linkage! No separate compilation!
3. Cross-platform
4. GNU Readline support
5. Can be used from C++ (without `-fpermissive`)

Requirements
------------
1. **Any ANSI C/ISO C90-compliant compiler**
<br />*Tested on GCC 5.4/6.3/7.1, clang 4.0 and MSVC 14.0*
2. **Linux/Windows**
<br />*Tested on Ubuntu 16.04 - 18.04, Fedora 26 - 30, and Windows 10 (all AMD64)*
3. **GNU Readline development libraries (optional)**
<br />*Required for GNU Readline support, if enabled.*

Usage
------
Being a header-only library, you don't need to do any complex linkage - just drop it in your project tree and you're done!

You will, however, need to define <code>LIBCMDF_IMPL</code> **only once**, and **before you include the library**, like this:

```
#define LIBCMDF_IMPL
#include <libcmdf.h>

...
```

API in a nutshell
--------------------
First of all, you must initialize libcmdf by calling either `cmdf_init_quick()` or `cmdf_init`:
```
void cmdf_init(const char *prompt, const char *intro, const char *doc_header,
               const char *undoc_header, char ruler, int use_default_exit);
#define cmdf_init_quick() cmdf_init(NULL, NULL, NULL, NULL, 0, 1)
```

The two most important parameters are the prompt and the intro:

**<code>prompt</code>** - The prompt for every command. <br />
**<code>intro</code>** - A text that is displayed to the user on program startup. <br />

After initialization is done, you must then register some **command callbacks**.
A command callback has a **command name** associated with it, and that can be executed
by the user, which in turn will execute the associated command callback.

The command callback has the following format:
```
typedef CMDF_RETURN (* cmdf_command_callback)(cmdf_arglist *arglist);
```

<code>CMDF_RETURN</code> is a <code>typedef</code>d integer specifying a return code.
<code>arglist</code> is a pointer to the arguments passed by the user along with the command,
which libcmdf transperantly handles behind the scenes. It is destroyed by libcmdf when the command callback
returns.

This simple structure contains two elements:
```
/* libcmdf command list and arglist */
typedef struct cmdf___arglist_s {
     char **args;                /* NULL-terminated string list */
     size_t count;               /* Argument list count */
} cmdf_arglist;

```

This way you can quickly iterate the command-line arguments and act accordingly.

After you have your command callback, simply register it using `cmdf_register_command`:
```
CMDF_RETURN cmdf_register_command(cmdf_command_callback callback, const char *cmdname,
                                  const char *help);
```

Note that you may provide an optional help message. If you do, the user will be able to see it when and if
he will request it using the `help` command.

After that, initialization of the library is pretty much complete, so you can just call the main command loop:
```
cmdf_commandloop();
```

In any case you may refer to <code>test.c</code> for a working example.


Configuration
---------------
The library can be configured by <code>#define</code>ing any of the following definitions **only once, before including the library**:
<br />

|Definition|Description|Default|
|----------|-----------|-------|
|<code>CMDF_MAX_COMMANDS</code>|Maxmium amount of allowed commands.|24|
|<code>CMDF_TAB_TO_SPACES</code>|If a tab is encountered in a command's help string, expand it to N spaces.|8|
|<code>CMDF_READLINE_SUPPORT</code>|Enable/disable GNU readline support (Linux only, requires readline development libraries)|(*Disabled*)|
|<code>CMDF_FGETS</code>|A <code>fgets()</code>-like function, to be used for command-line input.|<code>fgets()</code>|
|<code>CMDF_MALLOC</code>|A <code>malloc()</code>-like function, to be used for memory allocations<sup>1</sup>.|<code>malloc()</code>|
|<code>CMDF_FREE</code>|A <code>free()</code>-like function, to be used for memory deallocations<sup>1</sup>.|<code>free()</code>|
|<code>CMDF_MAX_INPUT_BUFFER_LENGTH</code>|The maximum length of the input buffer used to get user input<sup>1</sup>.|256|
|<code>CMDF_STDOUT</code>|A <code>FILE *</code> to be used as standard output.|<code>stdout</code>|
|<code>CMDF_STDIN</code>|A <code>FILE *</code> to be used as standard input.|<code>stdin</code>|

<sup>1</sup> Note: GNU Readline will **not** use any custom memory allocation functions, but rather the standard library's <code>malloc</code> and </code>free</code>. Also, you may have to provide additional linker flags to link against readline.

To configure libcmdf simply define any configuration definitions **once and before <code>LIBCMDF_IMPL</code>**, like so:
```
#define CMDF_READLINE_SUPPORT   /* Enable readline support */
#define LIBCMDF_IMPL
#include <libcmdf.h>

...
```

Feedback
---------
I tested the library to the best of my abilities, but there might still be some bugs. <br />
If you do find them, please contact me or open an issue!

FAQ
----
### Is the library thread-safe?
No, but it's just handling user input for CLI, so I honestly don't think it should be.

### Why is <code>cmdf_quit</code> not implemented?
At the moment, the initialization routines don't allocate any memory, or perform any weird
initialization tricks that require deinitalization.

This might change in the future, though, so make sure to call <code>cmdf_quit</code> when you're done with it!

-------------------------------------------------------------------------------------------------------

License
--------
This software is dual-licensed to the public domain and under the following license:
you are granted a perpetual, irrevocable license to copy, modify,
publish and distribute this file as you see fit.
