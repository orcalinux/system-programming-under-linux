# Doxygen Documentation Guide

@brief Guide for setting up and using Doxygen for project documentation.

## Introduction

This guide provides detailed instructions on how to set up and use Doxygen to generate professional and comprehensive documentation for your project.

> **📚 About Doxygen:** Doxygen is a powerful tool that can produce high-quality documentation from annotated C/C++ sources, making it a critical tool in any developer's toolkit.

---

## Installation

### Install Doxygen

To begin using Doxygen, install it on your system:

```bash
sudo apt-get install -y doxygen
```

### Install Graphviz (Optional)

If you plan to generate diagrams and charts, you will need Graphviz:

```bash
sudo apt-get install -y graphviz
```

> **✅ Verification:** After installation, verify with: `doxygen --version`

---

## Configuration Setup

### Generate Configuration File

Run the following command to create a `Doxyfile` configuration:

```bash
doxygen -g
```

This creates a default `Doxyfile` with all available options.

### Essential Configuration Options

| Option             | Value                 | Purpose                                |
| ------------------ | --------------------- | -------------------------------------- |
| `PROJECT_NAME`     | "My_Project"          | Name displayed in documentation        |
| `PROJECT_BRIEF`    | "Project description" | Short description shown on main page   |
| `INPUT`            | src include           | Directories to scan for source files   |
| `RECURSIVE`        | YES                   | Recursively search input directories   |
| `OUTPUT_DIRECTORY` | docs/output           | Where to place generated documentation |

### C Language Optimization

For C projects, add these settings:

```bash
# Optimize output for C
OPTIMIZE_OUTPUT_FOR_C = YES

# Extract all documentation
EXTRACT_ALL = YES
EXTRACT_STATIC = YES
EXTRACT_PRIVATE = YES
```

> **💡 Tip:** `EXTRACT_ALL = YES` generates documentation even for undocumented code.

### Source Code Browser

Enable source code browsing:

```bash
# Generate source browser
SOURCE_BROWSER = YES
INLINE_SOURCES = YES
STRIP_CODE_COMMENTS = NO
```

> **SOURCE_BROWSER = YES**  
> Generates hyperlinked source code  
> ↓  
> **INLINE_SOURCES = YES**  
> Includes source code in documentation  
> ↓  
> **STRIP_CODE_COMMENTS = NO**  
> Preserves comments in code listings

### Graphviz Integration

Enable diagram generation:

```bash
# Enable Graphviz for generating diagrams
HAVE_DOT = YES
DOT_NUM_THREADS = 4

# Generate call graphs and caller graphs
CALL_GRAPH = YES
CALLER_GRAPH = YES
CLASS_DIAGRAMS = YES
```

- **📊 CALL_GRAPH**  
  Shows which functions a given function calls
- **📈 CALLER_GRAPH**  
  Shows which functions call a given function
- **🏗️ CLASS_DIAGRAMS**  
  Generates inheritance and collaboration diagrams

### Output Formats

Configure output formats:

```bash
# HTML output
GENERATE_HTML = YES
HTML_OUTPUT = html

# LaTeX/PDF output
GENERATE_LATEX = YES
LATEX_OUTPUT = latex

# Man pages
GENERATE_MAN = NO
```

---

## Running Doxygen

### Basic Usage

After configuring the `Doxyfile`, generate your documentation:

```bash
doxygen Doxyfile
```

> **✅ Output Location:** Generated files will be in `OUTPUT_DIRECTORY/html/index.html`

### Makefile Integration

Add a documentation target to your Makefile:

```makefile
.PHONY: doc clean_doc

doc:
    doxygen Doxyfile
    @echo "Documentation generated in html/"

clean_doc:
    rm -rf html/ latex/ man/

all: build doc
```

- `make doc` — Generate documentation
- `make clean_doc` — Remove generated files
- `make all` — Build project and documentation

---

## Advanced Features

### Setting Up the Main Page

Use a markdown file as your main page:

**1. Create README.md:**

