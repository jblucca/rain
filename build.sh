#/bin/sh

# simple shell script for the lazy ones.

if [ ! -e udis86 ];
then
	echo "Building the udis86 library..."
	tar xvzf udis86-1.7.2.tar.gz
	cd udis86-1.7.2
	./configure --prefix=$(readlink -m ../udis86)
	make
	make install
	cd ..
fi

echo "Building rain..."
mkdir -p build
cd build
cmake ../
make

echo "Done."

