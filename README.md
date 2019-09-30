# Sudoku
General sudoku solver.

## General?
Usually by sudoku the first thing considered is typical 9x9 grid, with rules about numbers 1 to 9 appearing exactly once in
each row, column and 3x3 box. However, that is not where the story ends and seeing multiple sudoku solvers until now, I decided
to make a general one, that would not be constrained only on 9x9 with the standard rule set.

## How it all works (Idea)?

### Allowed

In `Sudoku.h` and `Sudoku.cpp` there is a matrix of lists, called `allowed`. `allowed[x][y]` represents list of numbers that
are possible to go in row `x` and column `y`. So for empty 9x9 sudoku, each of these lists will contain numbers 1-9. Once
we know that a field contains some number `v`, field is no longer empty, and information that `v` is in it, is passed to `Rules`
to determine the updates within `allowed`.

### IRules
IRules represent abstract class that captures idea behind the "rules". Idea of `IRules` and `Rules` are that they represent a link
between multiple fields. For example, in regular 9x9 sudoku, if there is a number 3 in the first row, we for a fact know that 
number 3 will not appear in the first row no more -- thus it can be seen that there exists a link between all the fields of the
first row. This link is captured by the `Rules`.

Common such rules that I have derived are `RowRules`, `ColumnRules` and `BoxRules` that portray the obvious connections
between fields. The significant method common to all rules is `applyOn` that takes 4 parameters:
- Information about the latest edited field (row, column)
- Entry that resides in that field
- Pointer to `allowed`
- Reference to list `q`

Thus, each rule will based on first 2 parameters and some inner data (links between fields specific to a rule), clear `allowed`
appropriately. List `q` represents list of field that are point of interest. Field in row `x` and `y` becomes
"point of interest" once `allowed[x][y]` is a list containing one number (i.e. it is possible to enter only one value
in the field without contradicting previous assumptions), so essentially putting that field in `q` is like booking
an appointment for the field to be officially filled with a value.

### Strategy using point-of-interest
With the two concepts explained above, explaining solving strategy is easy. At start, fill in all the values given by the
sudoku game (unless "solving" empty sudoku). While list `q` is not empty, there are fields that "want" to register number
inside them. Once "officially" filled, that field is taken out of the `q` (`q` behaves like a queue). Repeat that until sudoku
is solved.

### Strategy using splitting
Of course, at one point `q` may become empty, but there are still fields that have not inferred what numbers they hold.
In that case, find the "easiest" field -- that is, a field that is still empty but has least candidates for numbers in it
(if there are more than one such, pick any).

For that easiest field, that has `c` candidates, make `c`-1 copies of the sudoku; with `c` identical sudoku tables
try each possible candidate using mechanisms described earlier.

This approach allows mutliple solutions to be discovered.
