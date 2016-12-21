**Status**

[![Build Status](https://travis-ci.org/fpersson/logtool.svg?branch=master)](https://travis-ci.org/fpersson/logtool)

**About**

A better way debug your software.

Support:
* Android logcat
* rs232 (expermintal)
* tail

**Configuration:**

Create your config files in $HOME/log_profiles
 
Files to create:
* keys, contains a list of keywords to highlight (separated with newline)
* profile, contains a list of keywords to exclude (separated with newline)

Make sure your path to adb is in your $PATH

**Usage:**
```
Usage: logtool [options]
LogTool, A better way debug your software.

Options:
  -h, --help                         Displays this help.
  -v, --version                      Displays version information.
  -l, --logdir <dir>                 set logdir (/foo/logdir).
  -p, --profile </path/to/profile>   set profile (/path/to/profile)
  -m, --mode <logcat | rs232 | cmd>  set mode for logcat (default) or rs232
  -c, --cmd <path to log>            your own command (tail -f /path/to/log)
   ```
**Requirement**

QT 5.5 or later.

**Build:**
* mkdir ./build
* cd build
* cmake ..
* cd ..
* make -C build/

**TODO:**
* Rewrite the "profile"
* Better documentation.