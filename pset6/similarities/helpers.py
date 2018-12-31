from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    # split each string into lines
    # make a set of each string lines
    aSet = set(a.split('\n'))
    bSet = set(b.split('\n'))
    # return a new list of lines that are both in a and b
    sameLines = aSet & bSet
    return sameLines

# test
# ./compare --lines FILE1 FILE2
# ======


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    aSet = set(sent_tokenize(a))
    bSet = set(sent_tokenize(b))
    sameSentences = aSet & bSet
    return sameSentences

# test
# ./compare --sentences FILE3 FILE4
# ======


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    aArray = []
    bArray = []
    # TODO
    for index1, letterA in enumerate(a):
        temp = a[index1:n + index1]
        aArray.append(temp)
    aSet = set(aArray)
    if n > 1:
        aSet = set(aArray[0:-n+1])

    for index2, letterB in enumerate(b):
        temp = b[index2:n + index2]
        bArray.append(temp)
    bSet = set(bArray)
    if n > 1:
        bSet = set(bArray[0:-n+1])

    sameSubStr = aSet & bSet

    return sameSubStr

# test
# ./compare --substrings 1 STR1 STR2
# ======
