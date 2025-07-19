```shell

python3 -m venv .env
source .env/bin/activate



cd core-cpp
mkdir build && cd build
cmake .. -DPYTHON_EXECUTABLE=$(which python)
```
