import sys

def createCmake( list  ):
    cmkFile = "CMakeLists.txt"
    cmakeFile = open("CMakeLists.txt","w")
    cmakeFile.write("set(SOURCE\n\t${SOURCE}\n")
    for n in list[1:]:
        cmakeFile.write("\t${CMAKE_CURRENT_SOURCE_DIR}/%s.cpp\n"  % n[0] )

    cmakeFile.write("\tPARENT_SCOPE)\n\nset(HEADERS\n\t${HEADERS}\n")
    for n in list[1:]:
        cmakeFile.write("\t${CMAKE_CURRENT_SOURCE_DIR}/%s.h\n" % n[0] )
    cmakeFile.write("\tPARENT_SCOPE)\n")    

def csvToList( csvFile ):
    with open(csvFile) as f:
        content = f.readlines()

    l1 =  [n.rstrip() for n in content]
    l2 = [n.rsplit(',') for n in l1]
    return l2


def listToCpp( list ):
 
    genTypesFile( list )
    for item in list[1:]:
        genCpp(item)
        genH(item)

def genTypesFile( list ):

    
    fileType = open("DroneMsgTypes.h","w")
    fileType.write("#ifndef DRONEMSGTYPES_H\n")
    fileType.write("#define DRONEMSGTYPES_H\n\n")
    fileType.write("""#include "Structs.h"\n""")
    fileType.write("namespace DroneMsgTypes\n{\n")
    for n in list[1:]:
        idNum = n[1]
        msgName = n[0]
        fileType.write("\tstatic const unsigned int %sId = %s;\n" % (msgName, idNum))
    fileType.write("};\n\n#endif")

def genCpp( entry ):
    msgName = entry[0]
    msgId = entry[1]
    msgData = entry[3]
    msgEnd = "UNKNOWN"
    if( entry[2] == "Little" ):
        msgEnd = "LITTLE_E"
    if( entry[2] == "Big" ):
        msgEnd = "BIG_E"

    cppN = "%s.cpp" % msgName
   
    
    fcpp = open("%s.cpp" % msgName , "w")
    

    #cpp file
    fcpp.write("""#include "%s.h"\n""" % msgName )
    fcpp.write("%s::%s() : Message( sizeof( %s ) )\n{\n" %(msgName,msgName, msgData))
    fcpp.write("\tmyHeader.dataSize = sizeof(%s);\n" % msgData )
    fcpp.write("\tmyHeader.messageId = DroneMsgTypes::%sId;\n" % msgName)
    fcpp.write("\tmyHeader.endian = MessageTypes::%s;\n" % msgEnd)
    fcpp.write("\tldata = (char*)(&myData);\n}\n")

    fcpp.write("%s::~%s()\n" % (msgName,msgName) )
    fcpp.write("{\n\n}\n")

    fcpp.write("bool %s::getData(%s *data)\n" %(msgName,msgData) )
    fcpp.write("{\n\t*data = myData;\n\t return true;\n}\n")

    fcpp.write("bool %s::setData(%s *data)\n" % (msgName,msgData) )
    fcpp.write("{\n\tmyData = *data;\n\t return true;\n}\n")

               
def genH( entry ):
    msgName = entry[0]
    msgId = entry[1]
    msgData = entry[3]
    msgEnd = "UNKNOWN"
    if( entry[2] == "Little" ):
        msgEnd = "LITTLE_E"
    if( entry[2] == "Big" ):
        msgEnd = "BIG_E"
    hN = "%s.h" % msgName
    fh = open("%s.h" % msgName , "w")
    #h file
    fh.write("#ifndef %s_H\n" % msgName )
    fh.write("#define %s_H\n" % msgName )
    fh.write("""#include "Message.h"\n""")
    fh.write("""#include "DroneMsgTypes.h"\n""")
    fh.write("\n\n class %s : public Message \n" % msgName )
    fh.write("{\n")
    fh.write("public: \n\t%s();\n\t ~%s();\n" % (msgName,msgName))
    fh.write("\tbool getData(%s *data);\n" % msgData)
    fh.write("\tbool setData(%s *data);\n" % msgData)
    fh.write("\t%s myData;\n" % msgData )
    fh.write("private:\nprotected:\n")
    fh.write("};\n")
    fh.write("#endif")

    
fname = "./Messages.csv"
myList = csvToList( fname )
listToCpp( myList )
createCmake( myList ) 
