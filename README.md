# CP Library

A curated collection of algorithms for Codeforces and onsite contests (ICPC, IUPC), featuring a powerful bash script that automates problem fetching, solution testing, and stress testing.

## Features
- Fast, contest-ready algorithm implementations
- Bash script for problem fetch, test, stress test workflow
- Algorithms from KACTL, Benjamin Qi's notebook, and CPH
- Tested on Codeforces, CSES, AtCoder, and Kattis

## Overview
```
content/
├── contest/            # Contest templates and macros
├── math/               # Basic math utilities
├── data-structures/    # Segment Tree, Fenwick, Sparse Table
├── number-theory/      # Primes, Sieve, Modular arithmetic
├── combinatorial/      # Combinatorics, Permutations
├── numerical/          # Numerical methods, Precision handling
├── graph/              # Dijkstra, MST, Flow, LCA, SCC
├── geometry/           # Convex Hull, Line Intersection
├── strings/            # KMP, Z-algo, Suffix Array, Hashing
├── various/            # DP tricks, other useful stuff
├── test-session/       # LaTeX source for test session PDF
└── tex/                # LaTeX source for 25-page reference PDF
run.sh                  # Automation script for fetch, test, and stress testing
Makefile                # Build script for generating PDFs
kactl.pdf               # Generated 25-page algorithm reference
test-session.pdf        # Generated test session PDF
```

## Automation Script (run.sh)

The bash script handles:
- **Fetch** - Fetch test cases
- **Test** - Run against samples
- **Stress** - Compare with brute force using random tests

For more info, check out the [Codeforces blog](https://codeforces.com/blog/entry/142978) and [GitHub repo](https://github.com/sourav739397/Competitive-Programming-Automation).


## Sources

This library is built from:
- [KACTL](https://github.com/kth-competitive-programming/kactl) - KTH's ICPC reference
- [Benjamin Qi's CP Notebook](https://github.com/bqi343/cp-notebook)
- [Competitive Programmer's Handbook](https://cses.fi/book/) (CPH)


## From KACTL

This repo hosts KACTL, KTH's ICPC team reference document. It consists of 25 pages of copy-pasteable code, for use in ICPC-style programming competitions.

See **kactl.pdf** for the final, browsable version, and **content/** for raw source code.

### Aspirations

KACTL algorithms should be: useful, short, fast enough, readable, and if relevant, easy to modify. Short and readable sometimes conflict -- usually then short takes precedence, although the algorithms should still be made easy to type in and hard to make typos in (since ICPC-style contests require you to copy them from paper).

They should not be overly generic, since code is manually typed and that just adds overhead. Due to space issues, we also exclude algorithms that are very common/simple (e.g., Dijkstra), or very uncommon (general weighted matching).

If you feel that something is missing, could be cleaned up, or notice a bug, please file an issue or send us a pull request!

### Hacking on KACTL

For coding style, try to copy existing code. Each algorithm should contain a header with the author of the code, the date it was added, a description of the algorithm, its testing status, and preferably also source, license and time complexity. Line width is 63 chars, with tabs for indentation (tab = 2 spaces in the pdf).

When adding/removing files, edit the corresponding `chapter.tex` file as well. `chapter.tex` also contains all non-source code, e.g. math and textual descriptions. For nicer alignment you might want to use `\hardcolumnbreak`, `\columnbreak` or `\newpage` commands, though this is usually only done before important contests, and not on master.

To build KACTL, type `make kactl` (or `make fast`) on a *NIX machine -- this will update `kactl.pdf`. (Windows might work as well, but is not tested.) `doc/README` has a few more notes about this.

kactl.pdf is to be kept to 25 pages + cover page. Occasionally the generated kactl.pdf is committed to the repo for convenience, but not too often because it makes git operations slower.

Before printing KACTL for an official contest, you may want to locally change the arguments to `\team`, `\contest`, etc. in build/kactl.tex to something more fitting. You may also enable colored syntax highlighting in the same file.


## Contributing

Found a bug or want to add something? Open an issue or PR!

## License

As usual for competitive programming, the licensing situation is a bit unclear. Many source files are marked with license (we try to go with **CC0**), but many also aren't. Presumably good will is to be assumed from other authors, though, and in many cases permission should not be needed since the code is not distributed. To help trace things back, sources and authors are noted in source files.

## Author

**Sourav** - [@sourav739397](https://github.com/sourav739397)

Codeforces: [-739397](https://codeforces.com/profile/-739397)

---

⭐ Star this repo if it helps you in contests!