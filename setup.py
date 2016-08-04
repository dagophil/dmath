from distutils.core import setup
import sys

from Cython.Build import cythonize

ext = cythonize("src/dmath.pyx",
                compiler_directives={
                    "boundscheck": False,
                    "wraparound": False,
                    "nonecheck": False,
                    "cdivision": True
                },
                language="c++")

if not sys.platform.startswith("win"):
    ext[0].extra_compile_args = ["-O3", "-std=c++11"]
    ext[0].extra_link_args = ["-O3"]

setup(
    name="dmath",
    packages=["dmath"],
    ext_modules=ext
)
