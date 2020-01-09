f = open('rgb.txt','r')
rgbs = f.read()
#rgbs = rgbs.replace('\n', ' ')
rgbs = rgbs.replace('\t\t', ' ')
rgbs = rgbs.replace('\t', '')
rgbs = rgbs.split('\n')
rgbs2 = []
i = 0
while i < len(rgbs):
    if rgbs[i] != '':
        rgbs2.append(rgbs[i])
    i += 1
i = 0
outs = ''
while i < len(rgbs2):
    #a = rgbs2[i].lstrip('0123456789')
    a = rgbs2[i][:3].strip()
    b = rgbs2[i][4:7].strip()
    c = rgbs2[i][8:11].strip()
    d = rgbs2[i][12:].strip()
    outs += "\"" + a + ',' + b + ',' + c + ',' + d + "\",\n"
    i += 1

f = open('rgb.csv','w')
f.write(outs)
f.close()