```markdown
@mainpage Linux Memory Manager

@section intro_sec Introduction
This is the main documentation page...

@section install_sec Installation
Instructions for building...
```

**2. Configure Doxyfile:**

```bash
USE_MDFILE_AS_MAINPAGE = README.md
```

### Creating Documentation Pages

Create separate pages using `@page` directive:

```c
/**
 * @page user_guide User Guide
 *
 * @tableofcontents
 *
 * @section usage_sec Usage
 *
 * This page explains how to use the library...
 *
 * @subsection install_subsec Installation
 *
 * Steps to install:
 * 1. Clone repository
 * 2. Run make
 * 3. Install library
 */
```

> **💡 Navigation:** Use `@ref` to link between pages: `@ref user_guide "User Guide"`

### Documentation Comments

Doxygen recognizes several comment styles:

| Style        | Example       | Use Case                   |
| ------------ | ------------- | -------------------------- |
| JavaDoc (C)  | `/** ... */`  | Functions, structs, files  |
| Qt Style     | `/*! ... */`  | Alternative to JavaDoc     |
| Single Line  | `/// comment` | Brief inline documentation |
| After Member | `/**< ... */` | Document struct members    |

### Common Doxygen Tags

- **@brief**  
  Brief description (one line)
- **@param**  
  Document function parameters
- **@return**  
  Document return value
- **@code...@endcode**  
  Include code examples
- **@note**  
  Add important notes
- **@warning**  
  Highlight warnings

**Example:**

```c
/**
 * @brief Allocates memory for a data structure.
 *
 * @param count Number of elements to allocate
 * @param type Type of structure to allocate
 * @return Pointer to allocated memory, or NULL on failure
 *
 * @note The returned memory is zero-initialized.
 * @warning Must be freed with XFREE() to avoid memory leaks.
 *
 * @code{.c}
 * Employee *e = XCALLOC(1, Employee);
 * if (e) {
 *     strcpy(e->name, "John");
 *     XFREE(e);
 * }
 * @endcode
 */
void* XCALLOC(size_t count, size_t size);
```

---

## Customizing with Themes

### Doxygen-Awesome Theme

Install modern CSS theme for better appearance:

**1. Install theme:**

```bash
cd docs
git clone https://github.com/jothepro/doxygen-awesome-css.git theme/doxygen-awesome
```

**2. Configure Doxyfile:**

```bash
GENERATE_TREEVIEW = YES
HTML_EXTRA_STYLESHEET = docs/theme/doxygen-awesome/doxygen-awesome.css
HTML_COLORSTYLE = TOGGLE
```

**3. Add custom header (optional):**

```bash
HTML_HEADER = docs/header.html
```

> **✅ Features:**
>
> - Dark mode toggle
> - Copy code buttons
> - Responsive design
> - Interactive table of contents---

## Troubleshooting

> **⚠️ Common Issues:**  
> **Problem:** No documentation generated  
> **Solution:** Check `INPUT` paths are correct and `RECURSIVE = YES`  
> **Problem:** Graphviz diagrams not showing  
> **Solution:** Install Graphviz and set `HAVE_DOT = YES`  
> **Problem:** Theme files not loading  
> **Solution:** Verify `HTML_EXTRA_STYLESHEET` path is relative to Doxyfile  
> **Problem:** Main page not showing  
> **Solution:** Ensure `USE_MDFILE_AS_MAINPAGE` points to correct file

---

## Best Practices

- **📝 Document as You Code**  
  Write documentation comments while writing code, not after
- **🎯 Be Concise**  
  Keep @brief descriptions to one line, expand in full description
- **💡 Use Examples**  
  Include code blocks with practical usage examples
- **🔗 Cross-Reference**  
  Use @ref, @see, @sa to link related documentation
- **⚠️ Highlight Warnings**  
  Use @warning, @note, @attention for important information
- **🔄 Keep Updated**  
  Update documentation when changing code behavior

---

## Related Documentation

- [Developer Guide](developer_guide.md) - Contributing to documentation
- [User Guide](user_guide.md) - Using the documented library
- [API Reference](api_reference.md) - Generated API documentation
