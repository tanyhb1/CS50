import sys

def main():
    if len(sys.argv) != 2:
        print("Please enter a phrase for the cipher.")
        return 1
    cipher = sys.argv[1] 
    message = input("Please enter the sentence you want to encrypt: ")
    message = list(message.strip(' '))
    counter = 0
    for i, j in enumerate(message[::len(cipher)]):
        for c in cipher:
            if j.isalpha():
                message[i+counter*len(cipher)] = ord(message[i+counter*len(cipher)])
                message[i+counter*len(cipher)] = message[i+counter*len(cipher)] + ord(c)
                message[i+counter*len(cipher)] = chr(message[i+counter*len(cipher)]%65)
                print (message[i+counter*len(cipher)])
                
        
    
    
    
if __name__ == "__main__":
    main()