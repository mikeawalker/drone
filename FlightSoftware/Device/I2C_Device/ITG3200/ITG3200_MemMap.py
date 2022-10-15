import sys



def txtToList( txtFile ):
    print txtFile
    with open(txtFile) as f:
            content = f.readlines()

    l1 = [n.rstrip() for n in content]
    name = l1[0]
    l2 = [n.rsplit(' ') for n in l1[1:]]
    outList = {"name":name , "map":l2}
    return outList


def listToHeader( myList  ):
    dev = myList["name"].rsplit(' ')
    devName = dev[0]
    devId = dev[1]
    memMap = myList["map"]
    fileOut = open("%s_MemMap.h"%devName,'w')
    fileOut.write("#ifndef %s_MemMap_H\n" % devName )
    fileOut.write("#define %s_MemMap_H\n" % devName )
    fileOut.write("namespace %sMap\n{\n"%devName)
    fileOut.write("static const unsigned int deviceId = %s;\n" % devId )
    for n in memMap:
        addr = n[0]
        regName = n[1]
       # comment = ' '.join(n[5:])
       # rw = n[2]
       # if( rw=="R" ):
       #     r=1
       #     w=0
       # elif(rw=="W"):
       #     w=1
       #     r=0
       # elif(rw=="R/W"):
       #     r=1
       #     w=1
       # else:
       #    r=0
       #     w=0
            
        #expVal = memMap[4]

        fileOut.write("static const unsigned int %s = %s; //  \n" %(regName , addr  ))
    fileOut.write("};\n")
    fileOut.write("#endif")


fname = "ITG3200_MemMap.txt"
myList = txtToList(fname)
listToHeader(myList)
