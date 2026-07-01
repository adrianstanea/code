# s[start:stop:step]

l = [ x * 10 for x in range(1,7)]
print(l)

print(l[2:])
print(l[:3])

board = [ ['_'] * 3 for i in range(3)]
for row in board:
    print(row)