import Checkout
import sys

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage is " + sys.argv[0] + " <filename>")
    else:
        c = Checkout.Checkout(sys.argv[1])
        
        data = input()
        while data.upper() != "QUIT":
            if data == "":
                data = input()
                continue
            data_list = data.split(",")
            for item in data_list:
                c.scan(item)
            print(c.total)
            c.clear()
            data = input()
