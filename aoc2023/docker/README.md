from current dir

```
docker build -t aoc:local .
```

run
```
docker run -it --rm -v $(pwd)/../..:/repo aoc:local
```

inside container
```
cd /repo
```

