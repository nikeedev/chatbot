clang++ src/main.cpp -Llib -lcurlpp -lcurl -o main

if [ $? -eq 0 ]; then
    ./main
else 
    echo "Oh no"
fi
