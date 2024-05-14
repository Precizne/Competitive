echo "<<-COMPILING->>";
case $1 in
   a)
      g++ -O1 -Wall -fuse-ld=lld -std=c++20 -fsanitize=address -fno-omit-frame-pointer main.cpp;;
   m)
      g++ -O1 -Wall -fuse-ld=lld -std=c++20 -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -fno-optimize-sibling-calls -g main.cpp;;
   t)
      g++ -O1 -Wall -fuse-ld=lld -std=c++20 -fsanitize=thread -fPIE -pie -g main.cpp;;
   l)
      g++ -O1 -Wall -fuse-ld=lld -std=c++20 -fsanitize=leak main.cpp;;
   u)
      g++ -O1 -Wall -fuse-ld=lld -std=c++20 -fsanitize=undefined main.cpp;;
   *)
      g++ -Ofast -Wall -fuse-ld=lld -std=c++20 main.cpp;;
esac
echo "<<-EXECUTING->>";
./a.out;
