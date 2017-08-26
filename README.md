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
  -s, --set <setting files to use>   use <settings>.ini
   ```

**Example with inifile**
```
./build/logtool -s ~/log_profiles/foo.ini
```

**.ini file example**
```
[System]
logdir="/home/fredrik/logtool/log"
mode="logcat"
cmd=""
blacklist="/home/fredrik/log_profiles/foo"
```
* logdir is absolute path to your logdir (log file is /messages)
* mode valid mode is logcat | rs232 | cmd
* cmd is optional and only needed when mode=cmd.
* blacklist is a file containing blacklisted keyword, debug messages with keywords will be removed and never displayed. This is same thing as profile. 

**Example with arguments**
```
./build/logtool -m logcat -p ~/log_profiles/foo
```
Where foo is a plain text file containing a list black listed keywords. 

**Requirement**

QT 5.5 or later.

**Build:**
* mkdir ./build
* cd build
* cmake .. or cmake ../ -DCMAKE_PREFIX_PATH=/path_to/Qt/5.7/gcc_64/
* cd ..
* make -C build/

**TODO:**
* Rewrite the "profile" (WIP)
* Better documentation.