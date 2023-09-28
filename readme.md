# triangles
- This program helps to find intersection of triangles in 3D

## Required programs:

-  Cmake version  3.21


# Install and run
```
> git clone git@github.com:MaxGroshev/triangles.git
> mkdir build
> cd build
> cmake ..
> make
> ./src/triangles

```

# Tests
Required programs:

- Python
- Google tests


#### How to run unit tests?
```
> make tests
> ./tests/unit_tests
```
---

#### How to run end to end tests?
```
> python ./tests/end_to_end_tests/e2e_test.py

```
---

#### How to run debug mode?
- go to  ./CMakeLists.txt
- change CMAKE_BUILD_TYPE "Release" to "Debug"


---
