```shell
cd python/
python3 -m venv .env
source .env/bin/activate
pip install flatbuffers numpy
rm -rf Mentis
flatc --cpp --python --gen-all graph.fbs
cp graph_generated.h ../core-cpp/include/


cd core-cpp
mkdir build && cd build
cmake .. -DPYTHON_EXECUTABLE=$(which python)
```
