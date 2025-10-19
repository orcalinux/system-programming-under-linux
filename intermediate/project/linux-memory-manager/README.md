# Linux Memory Manager

![Heap Memory Manager Architecture](docs/assets/images/heap.png)

A compact, production-oriented Heap Memory Manager (HMM) for Linux.
This project provides a custom allocator, a thread-safe intrusive linked
list implementation (GLThread), and comprehensive documentation and
tests to aid integration and development.

## Highlights

- High-performance, low-fragmentation heap allocator
- Intrusive, thread-safe linked-list primitives (GLThread)
- Comprehensive API and developer documentation (Doxygen)
- Test suite and build targets for static/shared libraries

## Quick start

Prerequisites: GCC, GNU Make, and (optionally) Doxygen.

Build everything:

```sh
make all
```

Build static library only:

```sh
make static
```

Run tests / example binary:

```sh
./bin/hmm
```

Generate HTML documentation:

```sh
make doc
# open docs/doxygen/html/index.html
```

## Documentation (quick links)

- User Guide: `docs/pages/user_guide.md`
- API Reference: `docs/pages/api_reference.md`
- Architecture Overview: `docs/pages/architecture.md`
- Developer Guide: `docs/pages/developer_guide.md`

## Project layout

```
linux-memory-manager/
├─ src/                # C implementation
├─ include/            # Public and internal headers
├─ docs/               # Markdown pages and assets
├─ bin/                # Example/test binaries
├─ lib/                # Built libraries
├─ Makefile            # Build system
└─ LICENSE
```

## Contributing

Contributions are welcome. Open an issue or submit a pull request with a
clear description and tests. Please follow the Doxygen formatting used
in the repository for any documentation changes.

## License

This project is licensed under MIT — see `LICENSE` for details.
