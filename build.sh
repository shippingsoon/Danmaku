clear

if [ -a "bin/Danmaku x64" ]
	then
		#echo "Removing file"
		rm "bin/Danmaku x64"
fi

g++ -std=c++0x -o "bin/Danmaku x64" "src/"*.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

if [ -a "bin/Danmaku x64" ]
	then
		#echo "starting Danmaku"
		./bin/Danmaku\ x64
fi

#valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./bin/Danmaku\ x64
