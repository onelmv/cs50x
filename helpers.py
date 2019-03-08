from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    result = set()

    # Taking each line from a. Spliting every eash line('\n') and strip the '\n'
    lines_a = a.splitlines()

    # Taking each line from b. Spliting every eash line('\n') and strip the '\n'
    lines_b = b.splitlines()

    # Comparing eash list and store the similar lines
    for line1 in lines_a:
        for line2 in lines_b:
            if line1 == line2:
                result.add(line1)

    return result


def sentences(a, b):
    """Return sentences in both a and b"""

    result = set()

    # Split eash sentenses from the text( with nltk library)
    sentences_a = sent_tokenize(a, language='english')
    sentences_b = sent_tokenize(b, language='english')

    # Comparing eash list and store the similar senteces
    for sent1 in sentences_a:
        for sent2 in sentences_b:
            if sent1 == sent2:
                result.add(sent1)

    return result


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    result = set()
    s1 = []
    s2 = []
    i = 0

    for substr in a:
            s1.append(a[i:i+n])
            i += 1

    i = 0
    for substr in b:
        s2.append(b[i:i+n])
        i += 1

    for l in s1:
        for m in s2:
            if l == m and len(l) == n:
                result.add(l)

    return result