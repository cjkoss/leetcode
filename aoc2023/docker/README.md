from current dir

```
docker build -t aoc:local -f Dockerfile_<lang> .
```

run
```
docker run -it --rm -v $(pwd)/../..:/repo aoc:local
```

inside container
```
cd /repo
```

