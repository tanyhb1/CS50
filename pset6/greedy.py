def main():
    x = 0
    counter = 0
    while(x <= 0):
        x = float(input("How much change is owed, sir? "))

    #convert dollar to cents
    change = x*100
    
    while(change >= 25):
        change = change - 25
        counter = counter + 1
    while(change >= 10):
        change = change - 10
        counter = counter + 1
    while(change >= 5):
        change = change - 5
        counter = counter + 1
    while(change >= 1):
        change = change - 1
        counter = counter + 1
    print(counter)
    
    
    
if __name__ == "__main__":
    main()