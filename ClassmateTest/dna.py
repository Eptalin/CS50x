import sys



def main():


    if len(sys.argv) != 3:
        print("Wrong Usage \npython [source code file] [database file] [seqence file]")
        return


        # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], "r") as databaseFile:
        database = []
        while True:
            data = databaseFile.readline()
            if not data:
                break
            x = list(data)
            for i in range(len(x)):
                if x[i] == ",":
                    x[i] = " "
            database.append("".join(x).split())
    sequences = []
    sequencesDatabase = ['name']
    with open(sys.argv[2], "r") as sequenceFile:


        sequence = sequenceFile.read()


    j = 0
    tmpcount = 0
    count = 0
    str_count = [0]


    for i in range(1, len(database[0])):
        while True:


            if sequence[j:j+len(database[0][i])] == database[0][i]:
                tmpcount += 1
                if sequence[j:j+len(database[0][i])] == "AATG":
                    print(f"j: {j}, tmpcount: {tmpcount}")
                j += len(database[0][i])-1
            elif tmpcount >= count:
                count = tmpcount
                tmpcount = 0
            j += 1
            if j >= len(sequence):
                if tmpcount >= count:
                    count = tmpcount
                    tmpcount = 0
                j = 0
                break
        str_count.append(count)
        count = 0
        tmpcount = 0
        j = 0


    match = True
    for i in range(1, len(database)):
        match = True
        for j in range(1, len(database[0])):
            if str_count[j] == int(database[i][j]):
                match == True
            else:


                match = False
                break
        if match == True:
            print(database[i][0])
            break


    if match == False:
        print("No match")


    print(str_count)
    return



main()
