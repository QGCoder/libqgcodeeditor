To benchmark to QGCodeEditor widget with a ```gcode.ngc``` gcode file, run:

```bash
$ time -p bash -c '< gcode.ngc  | ./pipe '
```

Example: measure runtime of QGCodeEditor widget with a 1000 lines gcode file:

```bash
$ time -p bash -c 'cat <(./ngc-urandom.sh 1000) | ./pipe '
real 2.94
user 2.72
sys 0.10
```

