echo "Deleting previous build files..."
rm -rf ./Dinner_Checker.egg-info
rm -rf ./dist
rm -rf ./build
rm dinnerchecker.cpython*
echo "Compiling..."
python3 setup.py build_ext --inplace
echo "Installing..."
python3 setup.py install
