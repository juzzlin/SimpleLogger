SimpleLogger
============

Looking for a simple logger for C++ ? SimpleLogger might be for you.

# Features

* Based on RAII
* Configurable level symbols
* Date / time
* Logging levels: Trace, Debug, Info, Warning, Error, Fatal
* Log to file and/or console
* Very easy to use

# Installation

Just add `src/logger.hpp` and `src/logger.cpp` to your project and start using it!

# Examples

## Log to console

```
using juzzlin::L;

L().info() << "Something happened";
```

Outputs something like this:

`[Sat Oct 13 22:38:42 2018] I: Something happened`

## Log to file and console

```
using juzzlin::L;

L::init("/tmp/myLog.txt");

L().info() << "Something happened";
```

## Log only to file

```
using juzzlin::L;

L::init("/tmp/myLog.txt");
L::enableEchoMode(false);

L().info() << "Something happened";
```

## Set logging level 

```
using juzzlin::L;

L::setLoggingLevel(L::Level::Debug);

L().info() << "Something happened";
L().debug() << "A debug thing happened";
```

Outputs something like this:

`[Sat Oct 13 22:38:42 2018] I: Something happened`

`[Sat Oct 13 22:38:42 2018] D: A debug thing happened`

## Set custom level symbols

```
using juzzlin::L;

L::setLoggingLevel(L::Level::Debug);
L::setLevelSymbol(L::Level::Debug, "<DEBUG>");

L().debug() << "A debug thing happened";
```

Outputs something like this:

`[Sat Oct 13 22:38:42 2018] <DEBUG> A debug thing happened`

## Requirements

C++11

## Licence

MIT
