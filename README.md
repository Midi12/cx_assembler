# cx_assembler

A c++20 constexpr x86 assembler

## Purpose

* Learning x86 assembly encoding in a practical and fun way
* Having an easy framework to generate assembly instruction at compile time

## Practical examples

See `examples` folder.

## Want to add instruction ?

1. Add it to the instruction db file (to the `instdb`, `prefix_db` and `prefix_0fdb` arrays)
2. Code the encoder in `encoder.hpp` or add it to an existing encoder if applicable.
3. Add a test file =)

## Supported instructions ?

No extension set is currently being supported, only a subset of x86 instructions is currently being implemented.
SIB (Scale Index Base) byte is not fully implemented yet

## TODOs ?

- Implement jcc and jmp instructions

## Credits

- [Godbolt](https://godbolt.org/) for prototyping
- Intel x86-64 [manual](https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-instruction-set-reference-manual-325383.pdf)
- [Defuse.ca](https://defuse.ca/online-x86-assembler.htm#disassembly) for verifying outputs
- [Geek ABC reference](http://ref.x86asm.net/geek-abc.html)
- People who answered my questions about c++20