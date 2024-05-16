# Background Study for Particle Physics
Documentation of theoretical background for particle physics including linear and **abstract algebra** with manifolds, topology, and group theory.

# Compiling Documentation
The documentation is done completely using LaTeX, so you will require a pdfLaTeX compiler. For that you can use [overleaf](https://www.overleaf.com/), [TeXstudio](https://www.texstudio.org/#download), [Visual Studio Code](https://code.visualstudio.com/), or any other platform supporting pdfLaTeX compiler. For manual set up in Linux follow these steps:

## Dependencies
If you want to build the documentation manually selecting the compiler then install the dependencies as:
```
    sudo apt-get install texlive
    sudo apt-get install latexmk
    sudo apt-get install texlive-fonts-extra
    sudo apt-get install texlive-bibtex-extra
    sudo apt-get install biber
``` 

## Build Instructions
To build the Latex document, simply run make at the root directory.

Alternatively, you can build the document with VS Code. If you plan on using minted files then to avoid compilation error with minted files either build the documentation with `-shell-escape` flag or edit `settings.json`: in `args` key of `latex-workshop.latex.tools` add `-shell-escape` value. Then, you will be able to build simply with Ctrl+S.