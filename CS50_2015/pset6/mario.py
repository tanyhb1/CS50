def main():
    height = GetHeight()
    pyramid(height)
    
def GetHeight():
    height = 0
    while(height<1 or height >23):
        x = input("height: ")
        height = int(x)
    return height
    
def pyramid(height):
    for i in range(height):
        space(height-(i+1))
        blocks(i+2)

def space(n):
    print(" " * (n), end = '')

def blocks(n):
    print("#" * n)
    
if __name__ == "__main__":
    main()