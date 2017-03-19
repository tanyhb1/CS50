def main():
    #type of credit card
    cardtype = 'INVALID'
    while(True): 
        cardnumber = input("Number :")
        if cardnumber.isdigit():   
            cardnumber = int(cardnumber)
            if cardnumber > 10**13 and cardnumber <= 9999999999999999:
                break
    cardtype = check(cardnumber, cardtype)
    if verify(cardnumber, cardtype):
        print(cardtype)
    else:
        print('INVALID')
  
#checking the type of credit card 
def check(cardnumber, cardtype):
    #AE = 15 digits, MC = 16 digits, VISA = 13 and 16 digits
    if (cardnumber/(10**11)) < 100 and (cardnumber/(10**11) > 0):
        cardtype = 'VISA'
    elif cardnumber/(10**13) < 100 and cardnumber/(10**13) > 0:
        cardnumber/(10**11)
        cardtype = 'AMERICAN EXPRESS'
    elif cardnumber/(10**14) < 100 and cardnumber/(10**14) > 0:
        if cardnumber/(10**14) >= 51 and cardnumber/(10**14) < 56:
            cardnumber/(10**11)
            cardtype = 'MASTERCARD'
        elif cardnumber/(10**15) >= 4 and cardnumber/(10**15) < 5:
            cardnumber/(10**11)
            cardtype = 'VISA'
    return(cardtype)

def verify(cardnumber, cardtype):
    x = str(cardnumber)
    #creating list to store values
    a = []
    b = []
    for i, x in enumerate(x[::-1]):
        x = int(x)
        if i % 2 == 1:
            x = x * 2
            if (x >= 10):
                x = str(x)
                for d in x:
                    d = int(d)
                    a.append(d)
            else:
                a.append(x)
        else:
            b.append(x)
            
    c = sum(a) + sum(b)
    if c % 10 == 0:
        return True
    else:
        return False
    
if __name__ == "__main__":
    main()