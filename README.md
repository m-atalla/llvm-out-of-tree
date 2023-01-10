

## Requirements
- LLVM v15
- CMake
- Ninja

```bash
$ cmake -B build/ -S ./ -GNinja \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_PREFIX_PATH=<path/to/llvm/build>

$ ninja -C build/

# add option `-disable-output` if needed.
$ <path/to/opt/bin> -load-pass-plugin <path/to/dynamic/lib> -passes="<LOADED_PASS_NAME>" <INPUT_IR_FILE>
```
