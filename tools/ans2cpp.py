f = open('../assets/fruit.ans', 'rb')
inbytes = f.read()
f.close()
outs = "unsigned char* fruit = \""
for b in inbytes:
    o = '\\x' + "{:02x}".format(b)
    outs += o
outs += "\";"
print(outs)
