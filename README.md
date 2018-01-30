# si2cce
SIGINT to Console Ctrl Event

## Description

Small tool to help with running interactive CLI Windows programs in Cygwin.  
Windows CLI programs like cdb.exe install [control handler functions](https://docs.microsoft.com/en-us/windows/console/registering-a-control-handler-function) to handle Ctrl-C event.  
However, when running though Cygwin and OpenSSH, Ctrl-C generates SIGINT which just kills cdb.exe process thus interrupting desired workflow.  
This programm install SIGINT handler and sends ConsoleCtrlEvent to child process instead.

## Build & Install
Cygwin with gcc & make is required

```
make
make install
```

## Usage

```
si2cce.exe <program name> [program arguments]
```

## License
GNU GPLv3
