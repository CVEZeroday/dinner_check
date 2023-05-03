from distutils.core import setup, Extension

setup(
    name="Dinner Checker",
    version="0.1",
    description="C",
    author="CVE Zeroday (T.Y.Kim)",
    author_email="",
    ext_modules=[
        Extension(
            "dinnerchecker",
            ["./py.cc", "./jsoncpp.cpp"],
            include_dirs=["."],
        )
    ],
    python_requiers=">=2.8",
    include_package_data=True,
    classifiers=[
        "Programming Language :: Python :: 3",
        "Operating System :: OS Independent",
    ],
    zip_safe=False,
)
