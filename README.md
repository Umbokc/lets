# Lets

Lets is the new interpreted scripting language for quick and easy programming.

## License

MIT - see [MIT licence information](LICENSE)

## Building and testing

The project uses a simple `Makefile` for building the interpreter and running the
unit test suite.

```
make            # builds the interpreter into bin/lets
make test       # builds and runs the doctest-based test suite in tests/
make clean      # removes build artefacts and test binaries
```

The tests currently focus on regression coverage for the dynamic array
implementation and guard against past memory issues discovered during resizing.

