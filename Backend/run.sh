OUTPUT=server

echo "Compiling..."

if ! g++ -std=c++17 \
    -I src \
    -I src/Controllers \
    -I src/Routes \
    -I src/Objects \
    $(find src -name "*.cpp") \
    -o "$OUTPUT"
then
    echo "[Error] The server was not compiled"
    exit 1
fi

echo "The server was compiled successfully"
./"$OUTPUT"