import Inventory

class Checkout:
    def __init__(self, filename):
        self.Inventory = Inventory.Inventory(filename)
        self.clear()

    def clear(self):
        self.ShoppingList = dict()
        self.total = 0.0

    def scan(self, inpItem):
        item = inpItem.strip().upper()
        #ignore unknown items
        if item in self.Inventory.InventoryList:
            if item in self.ShoppingList:
                self.ShoppingList[item] += 1
            else:
                #ignore blank items
                if item != "":
                    self.ShoppingList[item] = 1
            self.calculatePrice()

    def calculatePrice(self):
        self.total = 0.0
        for item in self.ShoppingList:
            itemCount = self.ShoppingList[item]
            itemPrice = self.Inventory.InventoryList[item].Price
            # Offers and discounts here
            if item == "VOUCHER":
                # Every second item of this type is free (buy 2 for the price of one)
                free_items = int(itemCount/2)
                self.total += ( itemCount - free_items ) * itemPrice
            #Discounted price for 3 or more 
            elif item == "TSHIRT" and itemCount >= 3:
                self.total += itemCount * 19.00
            else:
                self.total += itemCount * itemPrice

    def __repr__(self):
        str_rep = "<Checkout ["
        for item in self.ShoppingList:
            str_rep += "" + item + ":" + str(self.ShoppingList[item]) + ","
        return str_rep + "], Total" + "{0:.2f}€".format(self.total)  + ">"

    def __str__(self):
        str_rep = "{<Checkout> ["
        first_item_added = False
        for item in self.ShoppingList:
            if first_item_added == True:
                str_rep += ", "
            first_item_added = True
            str_rep += "" + item + ":" + str(self.ShoppingList[item])
        return str_rep + "], Total: " + "{0:.2f}€".format(self.total) + "}"


#Test for the Checkout class
def run_tests(filename):
    sc = Checkout(filename)
    sc.scan("VOUCHER")
    sc.scan("VOUCHER")
    sc.scan("VOUCHER")
    sc.scan("MUG")
    sc.scan("TSHIRT")
    sc.scan("TSHIRT")
    sc.scan("TSHIRT")
    sc.scan("TSHIRT")
    print(sc)
    print("{0:.2f}€".format(sc.total))


if __name__ == "__main__":
    import sys
    if(len(sys.argv) != 2):
        print("Usage is " + sys.argv[0] + " <filename>")
    else:
        run_tests(sys.argv[1])





