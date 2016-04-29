To benchmark to QGCodeEditor widget with a ```gcode.ngc``` G-Code file, run:

```bash
$ time -p bash -c '< gcode.ngc  | ./pipe '
```

Example: measure runtime of QGCodeEditor widget with a 1000 lines G-Code file:

```bash
$ time -p bash -c 'cat <(ngc-urandom.sh 1000) | ./pipe '
real 2.94
user 2.72
sys 0.10
```

where ```ngc-urandom.sh``` is:

```bash
#!/usr/bin/env bash

N=$1; echo "F100"; cat /dev/urandom | hexdump -v -e '/1 "%u\n"' | paste - - -  | awk '{ print "G1 X"$1" Y"$2" Z"$3 }'|head -n $N; echo "M30"
```

