if __name__ == '__main__' :

    counter = 0

    file = open("../input/day1.txt","r")

    lines = file.readlines()

    computed_lines = []

    for i in range(len(lines)-2) :
        sum = 0        
        for j in range(3):
            sum += int(lines[i+j].strip("\n"))
        computed_lines.append(sum)

    data = None 
    for num in computed_lines :
        if data and num > data :
            counter += 1
        data = num 
    
    print(counter)
        

