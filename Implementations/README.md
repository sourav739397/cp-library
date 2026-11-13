This directory contains the source code and build configuration for generating the ICPC-style contest reference document, inspired by [KACTL](https://github.com/kth-competitive-programming/kactl).

The notebook is a concise collection of reusable, copy-paste-ready C++ implementations of algorithms and data structures, designed for ICPC-style programming competitions.

# Build Your Notebook

## Requirements

- A working LaTeX distribution with `pdflatex`.
- Python 3.
- GNU Make.

## Quick Start

Run the following commands from the `Implementations/` directory:

```
# Fast build: generate a quick preview
make fast

# Full build: generate the complete notebook with table of contents
make kactl

# Remove generated build files
make clean
```

After a successful build, the generated PDF will be available as `kactl.pdf`.

---

## Adding a New Algorithm

Follow these three steps to include a new implementation in your notebook.

### 1. Create the Header File

Place your implementation inside the appropriate category directory under `content/`.

For example:

```
content/
└── data-structures/
    ├── chapter.tex
    ├── SegmentTree.h
    └── ...
```

Keep implementations concise, self-contained, and contest-ready. Each file should begin with a short documentation block describing its purpose, complexity, source etc.

**Example:**

```
/**
 * Description: Short explanation of the implementation.
 * Time: O(N log N)
 * Source: 
 * Verification: CSES / Codeforces / Yosupo
 */

// Implementation goes here
```

### 2. Register It in `chapter.tex`

Open the `chapter.tex` file in the corresponding category directory and add an import statement for your new header.

For example, in `content/data-structures/chapter.tex`:

```
\kactlimport{SegmentTree.h}
```

This ensures that your implementation is included in the generated notebook.

### 3. Build and Verify

From the `Implementations/` directory, run:

```
make fast
```

Open the generated PDF and verify that your implementation is formatted correctly and appears in the expected section.

Once everything looks good, generate the complete notebook:

```
make kactl
```

That's it! Your new algorithm is now part of the reference notebook.

---
