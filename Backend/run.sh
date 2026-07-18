OUTPUT=server

echo "Compiling..."

if ! g++ -std=c++17 \
    -I src \
    $(find src -name "*.cpp") \
    -o "$OUTPUT"
then
    echo "[Error] The server was not compiled"
    exit 1
fi

echo "The server was compiled successfully"
./"$OUTPUT"