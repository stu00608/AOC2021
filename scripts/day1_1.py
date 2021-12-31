if __name__ == '__main__' :

    counter = 0

    file = open("../input/day1.txt","r")

    data = None

    for num in file :
        if data and int(num) > data :
            counter += 1
        data = int(num) 
    
    print(counter)

