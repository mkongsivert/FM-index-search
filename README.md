# FM-index-search
An implementation of FM-index substring search
## Classes
### bit_vector
This class forms the basis for the first two parts of this assignment. I tried to make the most efficient use of space by storing the bitstring as an array of unsigned integers. Each of these unsigned integers takes up a byte, so I broke the bitstring into eight-bit chunks, converted them individually into decimal integers, and made a dynamic array out of them. This required frequent conversion between decimal and binary, since the code itself operates using decimal numbers. Since it is mainly meant to be used for storage, I didn't add many more capabilities to the structure. The ones I did add were mainly for displaying information, such as `size()` and `print()`, which respectively return the size of the string in bits and print the bitstring to the command line.
### rank_support
In contrast to `bit_vector`, this class is much more elaborate, but most of this is stored as member variables. In fact, the most elaborate function, and the hardest to write, was the constructor. I suppose that is the point of this structure; a lot of auxiliary information is stored as part of the structure itself so that the access functions have less work to do. In addition to the required functions, I wrote a `print()` function, which displays all the information saved in `save(std::string& fname)`, but sends it to the console instead.
### select_support
This is structured very similarly to the `rank_support` class, but it relies very heavily on the structure of `rank_support` and doesn't have a lot of structure of its own. The main contrast here is that in this class, most of the heavy lifting is done by functions, whereas in `bit_vector`, most of the heavy lifting was done by tables and other data stored in the structure itself.
### ichar
This is a class that I added to aid in keeping track of subscripts on letters. It is very simple and is just the combination of a character and an integer. I only implemented a parameterized constructor and the two member variables (the character and its subscript).
### FM_text
First, in the interest of saving time in programming, I made the assumption that the only strings that would be loaded into this class would only use the alphabet `['a', 'c', 'g', 't']`. Unlike the `rank_support` and `select_support` classes, there is a lot of work being done by both the structure itself and its member functions. However, the work being done by the member functions is mostly a lot of elaborate arithmetic and still seems to run in constant time. I timed both the `query(std::string pre)` function and the parameterized constructor with different input text lengths (but keeping the length of the queried text the same). The `query` function consistently took around 15 miliseconds, whereas the parameterized constructor's time increased proportionally with the size of the input text.

As you can see from the attached code, I implemented the BWT on my own because I couldn't really figure out how to use the recommended package. This took the longest by far, both in terms of runtime and in terms of the amount of work required for it. Other than those two functions, there isn't much worth mentioning about this implementation aside from a few not-particularly-interesting helper functions.
