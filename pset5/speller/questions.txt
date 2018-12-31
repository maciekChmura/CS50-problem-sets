# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It is a word invented by the president of the National Puzzlers' League as a synonym for the disease known as silicosis.
It is the longest word in the English language published in a dictionary, the Oxford English Dictionary,
which defines it as "an artificial long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for who, which can be one of the following:

       RUSAGE_SELF
              Return resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

       RUSAGE_CHILDREN
              Return  resource  usage  statistics for all children of the calling process that have terminated and been waited for.  These statistics will include the resources used by grandchil‐
              dren, and further removed descendants, if all of the intervening descendants waited on their terminated children.

       RUSAGE_THREAD (since Linux 2.6.26)
              Return resource usage statistics for the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

To not copy whole structs into calculate, to not waste resources.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

For each word in the file, untill the end of file. Start reading each symbol in file. If the file is an alphabetical character or apostophe, append character to word. If the word is too long (specified in LENGTH) ignore it. If the word has number ignore it. If we found something else it must ba an end of the word. When we have a word we can do spelling check. Print word if misspelled. Go to next word.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

It would be hard to skip numbers in words, or any other not needed characters that we dont want to check.
When we construct our won word from reading letter we can use less memory to "save" it.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

These parameters are intended to not change during function execuction.
