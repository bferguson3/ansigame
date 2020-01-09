import os, sys
if len(sys.argv) != 2:
    print("\nUsage:\n $ python3 ./ans2cpp.py <ANSI filename>\n\nOutput:\n C-string in .h file in this folder")
    sys.exit()
f = open(sys.argv[1], 'rb')
inbytes = f.read()
f.close()
h, t = os.path.split(sys.argv[1])
t = t.split('.')
outs = "const char* " + t[0] + " = \""
for b in inbytes:
    o = '\\x' + "{:02x}".format(b)
    outs += o
outs += "\";"
f = open("./" + t[0] + ".h", 'w')
f.write(outs)
f.close()
print("\n" + t[0] + ".h written successfully.")
