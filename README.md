# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Artificial long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

Get resource stadistic usage , like running time.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 members.
struct rusage {
    struct timeval ru_utime; /* user CPU time used */
    struct timeval ru_stime; /* system CPU time used */
    long   ru_maxrss;        /* maximum resident set size */
    long   ru_ixrss;         /* integral shared memory size */
    long   ru_idrss;         /* integral unshared data size */
    long   ru_isrss;         /* integral unshared stack size */
    long   ru_minflt;        /* page reclaims (soft page faults) */
    long   ru_majflt;        /* page faults (hard page faults) */
    long   ru_nswap;         /* swaps */
    long   ru_inblock;       /* block input operations */
    long   ru_oublock;       /* block output operations */
    long   ru_msgsnd;        /* IPC messages sent */
    long   ru_msgrcv;        /* IPC messages received */
    long   ru_nsignals;      /* signals received */
    long   ru_nvcsw;         /* voluntary context switches */
    long   ru_nivcsw;        /* involuntary context switches */
};

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because that way we pass their address and we have access to all their struct variables.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop will go over each character until obtain a word , when it reach EOF. It will take each character and
1) It going to check if "\'" isn't the first character of the word.
2) Each character will be stored until a word is created.
3) It will check if the word isn't bigger than 45 characters. If it's bigger than 45 characters,
4) It going to discard it and It goint to prepare for the next word.
5) It going to check if some characer in the word is a number. if It's the case, It going to discard it and It goint to prepare for the next word.
6) After all the checks, It finaly going to construct the word, with of course , the extra EOF ("\0").
7) The word is counted for the stadistics.
8) the word is checked if there isn't misspelling.
9) getrusage() going to take the check function runung time.
10) If the word is misspellings, It's counted and printed.
11) Then ,It going to prepare for the next word and start again to scan another word char by char.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

With fgetc it's more efficient to analyze each character at time, while with fscanf we will have to go over the word several times to analyze it.
And , with fscanf it's possible to overflow the buffer, if the scanned word is bigger than the buffer,

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because that way you can't modify the parameters inside the functions.
