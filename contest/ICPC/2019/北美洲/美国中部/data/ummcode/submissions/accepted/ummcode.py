#!/usr/bin/env python3

import string

#grab input:

speech = input()

#split on spaces

words = speech.split()


ummcode = ''

#make translator to remove punctuation from words!
translator = str.maketrans('','',string.punctuation)


for word in words:
    word = word.translate(translator)
    if set(word) == set('u') or set(word) == set('m') or set(word) == set(['u','m']):
        ummcode += word

ummcode = ['1' if k == 'u' else '0' for k in ummcode]


#split code into list of 7 characters
encoding = [''.join(ummcode[i:i+7]) for i in range(0, len(ummcode), 7)]

#print(encoding)

out = ""

for char in encoding:
    out += chr(int('0' + char, 2))

print(out)
