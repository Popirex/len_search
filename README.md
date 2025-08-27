# len_search

`len_search` is a small command-line tool written in **C** that analyzes a project or folder and provides information about its "real" size. Specifically, the program calculates:

- 📂 **Total number of files** in the folder (recursively)  
- 📏 **Total number of lines** across all regular files  
- 🔡 **Total number of characters** (excluding spaces, tabs, and newlines)  

It is designed for anyone who wants a quick overview of a project's size without opening each file manually.

---

## Features

- Recursively scans all subfolders  
- Ignores hidden files and directories (those starting with `.`)  
- Counts only regular files  
- Prints a message every time it opens a folder or file, useful to monitor the analysis  
- Ignores most common image file extensions.

---

## Help

    If you still struggle to use it, I added a "help command", here you can see it:
    ```bash

    ./len_search -h

    OR

    ./len_search --help

    ```

---

## How to Compile

If you want to compile from source:

```bash

gcc -o len_search main.c

```

This will create an executable called len_search.

If you don't use the -o len_search when compiling you'll have a a.out executable.

The repository already includes a compiled executable, so you can skip this step if desired.

---

## How to Use len_search
The executable takes as an argument the path of the folder to analyze.

```bash

./len_search <path_to_folder>

```

- Example

```bash

./len_search /home/user/project

```
OR

```bash

./len_search ~/project

```


Sample output:

```bash

Opening folder: project
Opening file: main.c
Opening folder: src
Opening file: helper.c

Folder: /home/user/project
Total files: 5
Total Lines: 230
Total characters: 4520

```

-Shows each folder and file opened

-Then prints a summary with the total number of files, lines, and characters.

---

## Notes

- Works on Linux/macOS (requires <dirent.h>).

- Character count excludes spaces, tabs, and newlines to provide a more "accurate" measure of actual code.

- Hidden files (like .git, .vscode) are ignored.

---

## Used libraries

```bash
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
```

---

## Creator Note
- This project was created because I always wonder how big some of my projects are but I'm always too lazy to check each file on it's own, if you have any ideas to make it better, I would love to hear them :)